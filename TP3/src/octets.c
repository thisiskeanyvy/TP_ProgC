#include <stdio.h>
#include <stddef.h>

static void afficher_octets(const void *ptr, size_t taille) {
    const unsigned char *octets = (const unsigned char *)ptr;
    for (size_t i = 0; i < taille; ++i) {
        printf("%02X ", octets[i]);
    }
    putchar('\n');
}

int main(void) {
    short s = 515;
    int i = 0x01020304;
    long l = 0x0102030405060708;
    float f = 3.14f;
    double d = 2.718281828459045;
    long double ld = 1.6180339887498948482L;

    puts("Octets de short :");
    afficher_octets(&s, sizeof(s));
    puts("\nOctets de int :");
    afficher_octets(&i, sizeof(i));
    puts("\nOctets de long :");
    afficher_octets(&l, sizeof(l));
    puts("\nOctets de float :");
    afficher_octets(&f, sizeof(f));
    puts("\nOctets de double :");
    afficher_octets(&d, sizeof(d));
    puts("\nOctets de long double :");
    afficher_octets(&ld, sizeof(ld));

    return 0;
}

