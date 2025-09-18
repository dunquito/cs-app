/*
 * 2.62
 *
 * Write a function int_shifts_are_arithmetic() that yields 1 when run on a machine that uses arithmetic right shifts 
 * for data type int and yields 0 otherwise. Must work on a machine of any word size.
 *
*/

#include <stdio.h>
#include <assert.h>

int int_shifts_are_arithmetic() {
	int num = -1;				/* all bits = 1, in two's complement */
	
	/*
	 * if right shifts are arithmetic, num >> 1 is ALSO all ones (still -1)
	 * if right shifts are logical, then num >> 1 has a zero in the MSB and ones elsewhere
	 *
	 * then we check with num ^ (num >> 1) -->
	 * arithmetic shift: num ^ num == 0, so !(0) --> 1.
	 * logical shift: result would be nonzero, so !nonzero --> 0.
	 */
	return !(num ^ (num >> 1));
}

int main(int argc, char* argv[]) {
	assert(int_shifts_are_arithmetic());
	return 0;
}
