#include "project.h"
#include <stdint.h>
#include <stdbool.h>

enum
{
    RS_IDLE = 0, /* no data in buffer, no data pending */
    RS_READABLE, /* data in buffer */
    RS_DONE,     /* data has been read */
};

enum
{
    RA_DATA = (1<<0), /* data has been from buffer */
    RA_DONE = (1<<1), /* interface has been seen in RS_DONE */
};

enum
{
    WS_WRITABLE = 0, /* waiting for data in buffer */
    WS_WRITING,      /* data is being sent */
    WS_DONE,         /* data has been sent */
};

enum
{
    WA_DATA = (1<<2), /* data has been placed in the buffer */
    WA_DONE = (1<<3), /* interface has been seen in WS_DONE */
};

enum
{
    RESET = 128
};

static int read_state = RS_IDLE;
static int write_state = WS_WRITABLE;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_Start();

    for(;;)
    {
        uint32_t ackbits = STATUS_REG1_Read();
        
        if (ackbits & RESET)
        {
            //UART_UartPutString("reset\r\n");
            read_state = RS_IDLE;
            write_state = WS_WRITABLE;
        }
        
        switch (read_state)
        {
            case RS_IDLE:
            {
                if (UART_SpiUartGetRxBufferSize() > 0)
                {
                    uint32_t b = UART_UartGetByte();
                    CONTROL_REG0_Write(b & 0xff);
                    read_state = RS_READABLE;
                    //UART_UartPutString("RS_IDLE -> RS_READABLE\r\n");
                }                
                break;
            }
            
            case RS_READABLE:
            {
                if (ackbits & RA_DATA)
                {
                    //UART_UartPutString("RS_READABLE -> RS_DONE\r\n");
                    read_state = RS_DONE;
                }
                break;
            }
            
            case RS_DONE:
            {
                if (ackbits & RA_DONE)
                {
                    //UART_UartPutString("RS_DONE -> RS_IDLE\r\n");
                    read_state = RS_IDLE;
                }
                break;
            }
        }
        
        unsigned bs = UART_SpiUartGetTxBufferSize();
        switch (write_state)
        {
            case WS_WRITABLE:
                if (ackbits & WA_DATA)
                {
                    write_state = WS_WRITING;
                    //UART_UartPutString("WS_WRITABLE -> WS_WRITING\r\n");
                }
                break;
            
            case WS_WRITING:
                if (bs < UART_UART_TX_BUFFER_SIZE)
                {
                    uint8_t b = STATUS_REG0_Read();
                    UART_UartPutChar(b);
                    write_state = WS_DONE;
                    //UART_UartPutString("WS_WRITING -> WS_DONE\r\n");
                }
                break;
            
            case WS_DONE:
                if (ackbits & WA_DONE)
                {
                    write_state = WS_WRITABLE;
                    //UART_UartPutString("WS_DONE -> WS_WRITABLE\r\n");
                }
                break;
        }
        
        bool cts = bs > (UART_UART_TX_BUFFER_SIZE / 2);
        CONTROL_REG1_Write(read_state | (write_state<<2) | (cts<<7));
    }
}
