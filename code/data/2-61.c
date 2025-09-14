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

/*
 * return !~x;
 * Remember, ! is a logical operation, ~ is a bit-wise operation
 * ! is equivalent to "NOT". Like the other logical operators, they treat any nonzero argument
 * as representing TRUE and argument 0 as representing FALSE.
 *
 * ~ is bit-wise. Meaning, a 1 becomes 0; a 0 becomes 1.
 *
 * So, if x = 10101010, for example:
 * !(~10101010) = !(01010101) = 1 = TRUE.
 *
 * If x = 00000000:
 * !(~00000000) = !(11111111) = 0 = FALSE.
*/
int A(int x) {
	return !~x;
}

/*
 * return !!(~x);
 * Again, ~ is the bitwise NOT of x. It has a 1 in each position where x has a 0
 *
 * The double logical NOT (!!) converts any nonzero value to 1, and 0 stays 0.
 * !!(~x) -> 1 when ~x is nonzero (i.e., x has some zero bit), and 0 when ~x is zero 
 * (i.e., x == ~0, all bits 1).
 *
 * If x = 11010110, for example:
 * !!(~11010110) = !!(00101001) = !(0) = 1
 *
 * If x = 11111111:
 * !!(~11111111) = !!(00000000) = !(1) = 0
*/
int B(int x) {
	return !!(~x);
}

/*
 * return !!(x & 0xFF);
 *
 * We first have to isolate the least-significant bit with a mask, 0xFF.
 * This works regardless of the machine's word size, so long as it's a multiple 
 * of 8, which we are guaranteed by the assumptions listed above
 *
 * Then check if that byte is nonzero. I just used the same !! trick from before.
 * Nonzero --> 1
 * Zero --> 0
*/
int C(int x) {
	return !!(x & 0xFF);
}

/*
 * Actually need to compute w here. Problem says we're allowed to use:
 * w = sizeof(int) << 3;
 *
 * Then isolate the most significant bit.
 * To do this, shift x right by w - 8 to bring the MSB into the LEAST
 * significant byte position. All this does is extract the MSB as an 8-bit value.
 *
 * Then of course detect if any bit is 0.
 *
 * ~(something) flips the bits.
 * !!(something), from before, returns 0 if all ones, 1 otherwise.
*/
int D(int x) {
	int w = sizeof(int) << 3;
	return !!(~((x >> (w - 8)) & 0xFF));
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
	assert(!A(0x1234ff));
	assert(!B(0x1234ff));
	assert(C(0x1234ff));
	assert(D(0x1234ff));

	// test magic number 0x1234
	assert(!A(0x1234));
	assert(!B(0x1234));
	assert(!C(0x1234));
	assert(D(0x1234));
	
	return 0;
}
