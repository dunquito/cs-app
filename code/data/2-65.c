/*
 * 2.65
 *
 * Write code to implement the following function:
 *
 * Return 1 when x contains an odd number of 1s; 0 otherwise.
 * Assume w = 32.
 * int odd_ones(unsigned x);
 *
 * Your function must follow the following assumptions and restrictions:
 *
 * 1. Integers are represented in two's-complement form
 * 2. Right shifts of signed data are performed arithmetically
 * 3. Data type int is "w" bits long. Can use sizeof(int) << 3 to compute w.
 * 4. Conditionals, loops, switch statements, function calls, and macro
 * invocations are forbidden.
 * 5. Division, modulus, and multiplication are forbidden.
 * 6. Relative comparison operators (<, >, <=, >=) are forbidden.
 *
 * !!!!! Your code should contain a total of at most 12 arithmetic, bitwise, 
 * and logical operations !!!!!
*/

#include <stdio.h>
#include <assert.h>

/*
 * "XOR folding"
 * Can use XOR operations to "fold" down halves of the word until only 
 * 1 bit remains, e.g., x ^= x >> 16.
 *
 * So naturally, two numbers XOR'd together = 1 if the number of 1s in both
 * is odd.
*/

/*
 * Sample value of x = 0x12345678
 * 0x12345678 = 0b 0001 0010 0011 0100 0101 0110 0111 1000
 * b0 (LSB), b31 (MSB)
 * low 16 = 0x5678 (bits b0 - b15)
 * high 16 = 0x1234 (b16 - b31)
 *
 * First operation...
 * After x ^= x >> 16,
 * x >> 16 = 0x00001234
 * x = 0x12345678 ^ 0x00001234 = 0x1234444C = 0b 0001 0010 0011 0100 0100 0100 0100 1100
 * Upper half bits 16 - 31 remain equal to their original values in this step. 
 * LSB = 0
 *
 * Second...
 * After x ^= x >> 8,
 * x >> 8 = 0x00123444 (using current x)
 * x = 0x1234444C ^ 0x00123444 = 0x12267008 = 0b 0001 0010 0010 0110 0111 0000 0000 1000
 * LSB = 0
 *
 * Third...
 * After x ^= x >> 4,
 * x = 0x12267008 ^ (0x12267008 >> 4) = 0x13041708 = 0b 0001 0011 0000 0100 0001 0111 0000 1000
 * LSB = 0
 *
 * Fourth...
 * After x ^= x >> 2,
 * x = 0x13041708 ^ (0x13041708 >> 2) = 0x17C512CA = 0b0001 0111 1100 0101 0001 0010 1100 1010
 * LSB = 0
 *
 * Fifth...
 * After x ^= x >> 1,
 * x = 0x17C512CA ^ (0x17C512CA >> 1) = 0x1C279BAF = 0b 0001 1100 0010 0111 1001 1011 1010 1111
 * LSB = 1
 *
 * Finally, x & 1 = 1. Parity is odd.
 *
 * "Folding" like this doubles the group of original bit positions whose XOR is stored in the 
 * lower indices. After the last >> 1 step, bit 0 holds the XOR of EVERY original bit 
 * in the 32-bit word.
*/
int odd_ones(unsigned x) {
	
	x ^= x >> 16;	// fold upper 16 bits into lower 16
	x ^= x >> 8;	// fold upper 8 bits into lower 8
	x ^= x >> 4;	// and so on...
	x ^= x >> 2;	
	x ^= x >> 1;
	
	return x & 1;	// extract parity bit
}

int main(void) {
	// 0 has 0 ones (even)
	assert(odd_ones(0x0) == 0);

	// 1 has 1 one (odd)
	assert(odd_ones(0x1) == 1);

	// 3 (0b11) has 2 ones (even)
	assert(odd_ones(0x3) == 0);

	// 7 (0b111) has 3 ones (odd)
	assert(odd_ones(0x7) == 1);

	// 0xFFFFFFFF has 32 ones (even)
	assert(odd_ones(0xFFFFFFFF) == 0);

	// 0xFFFFFFFE has 31 ones (odd)
	assert(odd_ones(0xFFFFFFFE) == 1);

	// 0xAAAAAAAA = 16 ones (even)
	assert(odd_ones(0xAAAAAAAA) == 0);

	// 0xAAAAAAAA ^ 1 = 17 ones (odd)
	assert(odd_ones(0xAAAAAAAA ^ 1) == 1);

	printf("All tests passed.\n");
	
	return 0;
}




