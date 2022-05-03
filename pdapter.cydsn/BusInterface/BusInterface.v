
//`#start header` -- edit after this line, do not edit this line
// ========================================
//
// Copyright YOUR COMPANY, THE YEAR
// All Rights Reserved
// UNPUBLISHED, LICENSED SOFTWARE.
//
// CONFIDENTIAL AND PROPRIETARY INFORMATION
// WHICH IS THE PROPERTY OF your company.
//
// ========================================
`include "cypress.v"
//`#end` -- edit above this line, do not edit this line
// Generated on 05/04/2022 at 00:27
// Component: BusInterface
module BusInterface (
	output [7:0] data_w,
	output  data_w_oe,
	output  output0_oe,
	output  output1_oe,
	input  [7:0] address_r,
	input   clock,
	input  [7:0] data_r,
	input  [7:0] input0,
	input  [7:0] input1,
	input   ioe,
	input   rd,
	input   wr
);

//`#start body` -- edit after this line, do not edit this line

wire decoded = !ioe & ((address_r & 8'hfe) == 8'h40);
wire cpu_reading = decoded & !rd;
wire cpu_writing = decoded & !wr;
wire index = address_r[0];

reg [7:0] data_w_reg;

assign data_w_oe = cpu_reading;
assign data_w = data_w_reg;

always @(posedge clock) data_w_reg <= (index == 0) ? input0 : input1;

assign output0_oe = cpu_writing & (index == 0);
assign output1_oe = cpu_writing & (index == 1);

//`#end` -- edit above this line, do not edit this line
endmodule
//`#start footer` -- edit after this line, do not edit this line
//`#end` -- edit above this line, do not edit this line
