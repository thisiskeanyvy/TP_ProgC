#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>

#define TAILLE 12

static void afficher_ints(const int *depart) {
    const int *p = depart;
    for (size_t i = 0; i < TAILLE; ++i, ++p) {
        printf("%d%s", *p, (i + 1 == TAILLE) ? "\n" : ", ");
    }
}

static void afficher_floats(const float *depart) {
    const float *p = depart;
    for (size_t i = 0; i < TAILLE; ++i, ++p) {
        printf("%.2f%s", *p, (i + 1 == TAILLE) ? "\n" : ", ");
    }
}

int main(void) {
    int entiers[TAILLE];
    float reels[TAILLE];

    srand((unsigned)time(NULL));

    int *pi = entiers;
    for (size_t i = 0; i < TAILLE; ++i, ++pi) {
        *pi = rand() % 100;
    }

    float *pf = reels;
    for (size_t i = 0; i < TAILLE; ++i, ++pf) {
        *pf = (float)(rand() % 1000) / 10.0f;
    }

    puts("Tableau d'entiers (avant) :");
    afficher_ints(entiers);
    puts("Tableau de flottants (avant) :");
    afficher_floats(reels);

    size_t position = 0;
    for (int *p = entiers; p < entiers + TAILLE; ++p, ++position) {
        if (position % 2 == 0) {
            *p *= 3;
        }
    }

    position = 0;
    for (float *p = reels; p < reels + TAILLE; ++p, ++position) {
        if (position % 2 == 0) {
            *p *= 3.0f;
        }
    }

    puts("\nTableau d'entiers (après) :");
    afficher_ints(entiers);
    puts("Tableau de flottants (après) :");
    afficher_floats(reels);

    return 0;
}

