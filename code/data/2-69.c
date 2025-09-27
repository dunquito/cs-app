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

/*
 * If n = 4
 * We're right shifting by w - n
 * 32 - 4 = 28
 *
 * Say, 11110000 00000000 00000000 00000000
 * then 00000000 00000000 00000000 00001111
 *
 * But we also need to shift the remaining bits LEFT by an equal amount
 * So create two variables out of x
 *
 * Right shift one by (w - n)
 * Left shift the other by n
 *
 * Then... OR them together? We need the right shift to be LOGICAL...
 *
 * x = 11110101 01010101 01010101 01010101
 * n = 4
 * The result we're looking for is
 * 01010101 01010101 01010101 01011111
 *
 * So
 * this = x >> (w - n) -> x >> (32 - 4) -> x >> 28
 * this = 00000000 00000000 00000000 00001111
 *
 * And
 * that = x << 4
 * that = 01010101 01010101 01010101 01010000
 *
 * return this | that
*/
unsigned rotate_left(unsigned x, int n) {
	int w = sizeof(int) << 3;

	unsigned int right = x >> (w - n);
	unsigned int left = x << n;

	return right | left;
}

// need to finish and run tests
int main(void) {
	return 0;
}
	
