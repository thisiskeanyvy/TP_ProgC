#include <stdio.h>

int main(void) {
    signed char c = -42;
    unsigned char uc = 200;

    signed short s = -1234;
    unsigned short us = 54321;

    signed int i = -123456;
    unsigned int ui = 123456u;

    signed long l = -987654321L;
    unsigned long ul = 1987654321UL;

    signed long long ll = -9223372036854775807LL;
    unsigned long long ull = 1844674407370955161ULL;

    float f = 3.14f;
    double d = 2.718281828459045;
    long double ld = 1.6180339887498948482L;

    printf("signed char : %d\n", c);
    printf("unsigned char : %u\n", uc);
    printf("signed short : %hd\n", s);
    printf("unsigned short : %hu\n", us);
    printf("signed int : %d\n", i);
    printf("unsigned int : %u\n", ui);
    printf("signed long : %ld\n", l);
    printf("unsigned long : %lu\n", ul);
    printf("signed long long : %lld\n", ll);
    printf("unsigned long long : %llu\n", ull);
    printf("float : %.2f\n", f);
    printf("double : %.6f\n", d);
    printf("long double : %.10Lf\n", ld);

    return 0;
}

