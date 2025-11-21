#include <stdio.h>
#include <stddef.h>

int main(void) {
    const char *noms[] = {"Dupont", "Martin", "Bernard", "Durand", "Petit"};
    const char *prenoms[] = {"Alice", "Bruno", "Claire", "David", "Eva"};
    const char *adresses[] = {
        "10 rue de la Paix, Paris",
        "25 avenue Victor Hugo, Lyon",
        "5 chemin des Fleurs, Nice",
        "48 boulevard Voltaire, Lille",
        "2 impasse des Cerisiers, Nantes"};
    const float note_prog[] = {15.5f, 12.0f, 17.0f, 9.5f, 14.0f};
    const float note_sys[] = {13.0f, 16.5f, 11.0f, 10.0f, 15.5f};
    const size_t nb_etudiants = sizeof(noms) / sizeof(noms[0]);

    for (size_t i = 0; i < nb_etudiants; ++i) {
        printf("Étudiant.e %zu\n", i + 1);
        printf("Nom : %s\n", noms[i]);
        printf("Prénom : %s\n", prenoms[i]);
        printf("Adresse : %s\n", adresses[i]);
        printf("Note Programmation C : %.1f\n", note_prog[i]);
        printf("Note Système d'exploitation : %.1f\n\n", note_sys[i]);
    }

    return 0;
}

