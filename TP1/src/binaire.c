#include <stdio.h>

static void afficher_binaire(unsigned int valeur) {
    const int total_bits = (int)(sizeof(unsigned int) * 8);
    printf("%10u : ", valeur);
    for (int bit = total_bits - 1; bit >= 0; --bit) {
        unsigned int masque = 1u << bit;
        putchar((valeur & masque) ? '1' : '0');
        if (bit % 4 == 0) {
            putchar(' ');
        }
    }
    putchar('\n');
}

int main(void) {
    unsigned int valeurs[] = {0u, 4096u, 65536u, 65535u, 1024u};
    const size_t nb = sizeof(valeurs) / sizeof(valeurs[0]);

    for (size_t i = 0; i < nb; ++i) {
        afficher_binaire(valeurs[i]);
    }

    return 0;
}

