// learning about Boolean Algebra and bit-level operations in C.
// this is an interesting example of a practical use-case.
// "^" represents the Boolean XOR operation. "one or the other, but not both."
// this function takes two pointers, and, using solely the XOR operation, 
// swaps their values. 
//
// we do not need a third location to temporarily store one value while moving 
// the other.
//
// there is no performance advantage to this; it's just a fun example.
//
// say &x = 0000 and &y = 1111.
// *y = *x ^ *y = 0000 ^ 1111 = 1111 
// *x = *x ^ *y = 0000 ^ 1111 = 1111
// *y = *x ^ *y = 1111 ^ 1111 = 0000
// and the values are swapped!

void inplace_swap(int *x, int *y) {
	*y = *x ^ *y;
	*x = *x ^ *y;
	*y = *x ^ *y;
}

// now, here's a function that will reverse the elements of an array by 
// swapping elements from opposite ends, working toward the middle.
// we can actually use the previous inplace_swap function for this.
// however, by itself, this function only works as expected for arrays of
// even length.
// if given an array with elements 1, 2, 3, 4, and 5, for example, the output 
// becomes 5, 4, 0, 2, and 1. in fact, for arrays of odd length, the middle 
// value will always be set to 0.
// this is because of our use of inplace_swap. for odd-length arrays, 
// eventually, a call will be made to inplace_swap where x and y both point 
// to the same location. and if we compute *x ^ *y when they are equal, we'll
// get 0. 0 is then stored as the middle element of the array, and the 
// subsequent steps of the for loop keep setting this element to 0. 
// in short, inplace_swap implicitly assumes that x and y point to different 
// locations.
//
// to fix this, we can simply change reverse_array as noted in the below 
// comment, by changing <= to <, since there is no need to swap the middle 
// element with itself.
void reverse_array(int a[], int count) {
	int first, last;
	for (first = 0, last = count - 1;
			// change to <
			first <= last;
			first++, last--)
			inplace_swap(&a[first], &a[last]);
}
