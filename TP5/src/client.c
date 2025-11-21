#include "client.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stddef.h>

#define NB_ETUDIANTS 5
#define NB_NOTES 5

int envoie_recois_message(int socketfd) {
    char data[1024];
    memset(data, 0, sizeof(data));

    char message[1000];
    printf("Votre message (max 1000 caracteres): ");
    if (!fgets(message, sizeof(message), stdin)) {
        return -1;
    }

    snprintf(data, sizeof(data), "message: %s", message);

    if (write(socketfd, data, strlen(data)) < 0) {
        perror("Erreur d'ecriture");
        return -1;
    }

    memset(data, 0, sizeof(data));
    int read_status = read(socketfd, data, sizeof(data) - 1);
    if (read_status < 0) {
        perror("Erreur de lecture");
        return -1;
    }
    data[read_status] = '\0';
    printf("Message recu: %s\n", data);
    return 0;
}

int envoie_operateur_numeros(int socketfd, char operateur, int premier,
                             int second, int *resultat) {
    char requete[256];
    snprintf(requete, sizeof(requete), "calcule : %c %d %d", operateur,
             premier, second);

    if (write(socketfd, requete, strlen(requete)) < 0) {
        perror("Erreur d'ecriture");
        return -1;
    }

    char reponse[256];
    memset(reponse, 0, sizeof(reponse));
    int lecture = read(socketfd, reponse, sizeof(reponse) - 1);
    if (lecture < 0) {
        perror("Erreur de lecture");
        return -1;
    }
    reponse[lecture] = '\0';

    long valeur = 0;
    if (sscanf(reponse, "calcule : %ld", &valeur) == 1) {
        if (resultat) {
            *resultat = (int)valeur;
        }
        printf("Resultat recu: %ld\n", valeur);
        return 0;
    }

    fprintf(stderr, "Reponse inattendue: %s\n", reponse);
    return -1;
}

static int lire_entier_interactif(const char *invite, int *valeur) {
    printf("%s", invite);
    char ligne[64];
    if (!fgets(ligne, sizeof(ligne), stdin)) {
        return -1;
    }
    *valeur = atoi(ligne);
    return 0;
}

static void mode_calcul_simple(int socketfd) {
    char op_ligne[8];
    printf("Operateur (+ - * / %%): ");
    if (!fgets(op_ligne, sizeof(op_ligne), stdin)) {
        return;
    }
    char operateur = op_ligne[0];

    int premier = 0;
    int second = 0;
    if (lire_entier_interactif("Premier nombre: ", &premier) != 0 ||
        lire_entier_interactif("Second nombre: ", &second) != 0) {
        return;
    }

    envoie_operateur_numeros(socketfd, operateur, premier, second, NULL);
}

static int lire_notes_etudiant(int index_etudiant, int *notes,
                               size_t nb_notes) {
    for (size_t note = 1; note <= nb_notes; ++note) {
        char chemin[128];
        snprintf(chemin, sizeof(chemin), "../etudiant/%d/note%zu.txt",
                 index_etudiant, note);

        FILE *fichier = fopen(chemin, "r");
        if (!fichier) {
            perror("Impossible d'ouvrir le fichier de notes");
            return -1;
        }

        if (fscanf(fichier, "%d", &notes[note - 1]) != 1) {
            fclose(fichier);
            fprintf(stderr, "Lecture invalide dans %s\n", chemin);
            return -1;
        }
        fclose(fichier);
    }
    return 0;
}

static void calculer_statistiques_etudiants(int socketfd) {
    int total_classe = 0;

    for (int etudiant = 1; etudiant <= NB_ETUDIANTS; ++etudiant) {
        int notes[NB_NOTES];
        if (lire_notes_etudiant(etudiant, notes, NB_NOTES) != 0) {
            return;
        }

        int somme = 0;
        for (size_t i = 0; i < NB_NOTES; ++i) {
            int resultat = 0;
            if (envoie_operateur_numeros(socketfd, '+', somme, notes[i],
                                         &resultat) != 0) {
                return;
            }
            somme = resultat;
        }

        int moyenne = 0;
        if (envoie_operateur_numeros(socketfd, '/', somme, NB_NOTES,
                                     &moyenne) != 0) {
            return;
        }

        printf("Etudiant %d -> somme=%d moyenne=%d\n", etudiant, somme,
               moyenne);

        int nouveau_total = 0;
        if (envoie_operateur_numeros(socketfd, '+', total_classe, somme,
                                     &nouveau_total) != 0) {
            return;
        }
        total_classe = nouveau_total;
    }

    int total_notes = NB_ETUDIANTS * NB_NOTES;
    int moyenne_classe = 0;
    if (envoie_operateur_numeros(socketfd, '/', total_classe, total_notes,
                                 &moyenne_classe) != 0) {
        return;
    }

    printf("Somme classe=%d, moyenne classe=%d\n", total_classe,
           moyenne_classe);
}

static void afficher_menu(void) {
    puts("\nMenu client");
    puts("1 - Envoyer un message");
    puts("2 - Effectuer un calcul simple");
    puts("3 - Calculer les notes des etudiants");
    puts("0 - Quitter");
}

int main(void) {
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

    if (connect(socketfd, (struct sockaddr *)&server_addr,
                sizeof(server_addr)) < 0) {
        perror("connection serveur");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        afficher_menu();
        printf("Votre choix : ");
        char ligne[16];
        if (!fgets(ligne, sizeof(ligne), stdin)) {
            break;
        }
        int choix = atoi(ligne);

        switch (choix) {
        case 1:
            envoie_recois_message(socketfd);
            break;
        case 2:
            mode_calcul_simple(socketfd);
            break;
        case 3:
            calculer_statistiques_etudiants(socketfd);
            break;
        case 0:
            close(socketfd);
            return 0;
        default:
            puts("Choix inconnu.");
            break;
        }
    }

    close(socketfd);
    return 0;
}
