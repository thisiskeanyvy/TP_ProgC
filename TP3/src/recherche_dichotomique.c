#include <stdio.h>

#define TAILLE 100

static int recherche(int tableau[], int cible) {
    int gauche = 0;
    int droite = TAILLE - 1;

    while (gauche <= droite) {
        int milieu = gauche + (droite - gauche) / 2;
        if (tableau[milieu] == cible) {
            return 1;
        }
        if (tableau[milieu] < cible) {
            gauche = milieu + 1;
        } else {
            droite = milieu - 1;
        }
    }
    return 0;
}

int main(void) {
    int valeurs[TAILLE];
    for (int i = 0; i < TAILLE; ++i) {
        valeurs[i] = i * 3;
    }

    puts("Tableau trié :");
    for (int i = 0; i < TAILLE; ++i) {
        printf("%d%s", valeurs[i], (i + 1 == TAILLE) ? "\n" : " ");
    }

    int cible = 0;
    printf("Entrez l'entier à chercher : ");
    if (scanf("%d", &cible) != 1) {
        puts("Entrée invalide.");
        return 1;
    }

    int present = recherche(valeurs, cible);
    printf("Résultat : %s\n", present ? "entier présent" : "entier absent");
    return 0;
}

