#include "fichier.h"
#include "liste.h"
#include "operator.h"
#include <stdio.h>
#include <string.h>

static void vider_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static void retirer_newline(char *texte) {
    if (!texte) {
        return;
    }
    size_t len = strlen(texte);
    if (len > 0 && texte[len - 1] == '\n') {
        texte[len - 1] = '\0';
    }
}

static void exercice_41(void) {
    int num1 = 0;
    int num2 = 0;
    char op = 0;

    printf("Entrez num1 : ");
    if (scanf("%d", &num1) != 1) {
        puts("Entree invalide.");
        return;
    }
    printf("Entrez num2 : ");
    if (scanf("%d", &num2) != 1) {
        puts("Entree invalide.");
        return;
    }

    printf("Entrez l'operateur (+, -, *, /, %%, &, |, ~) : ");
    scanf(" %c", &op);

    int resultat = 0;
    if (appliquer_operation(op, num1, num2, &resultat)) {
        if (op == '~') {
            printf("Resultat : %d\n", resultat);
        } else {
            printf("Resultat : %d %c %d = %d\n", num1, op, num2, resultat);
        }
    } else {
        puts("Operation invalide ou division par zero.");
    }
}

static void exercice_42(void) {
    int choix = 0;
    printf("Que souhaitez-vous faire ?\n");
    printf("1. Lire un fichier\n");
    printf("2. Ecrire dans un fichier\n");
    printf("Votre choix : ");
    if (scanf("%d", &choix) != 1) {
        puts("Entree invalide.");
        return;
    }
    vider_buffer();

    char nom_fichier[256];
    printf("Entrez le nom du fichier : ");
    if (!fgets(nom_fichier, sizeof(nom_fichier), stdin)) {
        puts("Lecture interrompue.");
        return;
    }
    retirer_newline(nom_fichier);

    if (choix == 1) {
        lire_fichier(nom_fichier);
    } else if (choix == 2) {
        char message[512];
        printf("Entrez le message a ecrire : ");
        if (!fgets(message, sizeof(message), stdin)) {
            puts("Lecture interrompue.");
            return;
        }
        retirer_newline(message);
        if (ecrire_dans_fichier(nom_fichier, message)) {
            printf("Message ecrit dans %s.\n", nom_fichier);
        }
    } else {
        puts("Choix inconnu.");
    }
}

static void exercice_47(void) {
    struct liste_couleurs liste;
    init_liste(&liste);

    struct couleur couleurs[] = {
        {0xFF, 0x00, 0x00}, {0x00, 0xFF, 0x00}, {0x00, 0x00, 0xFF},
        {0xFF, 0xFF, 0x00}, {0xFF, 0x80, 0x00}, {0x80, 0x00, 0xFF},
        {0x00, 0xFF, 0xFF}, {0x80, 0x80, 0x80}, {0xAA, 0xBB, 0xCC},
        {0x11, 0x22, 0x33}};

    size_t nb = sizeof(couleurs) / sizeof(couleurs[0]);
    for (size_t i = 0; i < nb; ++i) {
        insertion(&couleurs[i], &liste);
    }

    puts("Liste des couleurs :");
    parcours(&liste);
    detruire_liste(&liste);
}

int main(void) {
    int choix = -1;
    printf("Choisissez l'exercice a executer :\n");
    printf("1 - Calculs (Exercice 4.1)\n");
    printf("2 - Fichiers (Exercice 4.2)\n");
    printf("3 - Liste de couleurs (Exercice 4.7)\n");
    printf("0 - Quitter\n");
    printf("Votre choix : ");

    if (scanf("%d", &choix) != 1) {
        puts("Entree invalide.");
        return 1;
    }
    vider_buffer();

    switch (choix) {
    case 1:
        exercice_41();
        break;
    case 2:
        exercice_42();
        break;
    case 3:
        exercice_47();
        break;
    case 0:
        puts("Au revoir.");
        break;
    default:
        puts("Choix inconnu.");
        break;
    }

    return 0;
}

