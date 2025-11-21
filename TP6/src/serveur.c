/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <math.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "serveur.h"
int socketfd;

#define MAX_COULEURS 30
#define TAILLE_VALEUR 32

int visualize_plot(void)
{
  const char *browser = "firefox";

  char command[256];
  snprintf(command, sizeof(command), "%s %s", browser, svg_file_path);

  int result = system(command);

  if (result == 0)
  {
    printf("SVG file opened in %s.\n", browser);
  }
  else
  {
    printf("Failed to open the SVG file.\n");
  }

  return 0;
}

static int extraire_code(const char *json, char *code, size_t taille)
{
  const char *position = strstr(json, "\"code\"");
  if (!position)
  {
    return 0;
  }
  position = strchr(position, ':');
  if (!position)
  {
    return 0;
  }
  position++;
  while (*position && *position != '"')
  {
    ++position;
  }
  if (*position != '"')
  {
    return 0;
  }
  ++position;
  size_t len = 0;
  while (*position && *position != '"' && len + 1 < taille)
  {
    code[len++] = *position++;
  }
  code[len] = '\0';
  return 1;
}

static int extraire_valeurs(const char *json, char valeurs[][TAILLE_VALEUR], size_t max_valeurs)
{
  const char *section = strstr(json, "\"valeurs\"");
  if (!section)
  {
    return 0;
  }
  const char *p = strchr(section, '[');
  if (!p)
  {
    return 0;
  }
  ++p;
  size_t compte = 0;
  while (*p && *p != ']' && compte < max_valeurs)
  {
    while (*p && (*p == ' ' || *p == ','))
    {
      ++p;
    }
    if (*p != '"')
    {
      ++p;
      continue;
    }
    ++p;
    size_t len = 0;
    while (*p && *p != '"' && len + 1 < TAILLE_VALEUR)
    {
      valeurs[compte][len++] = *p++;
    }
    valeurs[compte][len] = '\0';
    if (*p == '"')
    {
      ++p;
    }
    ++compte;
  }
  return (int)compte;
}

static void construire_json_reponse(const char *code, const char *valeurs[], size_t nb_valeurs, char *dest, size_t taille)
{
  size_t offset = 0;
  offset += snprintf(dest + offset, taille - offset, "{\"code\":\"%s\",\"valeurs\":[", code);
  for (size_t i = 0; i < nb_valeurs; ++i)
  {
    offset += snprintf(dest + offset, taille - offset, "\"%s\"%s", valeurs[i], (i + 1 == nb_valeurs) ? "]}" : ",");
    if (offset >= taille)
    {
      break;
    }
  }
}

double degreesToRadians(double degrees)
{
  return degrees * M_PI / 180.0;
}

int plot(char couleurs[][TAILLE_VALEUR], int nb_couleurs)
{
  if (nb_couleurs <= 0)
  {
    return 0;
  }

  FILE *svg_file = fopen(svg_file_path, "w");
  if (svg_file == NULL)
  {
    perror("Error opening file");
    return 1;
  }

  fprintf(svg_file, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
  fprintf(svg_file, "<svg width=\"400\" height=\"400\" xmlns=\"http://www.w3.org/2000/svg\">\n");
  fprintf(svg_file, "  <rect width=\"100%%\" height=\"100%%\" fill=\"#ffffff\" />\n");

  double center_x = 200.0;
  double center_y = 200.0;
  double radius = 150.0;
  double start_angle = -90.0;
  double angle_par_section = 360.0 / nb_couleurs;

  for (int i = 0; i < nb_couleurs; ++i)
  {
    double end_angle = start_angle + angle_par_section;
    double start_angle_rad = degreesToRadians(start_angle);
    double end_angle_rad = degreesToRadians(end_angle);

    double x1 = center_x + radius * cos(start_angle_rad);
    double y1 = center_y + radius * sin(start_angle_rad);
    double x2 = center_x + radius * cos(end_angle_rad);
    double y2 = center_y + radius * sin(end_angle_rad);

    fprintf(svg_file, "  <path d=\"M%.2f,%.2f A%.2f,%.2f 0 0,1 %.2f,%.2f L%.2f,%.2f Z\" fill=\"%s\" />\n",
            x1, y1, radius, radius, x2, y2, center_x, center_y, couleurs[i]);

    start_angle = end_angle;
  }

  fprintf(svg_file, "</svg>\n");
  fclose(svg_file);
  visualize_plot();
  return 0;
}

/* renvoyer un message (*data) au client (client_socket_fd)
 */
int renvoie_message(int client_socket_fd, char *data)
{
  int data_size = write(client_socket_fd, (void *)data, strlen(data));

  if (data_size < 0)
  {
    perror("erreur ecriture");
    return (EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}

/* accepter la nouvelle connection d'un client et lire les données
 * envoyées par le client. En suite, le serveur envoie un message
 * en retour
 */
int recois_envoie_message(int client_socket_fd, char data[1024])
{
  char code[32];
  if (!extraire_code(data, code, sizeof(code)))
  {
    fprintf(stderr, "Message JSON invalide\n");
    return EXIT_FAILURE;
  }

  if (strcmp(code, "message") == 0)
  {
    char valeurs[1][TAILLE_VALEUR];
    int nb = extraire_valeurs(data, valeurs, 1);
    if (nb > 0)
    {
      printf("Message recu: %s\n", valeurs[0]);
    }

    char reponse[512];
    printf("Reponse serveur: ");
    if (!fgets(reponse, sizeof(reponse), stdin))
    {
      return EXIT_FAILURE;
    }
    size_t len = strlen(reponse);
    if (len > 0 && reponse[len - 1] == '\n')
    {
      reponse[len - 1] = '\0';
    }

    const char *valeurs_reponse[] = {reponse};
    char json[1024];
    construire_json_reponse("message", valeurs_reponse, 1, json, sizeof(json));
    return renvoie_message(client_socket_fd, json);
  }

  if (strcmp(code, "couleurs") == 0)
  {
    char valeurs[MAX_COULEURS + 1][TAILLE_VALEUR];
    int total = extraire_valeurs(data, valeurs, MAX_COULEURS + 1);
    if (total < 2)
    {
      fprintf(stderr, "Couleurs insuffisantes recues\n");
      return EXIT_FAILURE;
    }
    int nb_couleurs = atoi(valeurs[0]);
    if (nb_couleurs > total - 1)
    {
      nb_couleurs = total - 1;
    }
    if (nb_couleurs > MAX_COULEURS)
    {
      nb_couleurs = MAX_COULEURS;
    }
    plot(&valeurs[1], nb_couleurs);
    return EXIT_SUCCESS;
  }

  fprintf(stderr, "Code inconnu: %s\n", code);
  return EXIT_FAILURE;
}

// Fonction de gestion du signal Ctrl+C
void gestionnaire_ctrl_c(int signal)
{
  (void)signal;
  printf("\nSignal Ctrl+C capturé. Sortie du programme.\n");
  // fermer le socket
  close(socketfd);
  exit(0); // Quitter proprement le programme.
}

int main(void)
{
  int bind_status;

  struct sockaddr_in server_addr;

  /*
   * Creation d'une socket
   */
  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
  {
    perror("Unable to open a socket");
    return -1;
  }

  int option = 1;
  setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

  // détails du serveur (adresse et port)
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // Relier l'adresse à la socket
  bind_status = bind(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (bind_status < 0)
  {
    perror("bind");
    return (EXIT_FAILURE);
  }

  // Enregistrez la fonction de gestion du signal Ctrl+C
  signal(SIGINT, gestionnaire_ctrl_c);

  // Écouter les messages envoyés par le client en boucle infinie
  while (1)
  {
    // Écouter les messages envoyés par le client
    listen(socketfd, 10);

    // Lire et répondre au client
    struct sockaddr_in client_addr;
    char data[1024];

    unsigned int client_addr_len = sizeof(client_addr);

    // nouvelle connection de client
    int client_socket_fd = accept(socketfd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_socket_fd < 0)
    {
      perror("accept");
      return (EXIT_FAILURE);
    }

    // la réinitialisation de l'ensemble des données
    memset(data, 0, sizeof(data));

    // lecture de données envoyées par un client
    int data_size = read(client_socket_fd, (void *)data, sizeof(data));

    if (data_size < 0)
    {
      perror("erreur lecture");
      return (EXIT_FAILURE);
    }

    recois_envoie_message(client_socket_fd, data);
  }

  return 0;
}
