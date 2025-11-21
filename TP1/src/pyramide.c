#include <stdio.h>

static void afficher_pyramide(int n) {
    for (int ligne = 1; ligne <= n; ++ligne) {
        for (int espace = 0; espace < n - ligne; ++espace) {
            putchar(' ');
        }
        for (int croissant = 1; croissant <= ligne; ++croissant) {
            printf("%d", croissant);
        }
        for (int decroissant = ligne - 1; decroissant >= 1; --decroissant) {
            printf("%d", decroissant);
        }
        putchar('\n');
    }
    puts("Pyramide générée avec succès.");
}

int main(void) {
    const int n = 5;
    afficher_pyramide(n);
    return 0;
}

