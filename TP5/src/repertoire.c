#include "repertoire.h"
#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

static int est_point(const char *nom) {
    return strcmp(nom, ".") == 0 || strcmp(nom, "..") == 0;
}

static int est_dossier(const char *chemin) {
    struct stat info;
    if (stat(chemin, &info) != 0) {
        return 0;
    }
    return S_ISDIR(info.st_mode);
}

int lire_dossier(const char *chemin) {
    DIR *dir = opendir(chemin);
    if (!dir) {
        perror("Impossible d'ouvrir le repertoire");
        return 0;
    }

    printf("Contenu de %s:\n", chemin);
    struct dirent *entry = NULL;
    while ((entry = readdir(dir)) != NULL) {
        if (est_point(entry->d_name)) {
            continue;
        }
        printf(" - %s\n", entry->d_name);
    }

    closedir(dir);
    return 1;
}

static void parcours_recursif(const char *chemin, int niveau) {
    DIR *dir = opendir(chemin);
    if (!dir) {
        perror("Impossible d'ouvrir le repertoire");
        return;
    }

    struct dirent *entry = NULL;
    while ((entry = readdir(dir)) != NULL) {
        if (est_point(entry->d_name)) {
            continue;
        }
        for (int i = 0; i < niveau; ++i) {
            printf("  ");
        }
        printf("%s\n", entry->d_name);

        char sous_chemin[PATH_MAX];
        snprintf(sous_chemin, sizeof(sous_chemin), "%s/%s", chemin, entry->d_name);

        if (est_dossier(sous_chemin)) {
            parcours_recursif(sous_chemin, niveau + 1);
        }
    }
    closedir(dir);
}

int lire_dossier_recursif(const char *chemin) {
    printf("Exploration recursive de %s:\n", chemin);
    parcours_recursif(chemin, 0);
    return 1;
}

struct pile_chemins {
    char **elements;
    size_t taille;
    size_t capacite;
};

static void pile_init(struct pile_chemins *pile) {
    pile->elements = NULL;
    pile->taille = 0;
    pile->capacite = 0;
}

static void pile_detruire(struct pile_chemins *pile) {
    for (size_t i = 0; i < pile->taille; ++i) {
        free(pile->elements[i]);
    }
    free(pile->elements);
    pile->elements = NULL;
    pile->taille = 0;
    pile->capacite = 0;
}

static void pile_push(struct pile_chemins *pile, const char *chemin) {
    if (pile->taille == pile->capacite) {
        size_t nouvelle_capacite = pile->capacite == 0 ? 8 : pile->capacite * 2;
        char **nouveaux =
            realloc(pile->elements, nouvelle_capacite * sizeof(char *));
        if (!nouveaux) {
            perror("Allocation impossible");
            return;
        }
        pile->elements = nouveaux;
        pile->capacite = nouvelle_capacite;
    }
    pile->elements[pile->taille] = malloc(strlen(chemin) + 1);
    if (!pile->elements[pile->taille]) {
        perror("Allocation impossible");
        return;
    }
    strcpy(pile->elements[pile->taille], chemin);
    pile->taille++;
}

static char *pile_pop(struct pile_chemins *pile) {
    if (pile->taille == 0) {
        return NULL;
    }
    return pile->elements[--pile->taille];
}

int lire_dossier_iteratif(const char *chemin) {
    struct pile_chemins pile;
    pile_init(&pile);
    pile_push(&pile, chemin);

    char *courant = NULL;
    while ((courant = pile_pop(&pile)) != NULL) {
        DIR *dir = opendir(courant);
        if (!dir) {
            perror("Impossible d'ouvrir le repertoire");
            free(courant);
            continue;
        }

        printf("Exploration de %s\n", courant);
        struct dirent *entry = NULL;
        while ((entry = readdir(dir)) != NULL) {
            if (est_point(entry->d_name)) {
                continue;
            }
            char sous_chemin[PATH_MAX];
            snprintf(sous_chemin, sizeof(sous_chemin), "%s/%s", courant,
                     entry->d_name);
            printf(" - %s\n", sous_chemin);
            if (est_dossier(sous_chemin)) {
                pile_push(&pile, sous_chemin);
            }
        }

        closedir(dir);
        free(courant);
    }

    pile_detruire(&pile);
    return 1;
}

