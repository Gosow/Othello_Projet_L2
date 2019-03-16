#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#include "define.h"
#include "gest_aff.h"
#include "gest_matrice.h"

//#define SERVEURNAME "192.168.1.106" // adresse IP de mon serveur
#define SERVEURNAME "127.0.0.1" // adresse IP de mon serveur
#include<strings.h>
//#define SERVEURNAME "172.18.41.139" // adresse IP de mon serveur
//#define SERVEURNAME "127.0.0.1" // adresse IP de mon serveur

#define QUITTER "QUITTER"
#define SOCKET_ERROR -1


char menu(){
	char choix;
	printf("Que voulez-vous faire ?\n");
	printf("m: envoyer un entier au serveur\n");
	printf("q: quitter\n");
	printf("a: afficher tableau\n");
	printf("Que voulez-vous faire ?\n");
	scanf(" %c", &choix);
	return choix;
}

void envoyer_crd(int to_server_socket){
  char msg[200], buffer[512];
	printf("quel sont les coordonnées? A1 par exemple : ");
	scanf(" %[^\n]s", buffer);
	sprintf(msg, "MSG %s", buffer);
	send(to_server_socket, msg, strlen(msg), 0); //on augmente la taille de 4 pour l'entête
	// lecture de la réponse
	memset(buffer, 0, sizeof(buffer));
	recv(to_server_socket,buffer,512,0);
	printf("[client] reponse du serveur : '%s'\n", buffer);

	}

void quitter(int to_server_socket){
	printf("[client] envoi message QUITTER au serveur\n");
	send(to_server_socket,QUITTER,7,0);
}

void afficher_tableau(int *tab_jeux, int nbval){
	int i;
	for(i=0;i<nbval;i++){
		printf("tab[%d]=%d\n",i,tab_jeux[i]);
	}
}

void envoyer_entier(int to_server_socket,int *tab_jeux,int i){
	int entier;
	printf("[CLIENT] Quel est votre entier : ");
	scanf("%d",&entier);
	tab_jeux[i]=entier;
	//write(to_server_socket,tab_jeux,sizeof(int)*20);
	send(to_server_socket,tab_jeux,sizeof(int)*20,0);
}

void jouer(){
	afficher_matrice (m);
	while (!partie_terminee (m)) {
		choisir_coup (m, &lig, &col, joueur);
		jouer_coup (m, lig, col, joueur);
		afficher_matrice (m);
		if (peut_jouer(m, joueur_suivant(joueur)))
			joueur = joueur_suivant (joueur);
		else
		 printf ("\nLe joueur %d passe son tour\n", joueur_suivant(joueur));
		calculer_score(m,&score1,&score2);
		printf("il y a %d pions du joueur 1 \n et %d du joueur 2 \n",score1,score2);
	}
}

int main (int argc,char **argv){
	//struct socka_addr permet de configurer la connexion (contexte d'addressage)
	struct sockaddr_in serveur_addr;
	struct hostent *serveur_info;
	long hostAddr;
	char buffer[512];
	int to_server_socket;

	bzero(&serveur_addr,sizeof(serveur_addr));
	hostAddr = inet_addr(SERVEURNAME);
	if ( (long)hostAddr != (long)-1 ){
		bcopy(&hostAddr,&serveur_addr.sin_addr,sizeof(hostAddr));
	} else {
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
	if(connect( to_server_socket, (struct sockaddr *)&serveur_addr, sizeof(serveur_addr)) < 0 ) {
		printf("Impossible de se connecter au serveur\n");
	  	exit(0);
	}
	/* envoie de données et reception */
	printf("Connexion avec le serveur reussi!\n");

    /* Un menu pour faire differentes actions */
	char choix;
	int i=0;
	int tab_jeux[20];
	t_matrice m;

	do {
		choix = menu();
		switch(choix){
			case 'm':
				jouer();
				break;
			case 'q':
				quitter(to_server_socket);
				break;
			default:
				printf("Commande '%c' invalide... recommencez\n", choix);
				break;
		}
		//read(to_server_socket,tab_jeux,sizeof(int)*20);
		recv(to_server_socket,&tab_jeux,sizeof(int)*20,0);
		i++;

	} while (choix != 'q' || i <20);

	/* fermeture de la connexion */
	shutdown(to_server_socket,2);
	close(to_server_socket);
	return 0;
}
