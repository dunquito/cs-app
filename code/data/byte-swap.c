#include <stdio.h>
#include <assert.h>

/*
 * Problem 2.59
 * Write a C expression that will yield a word consisting of the least 
 * significant byte of x and the remaining bytes of y. For operands 
 * x = 0x89ABCDEF and y = 0x76543210, this would give 0x765432EF,
 */

// the expression is (x & 0xFF) | (y & ~0xFF)
// (0x89ABCDEF & 0xFF) = 0x000000EF
// (y & ~0xFF) = 0x11111100 
int main(void) {

	// 0xff is the appropriate mask to make the math in the above equation 
	// work.
	// we define our values of type size_t, which is an unsigned integer 
	// data type
	size_t mask = 0xff;
	size_t x = 0x89ABCDEF;
	size_t y = 0x76543210;

	size_t result = (x & mask) | (y & ~mask);

	assert(result == 0x765432EF);
	return 0;
}
