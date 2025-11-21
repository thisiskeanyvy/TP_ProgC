#include <stdio.h>
#include <string.h>
#include <stddef.h>

static void retirer_newline(char *texte) {
    size_t len = strlen(texte);
    if (len > 0 && texte[len - 1] == '\n') {
        texte[len - 1] = '\0';
    }
}

static int compter_occurrences(const char *texte, const char *motif) {
    int total = 0;
    size_t len_motif = strlen(motif);
    if (len_motif == 0) {
        return 0;
    }

    const char *position = texte;
    while ((position = strstr(position, motif)) != NULL) {
        ++total;
        position += len_motif;
    }
    return total;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Utilisation : %s <fichier>\n", argv[0]);
        return 1;
    }

    const char *nom_fichier = argv[1];
    FILE *fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        perror("Impossible d'ouvrir le fichier");
        return 1;
    }

    char recherche[256];
    printf("Entrez la phrase a rechercher : ");
    if (!fgets(recherche, sizeof(recherche), stdin)) {
        puts("Lecture interrompue.");
        fclose(fichier);
        return 1;
    }
    retirer_newline(recherche);

    if (recherche[0] == '\0') {
        puts("Phrase vide.");
        fclose(fichier);
        return 1;
    }

    char ligne[512];
    int numero_ligne = 1;
    int trouve_total = 0;
    puts("Resultats de la recherche :");
    while (fgets(ligne, sizeof(ligne), fichier)) {
        int occurrences = compter_occurrences(ligne, recherche);
        if (occurrences > 0) {
            printf("Ligne %d, %d fois\n", numero_ligne, occurrences);
            trouve_total += occurrences;
        }
        ++numero_ligne;
    }

    if (trouve_total == 0) {
        puts("Aucune occurrence trouvee.");
    }

    fclose(fichier);
    return 0;
}

