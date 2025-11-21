#ifndef LISTE_H
#define LISTE_H

#include <stddef.h>
#include <stdint.h>

struct couleur {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct noeud_couleur {
    struct couleur valeur;
    struct noeud_couleur *suivant;
};

struct liste_couleurs {
    struct noeud_couleur *tete;
    size_t taille;
};

void init_liste(struct liste_couleurs *liste);
void insertion(const struct couleur *couleur, struct liste_couleurs *liste);
void parcours(const struct liste_couleurs *liste);
void detruire_liste(struct liste_couleurs *liste);

#endif

