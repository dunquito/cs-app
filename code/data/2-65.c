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

int odd_ones(unsigned x) {
	// Need to finish this. Can't for the life of me figure it out
	return x;
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




