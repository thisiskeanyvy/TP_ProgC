#include "operator.h"

int somme(int num1, int num2) {
    return num1 + num2;
}

int difference(int num1, int num2) {
    return num1 - num2;
}

int produit(int num1, int num2) {
    return num1 * num2;
}

int quotient(int num1, int num2) {
    return num2 == 0 ? 0 : num1 / num2;
}

int modulo(int num1, int num2) {
    return num2 == 0 ? 0 : num1 % num2;
}

int et_logique(int num1, int num2) {
    return num1 & num2;
}

int ou_logique(int num1, int num2) {
    return num1 | num2;
}

int negation(int num1, int num2) {
    (void)num2;
    return ~num1;
}

int appliquer_operation(char op, int num1, int num2, int *resultat) {
    if (!resultat) {
        return 0;
    }

    switch (op) {
    case '+':
        *resultat = somme(num1, num2);
        return 1;
    case '-':
        *resultat = difference(num1, num2);
        return 1;
    case '*':
        *resultat = produit(num1, num2);
        return 1;
    case '/':
        if (num2 == 0) {
            return 0;
        }
        *resultat = quotient(num1, num2);
        return 1;
    case '%':
        if (num2 == 0) {
            return 0;
        }
        *resultat = modulo(num1, num2);
        return 1;
    case '&':
        *resultat = et_logique(num1, num2);
        return 1;
    case '|':
        *resultat = ou_logique(num1, num2);
        return 1;
    case '~':
        *resultat = negation(num1, num2);
        return 1;
    default:
        return 0;
    }
}

