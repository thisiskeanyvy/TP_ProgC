#include <stdio.h>

#define NB_PHRASES 10
#define TAILLE_PHRASE 128

static int comparer(const char *a, const char *b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return 0;
        }
        ++i;
    }
    return a[i] == '\0' && b[i] == '\0';
}

int main(void) {
    const char phrases[NB_PHRASES][TAILLE_PHRASE] = {
        "Bonjour, comment ca va ?",
        "Le temps est magnifique aujourd'hui.",
        "C'est une belle journee.",
        "La programmation en C est amusante.",
        "Les tableaux en C sont puissants.",
        "Les pointeurs en C peuvent etre deroutants.",
        "Il fait beau dehors.",
        "La recherche dans un tableau est interessante.",
        "Les structures de donnees sont importantes.",
        "Programmer en C, c'est genial."};

    char recherche[TAILLE_PHRASE];
    printf("Entrez la phrase a chercher : ");
    if (fgets(recherche, sizeof(recherche), stdin) == NULL) {
        puts("Lecture invalide.");
        return 1;
    }

    int longueur = 0;
    while (recherche[longueur] != '\0') {
        if (recherche[longueur] == '\n') {
            recherche[longueur] = '\0';
            break;
        }
        ++longueur;
    }

    int trouve = 0;
    for (int i = 0; i < NB_PHRASES; ++i) {
        if (comparer(recherche, phrases[i])) {
            trouve = 1;
            break;
        }
    }

    puts(trouve ? "Phrase trouvee" : "Phrase non trouvee");
    return 0;
}

