#include <stdio.h>
#include <assert.h>

// is_little_endian returns 1 when compiled and run on a little-endian machine,
// and returns 0 when compiled and run on a big-endian machine.
// it must run on any machine regardless of its word size.
int is_little_endian(void) {
	// if little-endian
	// return 1
	// else
	// return 0
}

// this is my first time using assert.h.
// assert.h implements "runtime assertion" in C.
// "Assertion is a predicate connected to a point in the program that 
// always should evaluate to true at that point in code execution".
// this is basically how we ensure this program runs on any machine,
// regardless of whether or not is_little_endian returns true. 
int main(void) {
	assert(is_little_endian());
	return 0;
}
