#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <string.h>



#define SOCKET_ERROR -1
char buffer[512];

void fin(){//int sig parametre
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

void envoyer_entier(int client_socket,int *tab_jeux,int j){
	int entier;

	printf("[SERVEUR] Quel est votre entier : ");
	scanf("%d",&entier);
	tab_jeux[j]=entier;
	//write(client_socket,tab_jeux,sizeof(int)*20);
	send(client_socket,tab_jeux,sizeof(int)*20,0);
}

int main ( void )
{
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
				/*int read(numsoc, tampon, nboctets)
				int numsoc : numero de socket
				char *tampon : pointeur sur les donn ́ees re ̧cues par le processus
				int nboctets : nb octets du tampon*/
				/*int write(numsoc, tampon, nboctets)
				int numsoc : numero de socket
				char *tampon : pointeur sur les donn ́ees re ̧cues par le processus
				int nboctets : nb octets du tampon*/

			client_socket = accept(ma_socket,
	                         (struct sockaddr *)&client_address,
	                         &mon_address_longueur);

			printf("Connexion avec le client réussi!\n");
		}

	}
	//int send(int socket, void* buffer, size_t len, int flags); fonction pour envoyée des informations
	//int recv(int socket, void* buffer, size_t len, int flags); fonction qui recoit des informations
	//buffer : représente un pointeur (tableau) dans lequel résideront les informations à recevoir ou transmettre.
	int tab_jeux[20];
	int j=0;
	int quitter=0;
  while(!quitter || j < 20)
	{
		//read(client_socket,tab_jeux,sizeof(int)*20);
		recv(client_socket,tab_jeux,sizeof(int)*20,0);
		printf("tab[%d]=%d\n",j,tab_jeux[j]);
		j++;
		envoyer_entier(client_socket,tab_jeux,j);
	}

	shutdown(client_socket,2);
	close(client_socket);
	shutdown(ma_socket,2);
	close(ma_socket);
	return 0;
}
