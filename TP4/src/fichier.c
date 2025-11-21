#include "fichier.h"
#include <stdio.h>

int lire_fichier(const char *nom_de_fichier) {
    if (!nom_de_fichier) {
        return 0;
    }

    FILE *fichier = fopen(nom_de_fichier, "r");
    if (!fichier) {
        perror("Impossible d'ouvrir le fichier en lecture");
        return 0;
    }

    char ligne[512];
    printf("Contenu de %s :\n", nom_de_fichier);
    while (fgets(ligne, sizeof(ligne), fichier)) {
        fputs(ligne, stdout);
    }
    if (ferror(fichier)) {
        perror("Erreur lors de la lecture");
        fclose(fichier);
        return 0;
    }

    fclose(fichier);
    return 1;
}

int ecrire_dans_fichier(const char *nom_de_fichier, const char *message) {
    if (!nom_de_fichier || !message) {
        return 0;
    }

    FILE *fichier = fopen(nom_de_fichier, "a");
    if (!fichier) {
        perror("Impossible d'ouvrir le fichier en ecriture");
        return 0;
    }

    fprintf(fichier, "%s\n", message);
    if (ferror(fichier)) {
        perror("Erreur lors de l'ecriture");
        fclose(fichier);
        return 0;
    }

    fclose(fichier);
    return 1;
}

