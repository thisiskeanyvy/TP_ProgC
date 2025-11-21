#include <stdio.h>

int main(void) {
    const int a = 2;
    const int b = 10;
    long long resultat = 1;

    for (int i = 0; i < b; ++i) {
        resultat *= a;
    }

    printf("%d^%d = %lld\n", a, b, resultat);
    return 0;
}

