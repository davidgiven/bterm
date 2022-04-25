/* Amstrad NC200 cpmish BIOS © 2019 David Given
 * This file is distributable under the terms of the 2-clause BSD license.
 * See COPYING.cpmish in the distribution root directory for more information.
 */

#include <stdio.h>

static unsigned char normaltab[0x80] = {};
static unsigned char shiftedtab[0x80] = {};

/* Key table bit layout:
 *
 *     1 T T n n n n n
 *
 * T = 00: function
 * T = 01: more function
 * T = 10: cursor
 * T = 11: shifted cursor
 */

static void key(int keycode, unsigned char normal, unsigned char shifted)
{
    normaltab[keycode] = normal;
    shiftedtab[keycode] = shifted;
}

static void ckey(int keycode, unsigned char key)
{
    normaltab[keycode] = 0x80 | 0x40 | key;
    shiftedtab[keycode] = 0x80 | 0x60 | key;
}

static void fkey(int keycode, unsigned char key, unsigned char shifted)
{
    normaltab[keycode] = 0x80 | key;
    shiftedtab[keycode] = 0x80 | shifted;
}

int main(int argc, const char* argv[])
{
	key(0x31, '1', '!');
	key(0x32, '2', '"');
	key(0x33, '3', '#');
	key(0x34, '4', '$');
	key(0x35, '5', '%');
	key(0x36, '6', '^');
	key(0x37, '7', '&');
	key(0x38, '8', '*');
	key(0x39, '9', '(');
	key(0x30, '0', ')');
	key(0x2d, '-', '_');
	key(0x3d, '=', '+');
	key(0x1a, '\\', '|');

	key(0x0f, 9,   9);
	key(0x71, 'q', 'Q');
	key(0x77, 'w', 'W');
	key(0x65, 'e', 'E');
	key(0x72, 'r', 'R');
	key(0x74, 't', 'T');
	key(0x79, 'y', 'Y');
	key(0x75, 'u', 'U');
	key(0x69, 'i', 'I');
	key(0x6f, 'o', 'O');
	key(0x70, 'p', 'P');
	key(0x7c, '[', '{');
	key(0x5d, ']', '}');
	key(0x08, 127, 127);

	key(0x61, 'a', 'A');
	key(0x73, 's', 'S');
	key(0x64, 'd', 'D');
	key(0x66, 'f', 'F');
	key(0x67, 'g', 'G');
	key(0x68, 'h', 'H');
	key(0x6a, 'j', 'J');
	key(0x6b, 'k', 'K');
	key(0x6c, 'l', 'L');
	key(0x3b, ';', ':');
	key(0x27, '\'', '@');
	key(0x5c, '#', '~');
	key(0x0d, 13,  13);

	key(0x7a, 'z', 'Z');
	key(0x78, 'x', 'X');
	key(0x63, 'c', 'C');
	key(0x76, 'v', 'V');
	key(0x62, 'b', 'B');
	key(0x6e, 'n', 'N');
	key(0x6d, 'm', 'M');
	key(0x2c, ',', '<');
	key(0x2e, '.', '>');
	key(0x2f, '/', '?');

	key(0x20, ' ', ' ');
	key(0x7f, 8,   8);

	fkey(0x10, 11, 23); /* function keys */
	fkey(0x11, 12, 24);
	fkey(0x12, 13, 25);
	fkey(0x13, 14, 26);
	fkey(0x14, 15, 28);
	fkey(0x15, 17, 29);
	fkey(0x16, 18, 31);
	fkey(0x17, 19, 32);
	fkey(0x18, 20, 33);

	fkey(0x0c, 2,  2|0x20); /* nav cluster */
	fkey(0x0b, 7,  7|0x20);
	fkey(0x07, 5,  5|0x20);
	fkey(0x09, 3,  3|0x20);
	fkey(0x0e, 8,  8|0x20);
	fkey(0x0a, 6,  6|0x20);

	ckey(0x1e, 0); /* up */
	ckey(0x1d, 3); /* left */
	ckey(0x1f, 1); /* down */
	ckey(0x1c, 2); /* right */

	key(0x03, 27,  27); /* left row */
	fkey(0x04, 21, 34);
	fkey(0x05, 23, 23|0x20);
	fkey(0x06, 24, 24|0x20);

    printf("keyboard_normal_map:\n");
    for (int i=0; i<sizeof(normaltab); i++)
        printf("\t.db 0x%02x\n", normaltab[i]);
    printf("keyboard_shifted_map:\n");
    for (int i=0; i<sizeof(normaltab); i++)
        printf("\t.db 0x%02x\n", shiftedtab[i]);

    return 0;
}
