#include <stdio.h>

typedef struct float_repr float_repr;
struct float_repr {
	int sign, exp, mantis;
};

void print_float_repr(float_repr repr) {
	int e = repr.exp - 127;
    float m = (float) repr.mantis / (float) 0x800000 + 1;
    if (repr.exp == 0xff) {
		if (repr.mantis)
			printf("nan\n");
		else
			printf((repr.sign ? "-inf\n" : "+inf\n"));
    }
	else
		printf("%c2^(%d)*%f\n", (repr.sign ? '-' : '+'), e, m);
}

float_repr floatBits1(float value) {
    union {
        float f;
        int i;
    } some_union;
    some_union.f = value;
    float_repr res = {
		.sign = (some_union.i >> 31) & 1,
		.exp = (some_union.i >> 23) & 0xff,
		.mantis = some_union.i & 0x7fffff
	};
    return res;
}

float_repr floatBits2(float value) {
    union {
        float f;
        struct {
            unsigned int mantis : 23;
            unsigned int exp : 8;
            unsigned int sign : 1;
        } bit_field;
    } some_union;
    some_union.f = value;
    float_repr res = {
		.sign   = some_union.bit_field.sign,
		.exp    = some_union.bit_field.exp,
		.mantis = some_union.bit_field.mantis
	};
    return res;
}

float_repr floatBits3(float value) {
    int *p = (int *) (&value);
    float_repr res = {
		.sign = (*p >> 31) & 1,
		.exp = (*p >> 23) & 0xff,
		.mantis = *p & 0x7fffff
	};
    return res;
}

int main() {
	float tests[] = {1.0, 0.5, 1e9 + 7, 0.0 / 0.0, 1.0 / 0.0, -1.0 / 0.0};
	int i;
	for (i = 0; i < sizeof(tests) / sizeof(float); i++) {
		printf("Test %d: %f\n", i + 1, tests[i]);
		float_repr t1 = floatBits1(tests[i]); 
		float_repr t2 = floatBits2(tests[i]);
		float_repr t3 = floatBits3(tests[i]);
		print_float_repr(t1);
		print_float_repr(t2);
		print_float_repr(t3);
		printf("==============\n");
	}
	return 0;
}
