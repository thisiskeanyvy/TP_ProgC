#include <stdio.h>

static void afficher_triangle_for(int compteur) {
    printf("Triangle avec for (compteur=%d)\n", compteur);
    for (int ligne = 0; ligne < compteur; ++ligne) {
        for (int colonne = 0; colonne <= ligne; ++colonne) {
            int bord = (colonne == 0) || (colonne == ligne) || (ligne == compteur - 1);
            putchar(bord ? '*' : '#');
            putchar(' ');
        }
        putchar('\n');
    }
}

static void afficher_triangle_while(int compteur) {
    printf("\nTriangle avec while (compteur=%d)\n", compteur);
    int ligne = 0;
    while (ligne < compteur) {
        int colonne = 0;
        while (colonne <= ligne) {
            int bord = (colonne == 0) || (colonne == ligne) || (ligne == compteur - 1);
            putchar(bord ? '*' : '#');
            putchar(' ');
            ++colonne;
        }
        putchar('\n');
        ++ligne;
    }
}

int main(void) {
    const int compteur = 5; // doit rester strictement inférieur à 10
    afficher_triangle_for(compteur);
    afficher_triangle_while(compteur);
    return 0;
}

