/**
 * \file client.c
 * \brief Fichier qui sert au client 
 * \author Fatnassi Mendy
 * \version 2
 * \date 02 avril 2019
 * */


#include "socket.h"

#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "../define.h"
#include "../gest_matrice.h"
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <signal.h>

/*
* \brief Permet de se connecter au serveur
* \fn init_client(struct sockaddr_in serveur_addr,struct hostent * serveur_info , long hostAddr,int to_server_socket)  
*/
void init_client(struct sockaddr_in serveur_addr,struct hostent * serveur_info , long hostAddr,int to_server_socket){

	bzero(&serveur_addr,sizeof(serveur_addr));
	hostAddr = inet_addr(SERVEURNAME);
	if ( (long)hostAddr != (long)-1 ){
		bcopy(&hostAddr,&serveur_addr.sin_addr,sizeof(hostAddr));
	}
	else {
		serveur_info = gethostbyname(SERVEURNAME);
		if (serveur_info == NULL) {
			printf("Impossible de récupérer les infos du serveur\n");
			exit(0);
		}
		bcopy(serveur_info->h_addr,&serveur_addr.sin_addr,serveur_info->h_length);
	}
	//sin_port sera égal à la valeur retournée par la fonction htons, avec comme paramètre le port utilisé
	serveur_addr.sin_port = htons(30000);
	serveur_addr.sin_family = AF_INET;

	/* creation de la socket */
	//int socket(int domain, int type, int protocol)
	//avec domain:AF_INET pour TCP/IP et type :SOCK_STREAM si on utilise TCP/IP
	if ( (to_server_socket = socket(AF_INET,SOCK_STREAM,0)) < 0) {
		printf("Impossible de créer la socket client\n");
	  	exit(0);
	}
	/* requete de connexion */
	//int connect(int socket, struct sockaddr* addr, socklen_t addrlen);
	//avec sockaddr* :  pointeur sur le contexte d'adressage du client et socklen : taille du contexte d'adressage comme le fonction accept() cote serveur
	if(connect(to_server_socket, (struct sockaddr *)&serveur_addr, sizeof(serveur_addr)) < 0 ) {
		printf("Impossible de se connecter au serveur\n");
	  	exit(0);
	}
	/* envoie de données et reception */
	printf("Connexion avec le serveur reussi!\n");
}

/*
* \fn int quit_client (int to_server_socket)
*/

int quit_client (int to_server_socket){
	shutdown(to_server_socket,2);
	if(close(to_server_socket)==0){
		return 0;
	}
	else {
		return -1;
	}
}



void jeux_reseaux_c(){
	t_matrice m;
	int *lig=malloc(sizeof(int)),*col=malloc(sizeof(int)),score1=0,score2=0;
	char *joueur=malloc(sizeof(char));
	//struct socka_addr permet de configurer la connexion (contexte d'addressage)
	struct sockaddr_in serveur_addr;
	struct hostent *serveur_info=malloc(sizeof(struct hostent));
	long hostAddr=0;
	//char buffer[512];
	int to_server_socket=0;
	*joueur=NOIR;

//Initialisation du jeux
	init_client(serveur_addr,serveur_info ,hostAddr,to_server_socket);
	init_matrice(m);
	while(!partie_terminee (m)){ 
		while (!partie_terminee (m)) {
			afficher_matrice (m);
			choisir_coup(m,lig,col,*joueur);
			jouer_coup(m,*lig,*col,*joueur);
			afficher_matrice (m);
	        
		    if (peut_jouer(m,joueur_suivant(*joueur))){
		    	send(to_server_socket,lig,sizeof(*lig),0);
			    send(to_server_socket,col,sizeof(*col),0);
			    read(to_server_socket,joueur,sizeof(char));
			    send(to_server_socket,&score1,sizeof(int),0);
			    send(to_server_socket,&score2,sizeof(int),0);
		    	*joueur = joueur_suivant(*joueur);
			}
			else {
				printf ("\nLe joueur %c passe son tour\n", *joueur);
				calculer_score(m,&score1,&score2);
				printf("il y a %d pions du joueur 1 \n et %d du joueur 2 \n",score1,score2);

		   	}
		    recv(to_server_socket,lig,sizeof(*lig),0);
		    recv(to_server_socket,col,sizeof(*col),0);
			write(to_server_socket,joueur,sizeof(char));
		    recv(to_server_socket,&score1,sizeof(int),0);
		    recv(to_server_socket,&score2,sizeof(int),0);
		}
	}
	/* fermeture de la connexion */
	quit_client (to_server_socket);
}

int main(void){

	jeux_reseaux_c();
	return 0;
}
