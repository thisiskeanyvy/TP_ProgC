#include <stdio.h>

int main(void) {
    printf("Taille de signed char      : %zu octets\n", sizeof(signed char));
    printf("Taille de unsigned char    : %zu octets\n", sizeof(unsigned char));
    printf("Taille de signed short     : %zu octets\n", sizeof(signed short));
    printf("Taille de unsigned short   : %zu octets\n", sizeof(unsigned short));
    printf("Taille de signed int       : %zu octets\n", sizeof(signed int));
    printf("Taille de unsigned int     : %zu octets\n", sizeof(unsigned int));
    printf("Taille de signed long      : %zu octets\n", sizeof(signed long));
    printf("Taille de unsigned long    : %zu octets\n", sizeof(unsigned long));
    printf("Taille de signed long long : %zu octets\n", sizeof(signed long long));
    printf("Taille de unsigned long long : %zu octets\n",
           sizeof(unsigned long long));
    printf("Taille de float            : %zu octets\n", sizeof(float));
    printf("Taille de double           : %zu octets\n", sizeof(double));
    printf("Taille de long double      : %zu octets\n", sizeof(long double));

    return 0;
}

