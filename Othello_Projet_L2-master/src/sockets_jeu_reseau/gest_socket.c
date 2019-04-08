/**
 * \file gest_socket.c
 * \brief Fichier qui contient toutes les fonctions pour le client&serveur
 * \author Fatnassi Mendy
 * \version 2
 * \date 02 avril 2019
 **/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "socket.h"


/* envoyer_crd() & recep_crd fonction commune a client & serveur */
int envoyer_crd(int socket,t_matrice m, int *lig, int *col, char *joueur,int *score1,int *score2){
    char temp = joueur_suivant(*joueur);

	choisir_coup(m,lig,col,*joueur);

    if (peut_jouer(m,temp)){
        jouer_coup(m,*lig,*col,*joueur);
        send(socket,lig,sizeof(*lig),0);
        send(socket,col,sizeof(*col),0);
        read(socket,joueur,sizeof(char));
        send(socket,score1,sizeof(int),0);
        send(socket,score2,sizeof(int),0);
        *joueur = temp;
    return 0;
	}
	else {
		printf ("\nLe joueur %c passe son tour\n", temp);
		calculer_score(m,score1,score2);
	return 1;
	}
}

int recep_crd(int socket,t_matrice m, int *lig, int *col, char *joueur,int *score1,int *score2){
    recv(socket,lig,sizeof(*lig),0);
    recv(socket,col,sizeof(*col),0);
	write(socket,joueur,sizeof(char));
    recv(socket,score1,sizeof(int),0);
    recv(socket,score2,sizeof(int),0);

	//jouer_coup(m,*lig,*col,*joueur);
	return 0;
}