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


int jeux_reseaux_c(t_matrice m,int lig,int col,int joueur,int score1,int score2){ 
	//struct socka_addr permet de configurer la connexion (contexte d'addressage)
	struct sockaddr_in serveur_addr;
	struct hostent *serveur_info;
	long hostAddr;
	//char buffer[512];
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



//Initialisation du jeux
    init_matrice (m);

	
	while (!partie_terminee (m)) {
		afficher_matrice (m);
		choisir_coup (m, &lig, &col, joueur);
		jouer_coup (m, lig, col, joueur);
		afficher_matrice (m);
		if (peut_jouer(m, joueur_suivant(joueur))){
				send(to_server_socket,m,sizeof(t_matrice),0);
				read(to_server_socket,joueur,sizeof(int));
				joueur = joueur_suivant (joueur);
		}
		else {
			printf ("\nLe joueur %d passe son tour\n", joueur_suivant(joueur));
			calculer_score(m,&score1,&score2);
		}
			printf("il y a %d pions du joueur 1 \n et %d du joueur 2 \n",score1,score2);
			recv(to_server_socket,m,sizeof(t_matrice),0);
			write(to_server_socket,joueur,sizeof(int));

	}
	/* fermeture de la connexion */
	shutdown(to_server_socket,2);

	if(close(to_server_socket)==0){
		return 0;	
	}
	else {
		return -1;
	}
	
}


int main(void){
	int lig, col, joueur = 1,score1=0,score2=0;
	t_matrice m;
	
	jeux_reseaux_c(m,lig,col,joueur,score1,score2);


	return 0;
}
