#include "operator.h"
#include <stdio.h>
#include <stdlib.h>

static void afficher_usage(const char *nom) {
    printf("Utilisation : %s <operateur> <num1> [num2]\n", nom);
    printf("Exemple : %s + 10 5\n", nom);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        afficher_usage(argv[0]);
        return 1;
    }

    char op = argv[1][0];
    int num1 = (int)strtol(argv[2], NULL, 10);
    int num2 = 0;

    if (op != '~') {
        if (argc < 4) {
            afficher_usage(argv[0]);
            return 1;
        }
        num2 = (int)strtol(argv[3], NULL, 10);
    }

    int resultat = 0;
    if (!appliquer_operation(op, num1, num2, &resultat)) {
        puts("Operation invalide (division par zero ?).");
        return 1;
    }

    if (op == '~') {
        printf("Resultat : %d\n", resultat);
    } else {
        printf("Resultat : %d %c %d = %d\n", num1, op, num2, resultat);
    }
    return 0;
}

