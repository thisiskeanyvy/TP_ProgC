#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

struct couleur {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

static void afficher_couleur(const struct couleur *c) {
    printf("rgba(%3u, %3u, %3u, %3u)\n", c->r, c->g, c->b, c->a);
}

int main(void) {
    struct couleur palette[] = {
        {255, 0, 0, 255},   {0, 255, 0, 255},    {0, 0, 255, 255},
        {255, 255, 0, 255}, {255, 0, 255, 255},  {0, 255, 255, 255},
        {128, 64, 32, 255}, {64, 32, 16, 255},   {240, 128, 0, 255},
        {10, 20, 30, 255}};

    const size_t nb_couleurs = sizeof(palette) / sizeof(palette[0]);

    puts("Palette de couleurs :");
    for (size_t i = 0; i < nb_couleurs; ++i) {
        afficher_couleur(&palette[i]);
    }

    return 0;
}

