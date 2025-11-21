/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stddef.h>

#include "bmp.h"
#include "client.h"

#define MAX_COULEURS 30

static void nettoyer_fin_ligne(char *texte) {
  size_t len = strlen(texte);
  if (len > 0 && texte[len - 1] == '\n') {
    texte[len - 1] = '\0';
  }
}

static void construire_json(const char *code, const char *valeurs[],
                            size_t nb_valeurs, char *dest, size_t taille) {
  size_t offset = 0;
  offset += snprintf(dest + offset, taille - offset,
                     "{\"code\":\"%s\",\"valeurs\":[", code);
  for (size_t i = 0; i < nb_valeurs; ++i) {
    offset +=
        snprintf(dest + offset, taille - offset, "\"%s\"%s", valeurs[i],
                 (i + 1 == nb_valeurs) ? "]}" : ",");
    if (offset >= taille) {
      break;
    }
  }
}

static int extraire_valeur_index(const char *json, size_t index, char *buffer,
                                 size_t taille) {
  const char *valeurs = strstr(json, "\"valeurs\"");
  if (!valeurs) {
    return 0;
  }
  const char *p = strchr(valeurs, '[');
  if (!p) {
    return 0;
  }
  ++p;

  size_t courant = 0;
  while (*p && *p != ']') {
    while (*p && (*p == ' ' || *p == ',')) {
      ++p;
    }
    if (*p != '"') {
      ++p;
      continue;
    }
    ++p;
    char temp[256];
    size_t len = 0;
    while (*p && *p != '"' && len + 1 < sizeof(temp)) {
      temp[len++] = *p++;
    }
    temp[len] = '\0';
    if (*p == '"') {
      ++p;
    }
    if (courant == index) {
      strncpy(buffer, temp, taille);
      buffer[taille - 1] = '\0';
      return 1;
    }
    ++courant;
  }
  return 0;
}

static int construire_message_couleurs(const char *pathname, int nb_couleurs,
                                       char *dest, size_t taille) {
  couleur_compteur *cc = analyse_bmp_image((char *)pathname);
  if (!cc) {
    fprintf(stderr, "Impossible d'analyser l'image %s\n", pathname);
    return -1;
  }
  if (cc->size <= 0) {
    fprintf(stderr, "Aucune couleur detectee dans %s\n", pathname);
    return -1;
  }

  if (nb_couleurs > MAX_COULEURS) {
    nb_couleurs = MAX_COULEURS;
  }
  if (nb_couleurs > cc->size) {
    nb_couleurs = cc->size;
  }
  if (nb_couleurs <= 0) {
    nb_couleurs = cc->size;
  }

  char valeurs[MAX_COULEURS + 1][16];
  const char *ptrs[MAX_COULEURS + 1];

  snprintf(valeurs[0], sizeof(valeurs[0]), "%d", nb_couleurs);
  ptrs[0] = valeurs[0];

  for (int i = 0; i < nb_couleurs; ++i) {
    int index = cc->size - 1 - i;
    unsigned int rouge = 0;
    unsigned int vert = 0;
    unsigned int bleu = 0;
    if (cc->compte_bit == BITS32) {
      rouge = cc->cc.cc32[index].c.rouge;
      vert = cc->cc.cc32[index].c.vert;
      bleu = cc->cc.cc32[index].c.bleu;
    } else {
      rouge = cc->cc.cc24[index].c.rouge;
      vert = cc->cc.cc24[index].c.vert;
      bleu = cc->cc.cc24[index].c.bleu;
    }
    snprintf(valeurs[i + 1], sizeof(valeurs[i + 1]), "#%02x%02x%02x", rouge,
             vert, bleu);
    ptrs[i + 1] = valeurs[i + 1];
  }

  construire_json("couleurs", ptrs, nb_couleurs + 1, dest, taille);
  return 0;
}

int envoie_recois_message(int socketfd) {
  char message[512];
  printf("Votre message (max 500 caracteres): ");
  if (!fgets(message, sizeof(message), stdin)) {
    return -1;
  }
  nettoyer_fin_ligne(message);

  const char *valeurs[] = {message};
  char requete[1024];
  construire_json("message", valeurs, 1, requete, sizeof(requete));

  if (write(socketfd, requete, strlen(requete)) < 0) {
    perror("erreur ecriture");
    return -1;
  }

  char reponse[1024];
  memset(reponse, 0, sizeof(reponse));
  int read_status = read(socketfd, reponse, sizeof(reponse) - 1);
  if (read_status < 0) {
    perror("erreur lecture");
    return -1;
  }
  reponse[read_status] = '\0';

  char valeur[512];
  if (extraire_valeur_index(reponse, 0, valeur, sizeof(valeur))) {
    printf("Message recu: %s\n", valeur);
  } else {
    printf("Reponse brute: %s\n", reponse);
  }
  return 0;
}

static int envoie_couleurs(int socketfd, const char *pathname, int nb_couleurs) {
  char data[2048];
  if (construire_message_couleurs(pathname, nb_couleurs, data, sizeof(data)) !=
      0) {
    return -1;
  }

  if (write(socketfd, data, strlen(data)) < 0) {
    perror("erreur ecriture");
    return -1;
  }
  return 0;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("usage: ./client chemin_bmp_image [nombre_couleurs<=30]\n");
    printf("       ./client --message\n");
    return EXIT_FAILURE;
  }

  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  if (connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    perror("connection serveur");
    close(socketfd);
    exit(EXIT_FAILURE);
  }

  if (strcmp(argv[1], "--message") == 0) {
    envoie_recois_message(socketfd);
  } else {
    const char *image_path = argv[1];
    int nb_couleurs = 10;
    if (argc >= 3) {
      nb_couleurs = atoi(argv[2]);
    } else {
      char buffer[16];
      printf("Nombre de couleurs (<=30): ");
      if (fgets(buffer, sizeof(buffer), stdin)) {
        nb_couleurs = atoi(buffer);
      }
    }
    if (nb_couleurs <= 0) {
      nb_couleurs = 10;
    }
    if (nb_couleurs > MAX_COULEURS) {
      nb_couleurs = MAX_COULEURS;
    }
    envoie_couleurs(socketfd, image_path, nb_couleurs);
  }

  close(socketfd);
  return 0;
}
