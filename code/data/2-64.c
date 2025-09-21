/*
 * 2.64
 *
 * Write code to implement the following function:
 *
 * Return 1 when any odd bit of x equals 1; 0 otherwise
 * int any_odd_one(unsigned x);
 *
 * Code must follow the following bit-level integer coding rules:
 *
 * 1. Integers are represented in two's-complement form
 * 2. Right shifts of signed data are performed arithmetically
 * 3. Data type int is "w" bits long. Code should work as long as w is a 
 * multiple of 8. Can use sizeof(int) << 3 to compute w.
 * 4. Conditionals, loops, switch statements, function cals, and macro
 * invocations are forbidden.
 * 5. Division, modulus, and multiplication are forbidden.
 * 6. Relative comparison operators (<, >, <=, >=) are forbidden.
*/

#include <stdio.h>
#include <assert.h>

/*
 * 0xAAAAAAAA = 10101010...1010 in binary. This feels like a "trick", but I 
 * don't know how else you solve this problem. Odd positions are 1, even 
 * positions are 0, which gives us the ability to keep only the odd bits 
 * of x using bitwise AND.
 *
 * Then we use the same double negation we've used before to convert 
 * nonzero -> 1, zero -> 0. (this just guarantees the return value is 
 * exactly 0 or 1).
*/
int any_odd_one(unsigned x) {
	return !!(x & 0xAAAAAAAA);
}

int main(void) {
	// All zeros
	assert(any_odd_one(0x0) == 0);

	// Only even bits set
	assert(any_odd_one(0x55555555) == 0);

	// Only odd bits set
	assert(any_odd_one(0xAAAAAAAA) == 1);

	// Mixed (all bits set)
	assert(any_odd_one(0xFFFFFFFF) == 1);

	// Small values
	assert(any_odd_one(1) == 0); // binary ends in 0001 (even bit only)
	assert(any_odd_one(2) == 1); // binary ends in 0010 (odd bit set)
	assert(any_odd_one(3) == 1); // binary ends in 0011 (odd + even)
	
	printf("All tests passed.\n");

	return 0;
}
