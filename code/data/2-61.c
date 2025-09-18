/*
 * The code in this problem must follow these rules:
 *
 * Assumptions
 * 	Integers are represented in two's complement form
 * 	Right shifts of signed data are performed arithmetically
 * 	Data type int is "w" bits long. For this problem, the code must work so long as w is a 
 * 	multiple of 8. sizeof(int) << 3 is allowed to compute w.
 *
 * Forbidden
 * 	Conditionals (if or ?:), loops, switch statements, function calls, and macro invocations
 * 	Division, modulus, and multiplication
 * 	Relative comparison operators (<, >, <=, and >=).
 *
 * Allowed operations
 * 	All bit-level and logic operations
 * 	Left and right shifts, but only with shift amounts between 0 and w - 1.
 * 	Addition and subtraction
 * 	Equality (==) and inequality (!=) tests. (Some other problems in this chapter do NOT 
 * 	allow these.
 * 	Integer constants (INT_MIN and INT_MAX)
 * 	Casting between data types int and unsigned, either explicitly or implicitly.
 */

/* 2.61
 * Write C expressions that evaluate to 1 when the following conditions are true and 
 * to 0 when they are false. Assume x is of type int.
 *
 * A. Any bit of x equals 1.
 * B. Any bit of x equals 0.
 * C. Any bit in the least significant byte of x equals 1.
 * D. Any bit in the most significant byte of x equals 0.
 *
 * This problem has an additional restriction. Equality (==) and inequality (!=)
 * are not allowed.
 */

#include <stdio.h>
#include <assert.h>
#include <limits.h>

/*
 * !!x returns 1 for any nonzero x and 0 for x == 0.
 *
 * A(10101010) = !(!10101010) = !(0) = 1
 * A(11111111) = !(!11111111) = !(0) = 1
 * A(00000000) = !(!00000000) = !(1) = 0
*/
int A(int x) {
	return !!x;
}

/*
 * ~x is the bit-wise NOT. so, any bit that WAS a 1, becomes a 0, and vice versa.
 * do that, then the operation is the same as above in A.
 * if ~x is nonzero (x has at least one 0), !!(~x) becomes 1. 
 *
 * B(10101010) = !!(~10101010) = !!(01010101) = !(0) = 1
 * B(11111111) = !!(~11111111) = !!(00000000) = !(1) = 0
 * B(00000000) = !!(~00000000) = !!(11111111) = !(0) = 1
*/
int B(int x) {
	return !!(~x);
}

/*
 * (x & 0xFF) isolates the least-significant bit.
 * !!(...) maps nonzero -> 1 (some bit 1) and zero -> 0 (all zero).
 *
*/
int C(int x) {
	return !!(x & 0xFF);
}

/*
 * ((sizeof(int) - 1) << 3) equals ((sizeof(int) * 8) - 8) which shifts 0xFF into the
 * most-significant bit position.
 * then just test with (unsigned)x & mask.
*/
int D(int x) {
	unsigned mask = 0xFFu << (((sizeof(int) - 1) << 3)); /* (bytes - 1) * 8 is safe here */
	return !!((unsigned)x & mask);
}

int main(int argc, char *argv[]) {
	
	assert(A(1));				// simple one-bit set
	assert(A(-1));				// all bits set
	assert(!A(0));				// all bits 0
	assert(A(0x80000000));			// INT_MIN, top bit set

	assert(B(0));				// all zeroes
	assert(B(0x12345678));			// mixed
	assert(!B(~0));				// all ones

	assert(C(0x00000001));			// lowest bit set
	assert(C(0x00000080));			// high bit of LSB set
	assert(!C(0xFFFFFF00));			// LSB == 0x00, no bits set
	assert(C(0x1234FF));			// LSB == 0xFF, all ones

	assert(D(~0));				// MSB == 0xFF, all ones
	assert(!D(0x00FFFFFF));			// MSB == 0x00, all zeroes
	assert(D(0x7FFFFFFF));			// MSB = 0x7F, mixed bits
	assert(D(INT_MIN));			// MSB == 0x80, only top bit set

	printf("All tests passed.\n");
	return 0;
}
