#include <stdio.h>
#include <assert.h>

/*
 * Problem 2.60
 * Suppose the number of bytes in a w-bit word from 0 (least significant) to 
 * w/8 - 1 (most significant). Write code for the following C function, which 
 * will return an unsigned value in which byte i of argument x has been 
 * replaced by byte b:
 *
 * unsigned replace_byte (unsigned x, int i, unsigned char b);
 *
 * Example output:
 *
 * replace_byte(0x12345678, 2, 0xAB) --> 0x12AB5678
 * replace_byte(0x12345678, 0, 0xAB) --> 0x123456AB
 */

unsigned replace_byte(unsigned x, int i, unsigned char b) {
	
	// basic error checking
	if (i < 0) {
		printf("replace_bytes: i was passed as a negative value\n");
		return x;
	}

	// basic error checking
	if (i > sizeof(unsigned) - 1) {
		printf("replace_bytes: i was passed as a value greater than sizeof(unsigned)\n");
		return x;
	}
	
	unsigned mask = ((unsigned) 0xFF) << (i << 3);
	unsigned pos_byte = ((unsigned) b) << (i << 3);


	return (x & ~mask) | pos_byte;
}
