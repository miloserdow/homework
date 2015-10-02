#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TEST_COUNT 100

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

int main() {
	srand(time(NULL));
	int op1, op2, i;
	// currenly it does not check last 2 functions
	for (i = 0; i < TEST_COUNT; i++) {
		op1 = rand(), op2 = rand();
	
		assert(bitAnd(op1, op2) == (op1 & op2));
		assert(bitOr(op1, op2) == (op1 | op2));
		assert(bitXor(op1, op2) == (op1 ^ op2));
		assert(sign(op1) == (op1 < 0 ? -1 : (op1 == 0 ? 0: 1)));

		assert(thirdBits() == 0b00100100100100100100100100100100);
		assert(fitBits(op1, op2 % 31) == (abs(op1) <= (int) pow(2, op2 % 31)));
		assert(getByte(op1, op2 % 4) == ((unsigned char *)(&op1))[op2 % 4]);
		
		assert(isPowerOf2(pow(2, op1 % 31)));
		assert(!isPowerOf2(pow(2, op1 % 31) - op2 % 100000 - 1));
	}
	printf("%d iterations OK\nAll tests have been passed\n", TEST_COUNT); 
	return 0;
}
