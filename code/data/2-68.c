/*
 * 2.68
 *
 * Write code for a function with the following prototype:
 *
 * Mask with least significant n bits set to 1
 * Examples: n = 6 --> 0x3F, n = 17 --> 0x1FFFF
 * Assume 1 <= n <= w
 *
 * Your function should follow the same integer encoding rules:
 *
 * 1. Integers are represented in two's complement form
 * 2. Right shifts of signed data are performed arithmetically
 * 3. Data type int is "w" bits long. Can use sizeof(int) << 3 to compute w.
 * 4. Conditionals, loops, switch statements, function calls, and macro 
 * invocations are forbidden,
 * 5. Division, modulus, and multiplication are forbidden.
 * 6. Relative comparison operators (<, >, <=, >=) are forbidden.
 *
 * Be careful of the test case n = w.
*/

int lower_one_mask(int n);
