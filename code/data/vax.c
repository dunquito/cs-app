// The Digital Equipment VAX computer used "bit set" and "bit clear" 
// operations, rather than the Boolean AND and OR.
//
// Both instructions take a data word x, and a mask word m, then generate a 
// result z consisting of the bits of x modified according to the bits of m.
//
// With "bis" (bit set), the modification involves setting z to 1 at each bit 
// position where m is 1. 
//
// "bic" (bit clear) sets z to 0 at each position where m is 1. 
//
// So this is my attempt to implement those functions using only OR and XOR, 
// no other C operations.

// "bit set" is equivalent to Boolean OR--a bit is set in z if either this bit
// is set in x or it is set in m.
int bis(int x, int m) {
	int z = x | m;
	return z;
}

// "bit clear" is equivalent to x & ~m; we want the result to equal 1 only when
// the corresponding bit of x is 1 and of m is 0.
int bic(int x, int m) {
	int z = x & ~m;
	return z;
}	

// Compute x|y using only calls to functions bis and bic
int bool_or(int x, int y) {
	int result = bis(x, y);
	return result;
}

// Compute x^y using only calls to functions bis and bic
int bool_xor(int x, int y) {
	int result = bis(bic(x, y), bic(y, x));
	return result;
}
