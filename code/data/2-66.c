/*
 * 2.66
 *
 * Write code to implement the following function:
 *
 * Generate mask indicating leftmost 1 in x. Assume w = 32.
 * For example, 0xFF00 -> 0x8000, and 0x6600 -> 0x4000.
 * If x = 0, then return 0.
 *
 * int leftmost_one(unsigned x);
 *
 * Must follow the same integer encoding rules:
 *
 * 1. Integers are represented in two's-complement form
 * 2. Right shifts of signed data are performed arithmetically
 * 3. Data type int is "w" bits long. Can use sizeof(int) << 3 to compute w.
 * 4. Conditionals, loops, switch statements, function cals, and macro
 * invocations are forbidden.
 * 5. Division, modulus, and multiplication are forbidden.
 * 6. Relative comparison operators (<, >, <=, >=) are forbidden.
 *
 * !!!!! Code should contain a total of at most 15 arithmetic, bitwise, and 
 * logical operations. !!!!!
 *
 * Hint: First transform x into a bit vector of the form [0 ... 011 ... 1].
*/

#include <stdio.h>
#include <assert.h>

/*
 * Here we can use | (bitwise OR) to propagate. "Propagate" means to take a 1 bit in some
 * position and extend its effect into lower positions (toward the right, less significant 
 * bits) by OR-ing with shifted copies of itself.
 *
 * Operations used:
 *
 * Propagation: 5 shifts + 5 ORs = 10 operations
 * Extraction: 1 shift + 1 NOT + 1 AND = 3 operations
 * Total = 13 (<= 15 total operations)
 *
 * Here's what that looks like for x = 0x6600, where we expect 0x4000:
 *
 * x = 0x00006600 = 0b 0000 0000 0000 0000 0110 0110 0000 0000
 * Looking at the nonzero region (0110 0110) in the middle,
 * the leftmost 1 in this word is bit 14 (because 0x4000 == 1 << 14), so the expected
 * output is 0x4000.
 *
 * 0x00006600 -> 0000 0000 0000 0000 0110 0110 0000 0000
 * x |= x >> 1 : 0x00007700 -> 0000 0000 0000 0000 0111 0111 0000 0000
 * x |= x >> 2 : 0x00007FC0 -> 0000 0000 0000 0000 0111 1111 1100 0000
 * x |= x >> 4 : 0x00007FFC -> 0000 0000 0000 0000 0111 1111 1111 1100
 * x |= x >> 8 : 0x00007FFF -> 0000 0000 0000 0000 0111 1111 1111 1111
 * x |= x >> 16 : 0x00007FFF -> 0000 0000 0000 0000 0111 1111 1111 1111
 * result = x & ~(x >> 1) : 0x00004000 -> 0000 0000 0000 0000 0100 0000 0000 0000
 *
 * After x |= x >> 1, each 1 sets itself and its immediate right neighbor (because
 * we're OR-ing with the value shifted right one). This extends any single 1 into a 
 * short run of up to 2 ones. In this example, those nearby 1s combine to 
 * give 0x7700 (0111 0111), i.e., more 1s to the right of the original leftmost 1.
 *
 * By working up to 32 bits, x is then of the form 0...0 0 1 1 1 1 1 ... 1. A single 1 
 * at the leftmost original position followed by all ones down to bit 0.
 * Then we extract the leftmost 1.
 *
 * If x == 0, every propagation step leaves x == 0. Then x & ~(x >> 1) is 0 & ~0 -> 0, 
 * so the function correctly returns 0.
*/
int leftmost_one(unsigned x) {
	
	/* Propagate the leftmost 1 rightwards so that all lower bits
	 * become 1. After these steps, x will be of the form:
	 * 	0...0 1 1 1 1 ... 1
	 * where the leftmost 1 corresponds to the original leftmost 1.
	 * This uses successive widening (1, 2, 4, 8, 16) to cover 32 bits.
	*/
	x |= x >> 1;	// merge adjacent bits
	x |= x >> 2;	// merge 2-bit blocks
	x |= x >> 4;	// merge 4-bit blocks
	x |= x >> 8;	// merge 8-bit blocks
	x |= x >> 16;	// merge 16-bit blocks -> full propagation for 32-bit int

	/* Now x is 0...0111...1 (ones from leftmost 1 down). To isolate the 
	 * leftmost 1, clear all bits below it:
	 * x		= 0...0 1 1 1 1 1 ...
	 * x >> 1	= 0...0 0 1 1 1 1 ...
	 * ~(x >> 1)	= 1...1 1 0 0 0 0 ...
	 *
	 * x & ~(x >> 1) keeps only the single 1 at the original leftmost position.
	*/
	return (int)(x & ~(x >> 1));	
}

int main(void) {
	// Given examples
	assert(leftmost_one(0xFF00u) == 0x8000);
	assert(leftmost_one(0x6600u) == 0x4000);

	// Edge cases and more
	assert(leftmost_one(0x0u) == 0x0);			// zero -> zero
	assert(leftmost_one(0x1u) == 0x1);			// single least bit
	assert(leftmost_one(0x2u) == 0x2);			// single bit at position 1
	assert(leftmost_one(0x80000000u) == 0x80000000u);	// highest bit only
	assert(leftmost_one(0x7FFFFFFFu) == 0x40000000u);	// leftmost 1 at bit 30
	assert(leftmost_one(0x00F0u) == 0x0080u);		// 0x00F0 -> leftmost at 7 (0x0080)
	assert(leftmost_one(0x0100u) == 0x0100u);		// exactly one bit in middle

	// Some mixed patterns
	assert(leftmost_one(0x00008001u) == 0x00008000u);
	assert(leftmost_one(0x00A00000u) == 0x00800000u);

	printf("All tests passed.\n");

	return 0;
}
