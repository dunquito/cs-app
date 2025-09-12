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
		printf("replace_byte: i was passed as a negative value\n");
		return x;
	}

	// basic error checking
	if (i > sizeof(unsigned) - 1) {
		printf("replace_byte: i was passed as a value greater than sizeof(unsigned)\n");
		return x;
	}
	
	/*
	 * we can use left shifts to get after this problem
	 * say we call replace_byte(0x12345678, 2, 0xAB), like in the example 
	 * above. in that case, for variable "mask":
	 * mask = 0x000000FF << (2 << 3) 
	 * mask = 0x000000FF << (00000010 << 00000011)
	 * mask = 0x000000FF << 00010000
	 * mask = 0x000000FF << 16
	 * mask = 00000000 00000000 00000000 11111111 << 00010000
	 * mask = 00000000 11111111 00000000 00000000
	 *
	 * notice that our mask is now in that 2nd byte position.
	 *
	 * we use (i << 3) because 1 byte = 8 bits. so, if you want to move a value "over by 
	 * i bytes" in a word, you need to shift by 8 * i bits.
	 *
	 * i << 3 is just a "cheap" way of saying i * 8.
	 * Shifting left by 1 (i << 1) multiplies by 2.
	 * Shifting left by 3 (i << 3) multiplies by 2 ^ 3 = 8.
	 *
	 * So (i << 3) = i * 8 = "how many bits to shift to reach byte i."
	 *
	 * pos_byte = 0x000000AB << (2 << 3)
	 * pos_byte = 0x000000AB << 16
	 * pos_byte = 00000000 00000000 00000000 10101011 << 16
	 * pos_byte = 00000000 10101011 00000000 00000000
	 *
	 * (x & ~mask) | pos_byte
	 * (0x12345678 & ~0x00FF0000) | 0x00AB0000
	 * (0x12345678 & 0xFF00FFFF) | 0x00AB0000
	 * (0x12005678) | 0x00AB0000
	 * = 0x12AB5678
	*/ 
	unsigned mask = ((unsigned) 0xFF) << (i << 3);
	unsigned pos_byte = ((unsigned) b) << (i << 3);


	// "clear out the bytes to be overwritten, then drop in the new value"
	return (x & ~mask) | pos_byte;
}

int main(int argc, char *argv[]) {
	unsigned ex1 = replace_byte(0x12345678, 0, 0xAB);
	unsigned ex2 = replace_byte(0x12345678, 3, 0xAB);

	assert(ex1 == 0x123456AB);
	assert(ex2 == 0xAB345678);

	return 0;
}
