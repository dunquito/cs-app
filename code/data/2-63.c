/*
 * 2.63
 *
 * Fill in code for the following C functions. Function srl performs a logical 
 * right shift using an arithmetic right shift (given by value xsra), 
 * followed by other operations not including right shifts or division. 
 * Function sra performs an arithmetic right shift using a logical right shift 
 * (given by value xsrl), followed by other operations not including right 
 * shifts or division. You may use the computation 8 * sizeof(int) to 
 * determine w, the number of bits in data type int. The shift amount k can 
 * range from 0 to w - 1.
 *
*/

#include <stdio.h>
#include <assert.h>
#include <limits.h>

/*
 * First perform an arithmetic right shift by casting to signed int: (int)x >> k.
 * This may fill the high bits with sign bits (1s) if the interpreted signed value
 * is negative.
 * Then create mask, which ahs 1s in the low (w-k) positions and 0s in the high k positions.
 * The mask is (~0u) >> k which is defined for k in 0..w-1 and never shifts by w (shifting 
 * unsigned right by k where 0 <= k < w is safe).
 * Then finally return the result with the mask to clear any sign-extended 1s.
*/
unsigned srl(unsigned x, int k) {
	int w = sizeof(int) << 3;		/* number of bits in int */
	/* xsra: arithmetic right shift of bit pattern of x */
	int xsra = (int)x >> k;			/* arithmetic right shift (may sign-extend) */

	/* mask: lower (w - k) bits set to 1, high k bits 0.
	 * Using unsigned ~0u and right-shifting by k is safe for k in 0 .. w-1 */
	unsigned mask = ~0u >> k;		/* e.g. if k = 4, mask = 0x0FFF... */

	return (unsigned)xsra & mask;		/* clear any sign-extended 1s, yield logical shift */
}

/* 
 * Returns x arithmeticaly right-shifted by k
 *
 * Start by using logical right shift on unsigned: (unsigned)x >> k
 * Then, if x is negative, OR in a mask that sets the top k bits to 1.
*/
int sra(int x, int k) {
	int w = sizeof(int) << 3;

	/* k==0 -> no shift */
	if (k == 0) {
		return x;
	}

	/* Logical right shift using unsigned conversion */
	unsigned xsrl = (unsigned)x >> k;

	/* Mask with top k bits set (for w==32 and k==4 -> 0xF0000000) */
	unsigned mask = (~0u) << (w - k);

	/* If x is negative, need to fill top k bits with 1; otherwise leave xsrl unchanged */
	if (x < 0) {
		xsrl |= mask;
	}

	return (int)xsrl;
}

int main(int argc, char* argv[]) {
	
	int w = sizeof(int) << 4;

	unsigned u1 = 0x12345678u;
	unsigned u2 = 0x87654321u;		/* top bit set in 32-bit view */
	int i1 = 0x12345678;			/* positive */
	int i2 = (int)0x87654321u;		/* may be negative depending on width; treats top bit = 1 */

	/* testing srl (logical) against the standard unsigned >> (which is defined to be logical) */
	assert(srl(u1, 0) == (u1 >> 0));
	assert(srl(u1, 4) == (u1 >> 4));
	assert(srl(u1, w - 1) == (u1 >> (w - 1)));

	assert(srl(u2, 0) == (u2 >> 0));
	assert(srl(u2, 4) == (u2 >> 4));
	assert(srl(u2, w - 1) == (u2 >> (w - 1)));

	/* testing sra (arithmetic) by computing the "expected" arithmetic result in a portable way.
	 * and by expected, I mean we perform a logical shift on unsigned, then if original x < 0 OR in mask.
	*/

	for (int k = 0; k < w; ++k) {
		/* expected for i1 */
		unsigned xsrl_i1 = (unsigned)i1 >> k;
		unsigned expected_i1 = xsrl_i1;
		assert(sra(i1, k) == (int)expected_i1);		/* i1 >= 0, no sign-fill */

		/* expected for i2 */
		unsigned xsrl_i2 = (unsigned)i2 >> k;
		unsigned mask = (k == 0) ? 0u : ((~0u) << (w - k));
		unsigned expected_i2 = (i2 < 0) ? (xsrl_i2 | mask) : xsrl_i2;
		assert(sra(i2, k) == (int)expected_i2);
	}

	printf("All tests passed.\n");
	return 0;
}	
