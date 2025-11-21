/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef __CLIENT_H__
#define __CLIENT_H__

/*
 * port d'ordinateur pour envoyer et recevoir des messages
 */
#define PORT 8089

int envoie_recois_message(int socketfd);
int envoie_operateur_numeros(int socketfd, char operateur, int premier,
                             int second, int *resultat);

#endif
