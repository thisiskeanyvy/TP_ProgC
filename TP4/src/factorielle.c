#include <stdio.h>
#include <stddef.h>

static unsigned long long factorielle(unsigned int n) {
    if (n == 0) {
        printf("fact(0): 1\n");
        return 1ULL;
    }
    unsigned long long resultat = n * factorielle(n - 1);
    printf("fact(%u): %llu\n", n, resultat);
    return resultat;
}

int main(void) {
    unsigned int tests[] = {0, 1, 5, 8};
    const size_t nb_tests = sizeof(tests) / sizeof(tests[0]);
    for (size_t i = 0; i < nb_tests; ++i) {
        printf("Resultat final pour %u! = %llu\n\n", tests[i],
               factorielle(tests[i]));
    }
    return 0;
}

