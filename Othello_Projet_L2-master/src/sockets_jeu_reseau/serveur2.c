#include "socket.h"


void fin(){//int sig (parametre)
	printf("fin du serveur");
}

int hostname_to_ip(char * hostname , char* ip)
{
    struct hostent *he;
    struct in_addr **addr_list;
    int i;

    if ( (he = gethostbyname( hostname ) ) == NULL)
    {
        // get the host info
        herror("gethostbyname");
        return 1;
    }

    addr_list = (struct in_addr **) he->h_addr_list;

    for(i = 0; addr_list[i] != NULL; i++)
    {
        //Return the first one;
        strcpy(ip , inet_ntoa(*addr_list[i]) );
        return 0;
    }

    return 1;
}


void view_ip()
{
  char s[256];
  struct hostent *host;
  struct in_addr **adr;
  if (!gethostname(s, 256))
    if ((host = gethostbyname(s)) != NULL)
      for (adr = (struct in_addr **)host->h_addr_list; *adr; adr++)
          printf("IP : %s\n", inet_ntoa(**adr));
}

void afficher_tableau(int *tab_jeux){
	int i;
	for(i=0;i<20;i++){
		printf("tab[%d]=%d\n",i,tab_jeux[i]);
	}
}

/*void envoyer_entier(int client_socket,int *tab_jeux,int i){
	int entier;
	printf("[SERVEUR] Quel est votre entier : ");
	scanf("%d",&entier);
	tab_jeux[i]=entier;
	//write(client_socket,tab_jeux,sizeof(int)*20);
	send(client_socket,tab_jeux,sizeof(int)*20,0);
}*/

int jeux_reseaux(t_matrice m,int lig,int col,int joueur,int score1,int score2){
	int ma_socket;
	int client_socket;
	int sock_err;
	//struct socka_addr permet de configurer la connexion (contexte d'addressage)
	struct sockaddr_in mon_address, client_address;
	unsigned int mon_address_longueur, lg;
	bzero(&mon_address,sizeof(mon_address));
	//sin_port sera égal à la valeur retournée par la fonction htons, avec comme paramètre le port utilisé
	mon_address.sin_port = htons(30000);
	mon_address.sin_family = AF_INET;
	//sin_addr.s_addr sera l'IP donnée automatiquement au serveur. Pour le connaître nous utiliserons la fonction htonl avec comme seul paramètre la valeur INADDR_ANY
	mon_address.sin_addr.s_addr = htonl(INADDR_ANY);

	char *hostname = "localhost";
  char ip[100];

  hostname_to_ip(hostname , ip);
	fprintf(stderr, "%s resolved to %s\n" , hostname , ip);
	view_ip();

	/* creation de socket */
	//int socket(int domain, int type, int protocol)
	//avec domain:AF_INET pour TCP/IP et type :SOCK_STREAM si on utilise TCP/IP
	if ((ma_socket = socket(AF_INET,SOCK_STREAM,0))== SOCKET_ERROR) {
		printf("Impossible de créer la socket\n");
		exit(0);
	}
	/* bind serveur - socket */
	//bind permet d'etablir la connexion avec le client
	sock_err=bind(ma_socket,(struct sockaddr *)&mon_address,sizeof(mon_address));
	if(sock_err != SOCKET_ERROR){
		printf("Connexion etablie avec le client\n");
		/* ecoute sur la socket */
		sock_err=listen(ma_socket,client_socket);

		if(sock_err != SOCKET_ERROR){
			/* accept la connexion */
			mon_address_longueur = sizeof(client_address);
		    /* on attend que le client se connecte */
		    //int accept(int socket, struct sockaddr* addr, socklen_t* addrlen);
				//avec sockaddr* :  pointeur sur le contexte d'adressage du client et socklen : taille du contexte d'adressage
				/*int read(numsoc, tampon, nboctets));
				int numsoc : numero de socket
				char *tampon : pointeur sur les donn ́ees re ̧cues par le processus
				int nboctets : nb octets du tampon*/
				/*int write(numsoc, tampon, nboctets)
				int numsoc : numero de socket
				char *tampon : pointeur sur les donn ́ees re ̧cues par le processus
				int nboctets : nb octets du tampon*/
			client_socket = accept(ma_socket,(struct sockaddr *)&client_address,&mon_address_longueur);
			printf("Connexion avec le client réussi!\n");
		}

	}
	//int send(int socket, void* buffer, size_t len, int flags); fonction pour envoyée des informations
	//int recv(int socket, void* buffer, size_t len, int flags); fonction qui recoit des informations
	//buffer : représente un pointeur (tableau) dans lequel résideront les informations à recevoir ou transmettre.
	
	int i=0;
	int quitter=0;

  while(!quitter || i < 20)
	{
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

	shutdown(client_socket,2);
	close(client_socket);
	shutdown(ma_socket,2);
	if(close(ma_socket)==0){
		return 0;	
	}
	else{
		return -1;
	}
	
}

void main (void){
	int lig, col, joueur = 1 ,score1=0,score2=0;
	jeux_reseaux(lig,col,joueur,score1,score2);
}
