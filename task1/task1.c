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

// Return 1 if x is negative or 0 otherwise
int sign(int x) {
	return x >> 31;
}

// Returns 0 if x fits within n bits or some other number otherwise
int fitBits(int x, int n) {
	return x >> n;
}

// Gets n-th byte of x
int getByte(int x, int n) {
	// shift => 8 * n
	int shift = (n << 3);
	return (x >> shift) & 255;
}
	
int main() {
	srand(time(NULL));
	int op1, op2, i;
	for (i = 0; i < TEST_COUNT; i++) {
		op1 = rand(), op2 = rand();
		assert(bitAnd(op1, op2) == (op1 & op2));
		assert(bitOr(op1, op2) == (op1 | op2));
		assert(bitXor(op1, op2) == (op1 ^ op2));
		assert(thirdBits() == 0b00100100100100100100100100100100);
		assert(sign(op1) == (op1 < 0));
		assert((fitBits(op1, op2 % 31) == 0) == (abs(op1) <= (int) pow(2, op2 % 31)));
		assert(getByte(op1, op2 % 4) == ((unsigned char *)(&op1))[op2 % 4]);
	}
	printf("%d iterations OK\nAll test have been passed", TEST_COUNT); 
	return 0;
}
