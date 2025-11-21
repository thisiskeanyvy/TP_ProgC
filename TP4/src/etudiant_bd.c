#include "fichier.h"
#include <stdio.h>
#include <string.h>

#define NB_ETUDIANTS 5

struct etudiant {
    char nom[32];
    char prenom[32];
    char adresse[128];
    float note_prog;
    float note_sys;
};

static void vider_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int main(void) {
    struct etudiant etudiants[NB_ETUDIANTS];

    for (int i = 0; i < NB_ETUDIANTS; ++i) {
        printf("Etudiant.e %d\n", i + 1);
        printf("Nom : ");
        scanf(" %31s", etudiants[i].nom);
        printf("Prenom : ");
        scanf(" %31s", etudiants[i].prenom);
        printf("Adresse : ");
        scanf(" %127[^\n]", etudiants[i].adresse);
        printf("Note Programmation : ");
        scanf("%f", &etudiants[i].note_prog);
        printf("Note Systeme : ");
        scanf("%f", &etudiants[i].note_sys);
        vider_buffer();
    }

    const char *fichier = "etudiant.txt";
    FILE *reset = fopen(fichier, "w");
    if (reset) {
        fclose(reset);
    }

    char ligne[256];
    for (int i = 0; i < NB_ETUDIANTS; ++i) {
        snprintf(ligne, sizeof(ligne), "%s;%s;%s;%.2f;%.2f", etudiants[i].nom,
                 etudiants[i].prenom, etudiants[i].adresse,
                 etudiants[i].note_prog, etudiants[i].note_sys);
        ecrire_dans_fichier(fichier, ligne);
    }

    puts("Les details ont ete enregistres dans etudiant.txt");
    return 0;
}

