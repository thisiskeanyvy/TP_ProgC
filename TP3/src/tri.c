#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE 100

static void afficher_tableau(const int *tableau) {
    for (int i = 0; i < TAILLE; ++i) {
        printf("%d%s", tableau[i], (i + 1 == TAILLE) ? "\n" : " ");
    }
}

static void tri_insertion(int *tableau) {
    for (int i = 1; i < TAILLE; ++i) {
        int cle = tableau[i];
        int j = i - 1;
        while (j >= 0 && tableau[j] > cle) {
            tableau[j + 1] = tableau[j];
            --j;
        }
        tableau[j + 1] = cle;
    }
}

int main(void) {
    int valeurs[TAILLE];
    srand((unsigned)time(NULL));
    for (int i = 0; i < TAILLE; ++i) {
        valeurs[i] = (rand() % 200) - 50;
    }

    puts("Tableau non trié :");
    afficher_tableau(valeurs);

    tri_insertion(valeurs);

    puts("\nTableau trié :");
    afficher_tableau(valeurs);

    return 0;
}

