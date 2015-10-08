#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TEST_COUNT 100

// Returns 1 on Little Endian arch. and 0 on Big Endian one
int endian_check() {
	int bytes = 1;
	return 0x0000000f & bytes; 
}

// Bitwise AND without &
int bitAnd(int a, int b) {
	return ~(~a | ~b);
}

// Bitwise OR without |
int bitOr(int a, int b) {
	return ~(~a & ~b);
}

// Bitwise XOR using only ~ &
int bitXor(int a, int b) {
	int res = ~(~(a & ~b) & ~(~a & b));
	return res;
}

// Gets a magic sequence ...100100
int thirdBits() {
	return (36 << 24) | (146 << 16) | (73 << 8) | 36;
}

// Return -1 if x is negative, 1 if positive or 0 otherwise
int sign(int x) {
	return ((x >> 31) | (!!x));
}

// Returns 1 if x fits within n bits or some 0 otherwise
// (yet it works only with positive numbers)
int fitBits(int x, int n) {
	return !(x >> n);
}

// Gets n-th byte of x
int getByte(int x, int n) {
	// shift => 8 * n
	int shift = (n << 3);
	return (x >> shift) & 255;
}

// Returns 1 if x is a power of 2 and 0 otherwise
int isPowerOf2(int x) {
	return x && !(x & (x - 1));
}

// returns 1 if adding b to a will not lead to overflow of int
// (no autotesting for this)
int addOk(int a, int b) {
	int s = a + b;
	int a_sign = a >> 31, 
	    b_sign = b >> 31,
	    s_sign = s >> 31;
	return !((a_sign ^ s_sign) & (b_sign ^ s_sign));
}

// returns 1 if (!x) or 0 otherwise
int bang(int x) {
	int t = (x | (~x + 1)) >> 31;
	return t + 1;
}

// performs bitshift on x (math. shift)
// (no autotesting for this)
int logicalShift(int x, int n) {
	return ((x >> n) & ((1 << (~n + 33)) + ~0));
}

// as (x ? y : z)
int conditional(int x, int y, int z) {
	int t = (x | (~x + 1)) >> 31;
	int r = (t & y) | (~t & z);
	return r;
}

int main() {
	srand(time(NULL));
	int op1, op2, i;
	
	for (i = 0; i < TEST_COUNT; i++) {
		op1 = rand(), op2 = rand();
	
		assert(bitAnd(op1, op2) == (op1 & op2));
		assert(bitOr(op1, op2) == (op1 | op2));
		assert(bitXor(op1, op2) == (op1 ^ op2));
		assert(sign(op1) == (op1 < 0 ? -1 : (op1 == 0 ? 0: 1)));

		assert(fitBits(op1, op2 % 31) == (abs(op1) <= (int) pow(2, op2 % 31)));
		assert(getByte(op1, op2 % 4) == ((unsigned char *)(&op1))[op2 % 4]);
		
		assert(isPowerOf2(pow(2, op1 % 31)));
		assert(!isPowerOf2(pow(2, op1 % 31) - op2 % 100000 - 1));
		
		assert(!op1 == bang(op1));
		assert((op1 ? op1 : op2) == conditional(op1, op1, op2));
	}

	assert(thirdBits() == 0b00100100100100100100100100100100);
	
	// checking endian_check() function
	unsigned int x = 0x76543210;
	char *c = (char*) &x;
	assert((*c == 0x10) == endian_check());
	
	printf("%d iterations OK\nAll tests have been passed\n", TEST_COUNT); 
	return 0;
}
