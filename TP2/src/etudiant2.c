#include <stdio.h>
#include <string.h>

#define NB_ETUDIANTS 5

struct etudiant {
    char nom[32];
    char prenom[32];
    char adresse[64];
    float note_prog;
    float note_sys;
};

static void initialiser(struct etudiant *et, const char *nom, const char *prenom,
                        const char *adresse, float note_prog, float note_sys) {
    strcpy(et->nom, nom);
    strcpy(et->prenom, prenom);
    strcpy(et->adresse, adresse);
    et->note_prog = note_prog;
    et->note_sys = note_sys;
}

int main(void) {
    struct etudiant etudiants[NB_ETUDIANTS];

    initialiser(&etudiants[0], "Dupont", "Marie",
                "20 Boulevard Niels Bohr, Lyon", 16.5f, 12.1f);
    initialiser(&etudiants[1], "Martin", "Pierre",
                "22 Boulevard Niels Bohr, Lyon", 14.0f, 14.1f);
    initialiser(&etudiants[2], "Bernard", "Luc",
                "5 rue Victor Hugo, Paris", 13.0f, 11.5f);
    initialiser(&etudiants[3], "Durand", "Sophie",
                "18 avenue des Frères Lumière, Lyon", 19.0f, 17.0f);
    initialiser(&etudiants[4], "Petit", "Hugo",
                "3 allée des Platanes, Grenoble", 12.5f, 15.0f);

    for (int i = 0; i < NB_ETUDIANTS; ++i) {
        printf("Étudiant.e %d\n", i + 1);
        printf("Nom : %s\n", etudiants[i].nom);
        printf("Prénom : %s\n", etudiants[i].prenom);
        printf("Adresse : %s\n", etudiants[i].adresse);
        printf("Note Programmation : %.1f\n", etudiants[i].note_prog);
        printf("Note Système : %.1f\n\n", etudiants[i].note_sys);
    }

    return 0;
}

