#include <stdbool.h>
#include <stdio.h>

int main(void) {
    const int a = 16;
    const int b = 3;

    printf("a = %d, b = %d\n", a, b);
    printf("Addition : %d\n", a + b);
    printf("Soustraction : %d\n", a - b);
    printf("Multiplication : %d\n", a * b);
    printf("Division entière : %d\n", a / b);
    printf("Modulo : %d\n", a % b);

    bool egal = (a == b);
    bool superieur = (a > b);
    printf("a == b ? %s\n", egal ? "vrai" : "faux");
    printf("a > b ? %s\n", superieur ? "vrai" : "faux");

    return 0;
}

