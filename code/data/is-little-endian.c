#include <stdio.h>
#include <assert.h>

// byte_pointer is a pointer to an object of type unsigned char.
// it references a sequence of bytes where each byte is considered to be a 
// nonnegative integer.
typedef unsigned char *byte_pointer;

// is_little_endian returns 1 when compiled and run on a little-endian machine,
// and returns 0 when compiled and run on a big-endian machine.
// it must run on any machine regardless of its word size.
int is_little_endian(void) {
	
	// creating an arbitrary value to test against
	int testVal = 0xff;

	// casting to type byte_pointer
	byte_pointer start = (byte_pointer) &testVal;

	// because byte_pointer references a sequence of bytes, we can index it as 
	// an array
	// therefore, if the first element of start is 0xff, we know we're on a little
	// endian machine.
	// ... finish these comments...
	
	// here is the same for-loop from show-bytes.c that we can use to test, and 
	// print the value of start as a 4-byte integer (or, sizeof(testVal)).
	/*
	int i;
	size_t len = sizeof(testVal);
	for (i = 0; i < len; i++)
		printf(" %.2x", start[i]);
	printf("\n"); */

	// because byte_pointer references a sequence of bytes, we can index it as 
	// an array.
	// therefore, if the first element of start is 0xff, we know we're on a little-
	// endian machine.
	// this is because 0xff, when represented as a 4-byte integer, is 0x000000ff.
	// so, big-endian: 00 00 00 ff
	// little-endian: ff 00 00 00
	if (start[0] == 0xff) {
		return 1;
	}

	return 0;
}

// this is my first time using assert.h.
// assert.h implements "runtime assertion" in C.
// "Assertion is a predicate connected to a point in the program that 
// always should evaluate to true at that point in code execution".
// this is basically how we ensure this program runs on any machine,
// regardless of whether or not is_little_endian returns true. 
int main(void) {
	// can call this in main to test, see above for-loop in is_little_endian
	// is_little_endian();
	assert(is_little_endian());
	return 0;
}
