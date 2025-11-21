#include <stdio.h>
#include <string.h>
#include <stddef.h>

static void afficher_etat(const char *nom, void *ptr, size_t taille) {
    const unsigned char *octets = (const unsigned char *)ptr;
    printf("%-20s adresse=%p valeur=0x", nom, (void *)ptr);
    for (size_t i = 0; i < taille; ++i) {
        printf("%02X", octets[taille - 1 - i]);
    }
    putchar('\n');
}

int main(void) {
    signed char c = -42;
    unsigned char uc = 200;
    short s = -1234;
    unsigned short us = 54321;
    int i = -123456;
    unsigned int ui = 123456u;
    long l = -987654321L;
    long long ll = -1234567890123456789LL;
    float f = 3.14f;
    double d = 2.718281828459045;
    long double ld = 1.6180339887498948482L;

    printf("Avant manipulation\n");
    afficher_etat("signed char", &c, sizeof(c));
    afficher_etat("unsigned char", &uc, sizeof(uc));
    afficher_etat("short", &s, sizeof(s));
    afficher_etat("unsigned short", &us, sizeof(us));
    afficher_etat("int", &i, sizeof(i));
    afficher_etat("unsigned int", &ui, sizeof(ui));
    afficher_etat("long", &l, sizeof(l));
    afficher_etat("long long", &ll, sizeof(ll));
    afficher_etat("float", &f, sizeof(f));
    afficher_etat("double", &d, sizeof(d));
    afficher_etat("long double", &ld, sizeof(ld));

    signed char *pc = &c;
    unsigned char *puc = &uc;
    short *ps = &s;
    unsigned short *pus = &us;
    int *pi = &i;
    unsigned int *pui = &ui;
    long *pl = &l;
    long long *pll = &ll;
    float *pf = &f;
    double *pd = &d;
    long double *pld = &ld;

    *pc += 1;
    *puc -= 1;
    *ps += 10;
    *pus -= 10;
    *pi *= -1;
    *pui += 1000;
    *pl -= 1000000;
    *pll += 123456789LL;
    *pf *= 2.0f;
    *pd /= 2.0;
    *pld += 0.5L;

    printf("\nAprès manipulation\n");
    afficher_etat("signed char", &c, sizeof(c));
    afficher_etat("unsigned char", &uc, sizeof(uc));
    afficher_etat("short", &s, sizeof(s));
    afficher_etat("unsigned short", &us, sizeof(us));
    afficher_etat("int", &i, sizeof(i));
    afficher_etat("unsigned int", &ui, sizeof(ui));
    afficher_etat("long", &l, sizeof(l));
    afficher_etat("long long", &ll, sizeof(ll));
    afficher_etat("float", &f, sizeof(f));
    afficher_etat("double", &d, sizeof(d));
    afficher_etat("long double", &ld, sizeof(ld));

    return 0;
}

