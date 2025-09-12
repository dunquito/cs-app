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

int A(int x) {
	return x;
}

int B(int x) {
	return x;
}

int C(int x) {
	return x;
}

int D(int x) {
	return x;
}

int main(int argc, char *argv[]) {
	
	int allOne = ~0;
	int allZero = 0;

	assert(A(allOne));	
	assert(!B(allOne));
	assert(C(allOne));
	assert(!D(allOne));

	assert(!A(allZero));
	assert(B(allZero));
	assert(!C(allZero));
	assert(D(allZero));

	// test magic number 0x1234ff
	// assert(!A(0x1234ff));
	// assert(!B(0x1234ff));
	// assert(C(0x1234ff));
	// assert(D(0x1234ff));

	// test magic number 0x1234
	// assert(!A(0x1234));
	// assert(!B(0x1234));
	// assert(!C(0x1234));
	// assert(D(0x1234));
	
	return 0;
}
