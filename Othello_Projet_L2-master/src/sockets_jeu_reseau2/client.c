#include "socket.h"

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

void envoyer_message(int to_server_socket){
	char msg[200], buffer[512];
	printf("quel est votre message : ");
	scanf(" %[^\n]s", buffer);
	sprintf(msg, "MSG %s", buffer);
	send(to_server_socket, msg, strlen(msg), 0); //on augmente la taille de 4 pour l'entête
	// lecture de la réponse
	memset(buffer, 0, sizeof(buffer));
	recv(to_server_socket,buffer,512,0);
	printf("[client] reponse du serveur : '%s'\n", buffer);
}

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
	int score1=0,score2=0;
	char *joueur=malloc(sizeof(char));
	//struct socka_addr permet de configurer la connexion (contexte d'addressage)
	struct sockaddr_in serveur_addr;
	struct hostent *serveur_info=malloc(sizeof(struct hostent));
	long hostAddr=0;
	char buffer[512];
	int to_server_socket=0;

	*joueur=BLANC;

	//Initialisation du jeux
	init_client(serveur_addr,serveur_info ,hostAddr,to_server_socket);
	init_matrice(m);

	afficher_matrice(m);

	while (!partie_terminee (m)) {

		envoyer_crd(to_server_socket,m,buffer,joueur,&score1,&score2);
		afficher_matrice(m);
		recep_crd(to_server_socket,m,buffer,joueur);
		afficher_matrice(m);
	}
	/* fermeture de la connexion */
	quit_client (to_server_socket);
}

int main(void){

	jeux_reseaux_c();
	return 0;
}