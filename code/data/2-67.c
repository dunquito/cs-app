/*
 * 2.67
 *
 * You are given the task of writing a procedure int_size_is_32() that yields 
 * 1 when run on a machine for which an int is 32 bits, and yields 0 otherwise.
 * You are not allowed to use the sizeof operator. Here is a first attempt: 
 *
 * The following code does not run properly on some machines.
 * int bad_int_size_is_32() {
 *
 * 	// Set the most significant bit (msb) of 32-bit machine
 * 	int set_msb = 1 << 31;
 *	// Shift past msb of 32-bit word
 * 	int beyond_msb = 1 << 32;
 *
 * 	// set_msb is nonzero when word size is >= 32
 * 	// beyond_msb is zero when word size <= 32
 * 	return set_msb && !beyond_msb;
 * }
 *
 * When compiled and run on a 32-bit SUN SPARC, however, this procedure 
 * returns 0. The following compiler message gives us an indication of 
 * the problem:
 *
 * warning: left shift count >= width of type
 *
 * A. In what way does our code fail to comply with the C standard?
 * B. Modify the code to run properly on any machine for which data type int 
 * is at least 32 bits.
 * C. Modify the code to run properly on any machine for which data type int 
 * is at least 16 bits.
*/

#include <stdio.h>
#include <assert.h>

/*
 * The bad line is:
 * int beyond_msb = 1 << 32;
 *
 * You cannot shift by an amount >= the width of the type. That's undefined.
 * The compiler warning hints at this. On a machine where int is 32 bits, 
 * 1 << 32 attempts to shift by 32 positions while the width is 32.
 *
 * This problem did not state that the use of loops is forbidden, so that's 
 * what I'm going to use...
*/
int int_size_is_32() {
	unsigned u = 1u;	// start with 0000 ... 0001
	int count = 0;

	while (u != 0u) {
		u <<= 1;	// shift left by 1 each iteration
		count++;
	}

	return count == 32;
}

int int_size_is_16() {
	unsigned u = 1u;
	int count = 0;

	while (u != 0u) {
		u <<= 1;
		count++;
	}

	return count >= 16;
}

/*
 * main for testing.
*/
int main(void) {
	int w = (int)(sizeof(int) * 8); // using sizeof only for testing
	
	printf("Detected via sizeof: int is %d bits\n", w);
	printf("int_size_is_32(): %d\n", int_size_is_32());
	printf("int_size_is_16(): %d\n", int_size_is_16());

	assert(int_size_is_32() == (w == 32));
	assert(int_size_is_16() == (w >= 16));

	printf("All tests passed.\n");
	return 0;
}
