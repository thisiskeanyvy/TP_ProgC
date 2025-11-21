#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NB_COULEURS 100

struct couleur {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

struct couleur_occurrence {
    struct couleur couleur;
    int compteur;
};

static int couleurs_identiques(const struct couleur *a, const struct couleur *b) {
    return a->r == b->r && a->g == b->g && a->b == b->b && a->a == b->a;
}

int main(void) {
    struct couleur couleurs[NB_COULEURS];
    srand((unsigned)time(NULL));

    for (int i = 0; i < NB_COULEURS; ++i) {
        couleurs[i].r = (uint8_t)(rand() % 256);
        couleurs[i].g = (uint8_t)(rand() % 256);
        couleurs[i].b = (uint8_t)(rand() % 256);
        couleurs[i].a = 0xFF;
    }

    struct couleur_occurrence distinctes[NB_COULEURS] = {0};
    int total_distinctes = 0;

    for (int i = 0; i < NB_COULEURS; ++i) {
        int trouve = 0;
        for (int j = 0; j < total_distinctes; ++j) {
            if (couleurs_identiques(&couleurs[i], &distinctes[j].couleur)) {
                ++distinctes[j].compteur;
                trouve = 1;
                break;
            }
        }
        if (!trouve) {
            distinctes[total_distinctes].couleur = couleurs[i];
            distinctes[total_distinctes].compteur = 1;
            ++total_distinctes;
        }
    }

    puts("Couleurs distinctes et occurrences :");
    for (int i = 0; i < total_distinctes; ++i) {
        printf("rgba(%3u, %3u, %3u, %3u) : %d\n", distinctes[i].couleur.r,
               distinctes[i].couleur.g, distinctes[i].couleur.b,
               distinctes[i].couleur.a, distinctes[i].compteur);
    }

    return 0;
}

