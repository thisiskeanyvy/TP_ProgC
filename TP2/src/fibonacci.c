#include <stdio.h>

int main(void) {
    unsigned int n = 10;

    printf("Entrez le nombre de termes à générer : ");
    if (scanf("%u", &n) != 1 || n == 0) {
        puts("Entrée invalide.");
        return 1;
    }

    unsigned long long precedent = 0;
    unsigned long long courant = 1;

    printf("Suite de Fibonacci (%u termes) : ", n);
    for (unsigned int index = 0; index < n; ++index) {
        if (index == 0) {
            printf("%llu", precedent);
        } else if (index == 1) {
            printf(", %llu", courant);
        } else {
            unsigned long long suivant = precedent + courant;
            printf(", %llu", suivant);
            precedent = courant;
            courant = suivant;
        }
    }
    putchar('\n');

    return 0;
}

