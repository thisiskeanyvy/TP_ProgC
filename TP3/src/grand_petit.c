#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE 100

int main(void) {
    int valeurs[TAILLE];

    srand((unsigned)time(NULL));
    for (int i = 0; i < TAILLE; ++i) {
        valeurs[i] = rand() % 1000 + 1;
    }

    int minimum = valeurs[0];
    int maximum = valeurs[0];
    for (int i = 1; i < TAILLE; ++i) {
        if (valeurs[i] < minimum) {
            minimum = valeurs[i];
        }
        if (valeurs[i] > maximum) {
            maximum = valeurs[i];
        }
    }

    printf("Le numéro le plus petit est : %d\n", minimum);
    printf("Le numéro le plus grand est : %d\n", maximum);

    return 0;
}

