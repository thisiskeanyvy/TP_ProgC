#include "liste.h"
#include <stdio.h>
#include <stdlib.h>

void init_liste(struct liste_couleurs *liste) {
    if (!liste) {
        return;
    }
    liste->tete = NULL;
    liste->taille = 0;
}

void insertion(const struct couleur *couleur, struct liste_couleurs *liste) {
    if (!liste || !couleur) {
        return;
    }

    struct noeud_couleur *nouveau = malloc(sizeof(*nouveau));
    if (!nouveau) {
        perror("Allocation echouee");
        return;
    }
    nouveau->valeur = *couleur;
    nouveau->suivant = NULL;

    if (!liste->tete) {
        liste->tete = nouveau;
    } else {
        struct noeud_couleur *courant = liste->tete;
        while (courant->suivant) {
            courant = courant->suivant;
        }
        courant->suivant = nouveau;
    }
    liste->taille++;
}

void parcours(const struct liste_couleurs *liste) {
    if (!liste) {
        return;
    }

    const struct noeud_couleur *courant = liste->tete;
    size_t index = 1;
    while (courant) {
        printf("Couleur %zu -> R=%3u G=%3u B=%3u\n", index, courant->valeur.r,
               courant->valeur.g, courant->valeur.b);
        courant = courant->suivant;
        ++index;
    }
}

void detruire_liste(struct liste_couleurs *liste) {
    if (!liste) {
        return;
    }

    struct noeud_couleur *courant = liste->tete;
    while (courant) {
        struct noeud_couleur *suivant = courant->suivant;
        free(courant);
        courant = suivant;
    }
    liste->tete = NULL;
    liste->taille = 0;
}

