/*
 * 2.68
 *
 * Write code for a function with the following prototype:
 *
 * Mask with least significant n bits set to 1
 * Examples: n = 6 --> 0x3F, n = 17 --> 0x1FFFF
 * Assume 1 <= n <= w
 *
 * Your function should follow the same integer encoding rules:
 *
 * 1. Integers are represented in two's complement form
 * 2. Right shifts of signed data are performed arithmetically
 * 3. Data type int is "w" bits long. Can use sizeof(int) << 3 to compute w.
 * 4. Conditionals, loops, switch statements, function calls, and macro 
 * invocations are forbidden,
 * 5. Division, modulus, and multiplication are forbidden.
 * 6. Relative comparison operators (<, >, <=, >=) are forbidden.
 *
 * Be careful of the test case n = w.
*/

#include <stdio.h>
#include <assert.h>

int lower_one_mask(int n) {
	int w = sizeof(int) << 3;	// number of bits in int

	/* Create an unsigned value with all bits = 0
	 * Right shift by (w - n).
	 * For 1 <= n <= w, (w - n) is in [0, w-1], so this 
	 * is well defined. The result is an unsigned value whose low n 
	 * bits are 1.
	*/	
	unsigned u = ~0u;
	return (int)(u >> (w - n));
}

int main(void) {
	int w = sizeof(int) << 3;

	assert(lower_one_mask(1) == 0x1);
	assert(lower_one_mask(6) == 0x3F);
	assert(lower_one_mask(8) == 0xFF);
	assert(lower_one_mask(17) == 0x1FFFF);	
	assert(lower_one_mask(w) == ~0);	// all ones
	
	printf("All tests passed.\n");
	return 0;
}
