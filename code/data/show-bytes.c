#include <stdio.h>

// byte_pointer is a pointer to an object of type unsigned char.
// it references a sequence of bytes where each byte is considered to be a 
// nonnegative integer.
typedef unsigned char *byte_pointer;

// show_bytes is given the address of a sequence of bytes (indicated by a 
// byte_pointer) and a byte count. 
// the byte count is specified as having data type size_t. 
// show_bytes prints the individual bytes in hexadecimal.
// %.2x indicates that an integer should be printed in hexcadecimal with 
// at least 2 digits.
void show_bytes(byte_pointer start, size_t len) {
	int i;
	for (i = 0; i < len; i++)
		printf(" %.2x", start[i]);
	printf("\n");
}

// the next functions (show_int, show_float, and show_pointer) demonstrate how 
// to use show_bytes to print the byte representations of C program objects 
// of type int, float, and void *. 
// they simply pass show_bytes a pointer &x to their argument x, casting the 
// pointer to be of type unsigned char *. 
//
// this cast indicates to the compiler that the program should consider the 
// pointer to be to a sequence of bytes rather than to an object of the 
// original data type (like an integer). 
//
// they all use sizeof to determine the number of bytes used by the object. 
void show_int(int x) {
	show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x) {
	show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) {
	show_bytes((byte_pointer) &x, sizeof(void *));
}

void test_show_bytes(int val) {
	int ival = val;
	float fval = (float) ival;
	int *pval = &ival;
	show_int(ival);
	show_float(fval);
	show_pointer(pval);
}

// here's a simple main() function testing it out.
// 12,345 has a hex value of 0x00003039.
// for the integer data (show_int), you'll get identical results, no matter 
// what machine you run this on, except for the byte ordering.
// if you're running a little-endian machine (Linux 32, Windows, Linux 64), 
// you'll see the least significant byte value of 0x39 printed first.
// same goes for the float (show_float) data. 
// however, the pointer values will be completely different, as different 
// machine/operating systems will use different conventions for storage 
// allocation.
// one thing to note, though, is that Linux 32 and Windows machines will use 
// 4-byte addresses, whereas Linux 64 will use 8-byte addresses.
int main() {
	test_show_bytes(12345);
	return 0;
}
