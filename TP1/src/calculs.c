#include <stdio.h>

static int appliquer_operation(int num1, int num2, char op, int *resultat) {
    switch (op) {
    case '+':
        *resultat = num1 + num2;
        return 1;
    case '-':
        *resultat = num1 - num2;
        return 1;
    case '*':
        *resultat = num1 * num2;
        return 1;
    case '/':
        if (num2 == 0) {
            return 0;
        }
        *resultat = num1 / num2;
        return 1;
    case '%':
        if (num2 == 0) {
            return 0;
        }
        *resultat = num1 % num2;
        return 1;
    case '&':
        *resultat = num1 & num2;
        return 1;
    case '|':
        *resultat = num1 | num2;
        return 1;
    case '~':
        *resultat = ~num1;
        return 1;
    default:
        return 0;
    }
}

int main(void) {
    const int num1 = 42;
    const int num2 = 13;
    const char ops[] = {'+', '-', '*', '/', '%', '&', '|', '~'};

    for (size_t i = 0; i < sizeof(ops); ++i) {
        int resultat = 0;
        if (appliquer_operation(num1, num2, ops[i], &resultat)) {
            if (ops[i] == '~') {
                printf("%c %d -> %d\n", ops[i], num1, resultat);
            } else {
                printf("%d %c %d = %d\n", num1, ops[i], num2, resultat);
            }
        } else {
            printf("Opération %c impossible (division par zéro ?)\n", ops[i]);
        }
    }

    return 0;
}
