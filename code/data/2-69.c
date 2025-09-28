/*
 * 2.69
 *
 * Write code for a function with the following prototype:
 *
 * Do rotating left shift. Assume 0 <= n < w
 * Examples when x = 0x12345678 and w = 32:
 * n = 4 -> 0x23456781, n = 20 -> 0x67812345
 *
 * Code must follow the same integer coding rules:
 *
 * 1. Integers are represented in two's complement form
 * 2. Right shifts of signed data are performed arithmetically
 * 3. Data type int is "w" bits long. Can use sizeof(int) << 3 to compute w.
 * 4. Conditionals, loops, switch statements, function calls, and macro
 * invocations are forbidden,
 * 5. Division, modulus, and multiplication are forbidden.
 * 6. Relative comparison operators (<, >, <=, >=) are forbidden.
 *
 * Be careful of the case n = 0.
*/

#include <stdio.h>
#include <assert.h>

/*
 * Originally, I had something that simplified down to something like:
 *
 * rotate_left(unsigned x, n) = (x << n) | ((unsigned)x >> (w - n))
 *
 * However, after failing some of my own tests I realized that 
 * this expression is undefined when n == 0, because it makes you 
 * shift by w (i.e., w - n == w). 
 *
 * To avoid this (without using conditionals), I had to mask the second 
 * shift amount so that when n == 0, the shift amount becomes 0 (which is 
 * safe), and when n != 0 the shift amount is w - n (also safe, within the 
 * range 0..w-1).
*/
unsigned rotate_left(unsigned x, int n) {
	int w = sizeof(int) << 3; 			// number of bits in int (w >= 1)

	// left: shift x by n (safe because 0 <= n < w)
	unsigned left = x << n;

	/*
	 * Computing shift amount for the right part safely, even when n == 0
	 *
	 * So amt becomes = (w - n) & (-!!n)
	 *
	 * !!n -> 0 when n == 0, 1 otherwise
	 * -!!n -> 0 when n == 0, -1 otherwise
	 *  
	 *  Then, casting to unsigned gives 0u, or just a mask of all ones
	 *  (w - n) & mask gives 0 when n == 0 (so we're just shifting by 0), else w - n when n != 0
	 *
	 *  This prevents shifting by w, which would be undefined
	*/
	unsigned mask = (unsigned)(-!!n);		// 0u when n == 0, else 0xFFFFFFFF ...
	unsigned amt = ((unsigned)(w - n)) & mask;	// 0 when n == 0, else w - n
	
	unsigned right = x >> amt;

	return (int)(left | right);
}

// Testing
int main(void) {
	int w = sizeof(int) << 3;

	// Given examples
	assert(rotate_left(0x12345678, 4) == 0x23456781);
	assert(rotate_left(0x12345678, 20) == 0x67812345);

	// n == 0 should be identity
	assert(rotate_left(0x12345678, 0) == 0x12345678);

	// rotate by 1 and by w - 1
	assert(rotate_left(0x80000000, 1) == 0x00000001); // top bit moves to low bit
	assert(rotate_left(0x00000001, w - 1) == 0x80000000); // same as above
	
	// some random checks
	for (int n = 0; n < w; ++n) {
		unsigned x = 0xDEADBEEFu;
		unsigned ref;

		if (n == 0) ref = x;
		else ref = (x << n) | (x >> (w - n));
		assert(rotate_left(x, n) == ref);
	}

	printf("All tests passed.\n");
	return 0;
}
	
