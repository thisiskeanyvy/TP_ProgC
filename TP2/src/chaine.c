#include <stdio.h>
#include <stddef.h>

static size_t longueur(const char *chaine) {
    size_t len = 0;
    while (chaine[len] != '\0') {
        ++len;
    }
    return len;
}

static void copie(char *destination, const char *source) {
    size_t i = 0;
    while (source[i] != '\0') {
        destination[i] = source[i];
        ++i;
    }
    destination[i] = '\0';
}

static void concat(char *destination, const char *source) {
    size_t dest_len = longueur(destination);
    size_t i = 0;
    while (source[i] != '\0') {
        destination[dest_len + i] = source[i];
        ++i;
    }
    destination[dest_len + i] = '\0';
}

int main(void) {
    char chaine1[64] = "Hello";
    char chaine2[64] = " World!";
    char copie_destination[64];

    printf("Longueur de \"%s\" : %zu\n", chaine1, longueur(chaine1));

    copie(copie_destination, chaine1);
    printf("Copie : \"%s\"\n", copie_destination);

    concat(chaine1, chaine2);
    printf("Concatenation : \"%s\"\n", chaine1);

    return 0;
}

