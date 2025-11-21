#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE 100

int main(void) {
    int valeurs[TAILLE];
    srand((unsigned)time(NULL));

    for (int i = 0; i < TAILLE; ++i) {
        valeurs[i] = rand() % 200 - 50;
    }

    puts("Tableau généré :");
    for (int i = 0; i < TAILLE; ++i) {
        printf("%d%s", valeurs[i], (i + 1 == TAILLE) ? "\n" : " ");
    }

    int cible = 0;
    printf("Entrez l'entier que vous souhaitez chercher : ");
    if (scanf("%d", &cible) != 1) {
        puts("Entrée invalide.");
        return 1;
    }

    int trouve = 0;
    for (int i = 0; i < TAILLE; ++i) {
        if (valeurs[i] == cible) {
            trouve = 1;
            break;
        }
    }

    printf("Résultat : %s\n", trouve ? "entier présent" : "entier absent");
    return 0;
}

