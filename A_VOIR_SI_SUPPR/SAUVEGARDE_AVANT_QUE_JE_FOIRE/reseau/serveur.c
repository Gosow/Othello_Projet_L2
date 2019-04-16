#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<netdb.h>
#include <signal.h>
#include <unistd.h>
char buffer[512];
static int client_socket;

void fin(int sig){
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

int fermer_serv(void){
	shutdown(client_socket,2);
	close(client_socket);
	return 0;
}

int init_serv ( void )
{
	int ma_socket;
	struct sockaddr_in mon_address, client_address;
	unsigned int mon_address_longueur;
	bzero(&mon_address,sizeof(mon_address));
	mon_address.sin_port = htons(30000);
	mon_address.sin_family = AF_INET;
	mon_address.sin_addr.s_addr = htonl(INADDR_ANY);

	char *hostname = "localhost";
    char ip[100];
     
    hostname_to_ip(hostname , ip);
	fprintf(stderr, "%s resolved to %s" , hostname , ip);
	view_ip();

	/* creation de socket */
	if ((ma_socket = socket(AF_INET,SOCK_STREAM,0))== -1) {
		printf("Impossible de créer la socket\n");
		exit(0);
	}

	/* bind serveur - socket */
	bind(ma_socket,(struct sockaddr *)&mon_address,sizeof(mon_address));
	/* ecoute sur la socket */
	listen(ma_socket,5);
	/* accept la connexion */
	mon_address_longueur = sizeof(client_address);
	
    /* on attend que le client se connecte */
	client_socket = accept(ma_socket,
                         (struct sockaddr *)&client_address,
                         &mon_address_longueur);
    return 0;
}

int fin_jeu_serv(void){
	return !((strncmp("j", buffer, 1)==0));
}

unsigned int recv_from_serv(char* msg){
	unsigned int lg;
	memset(buffer, 0, sizeof(buffer));
	lg = recv(client_socket, buffer, 512,0);
	strcpy(msg,buffer);
	return lg;
}

int send_from_serv(char* msg){
	//strcpy(buffer,msg);

	sscanf(msg, "%s", buffer);
	//fprintf(stderr,"ENTREE DANS LE SEND FROM SERV : %s\n",buffer);
	send(client_socket, buffer, strlen(buffer)+4, 0); //on augmente la taille de 4 pour l'entête
	return 0;
}
/*
int main(void){
	init_serv();
	unsigned int lg;
	int quitter=0;
    
	do{
		printf("b");
		memset(buffer, 0, sizeof(buffer));
		lg = recv(client_socket, buffer, 512,0);
		printf("msg : '%s'\n",buffer+2);
		printf("quel est votre message : \n");
		scanf("%s",buffer);
		send(client_socket, buffer, 512, 0);
		
	}while(!fin_jeu_serv());
	
	fermer_reseau();
	return 0;
}*/

