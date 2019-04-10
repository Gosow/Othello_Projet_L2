/*client*/
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/*serveur*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*Module cummun a client et serveur*/
#include "../define.h"
#include "gest_socket.h"
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <signal.h>

//#define SERVEURNAME "192.168.1.106" // adresse IP de mon serveur
#define SERVEURNAME "127.0.0.1" // adresse IP de mon serveur
//#define SERVEURNAME "172.18.41.139" // adresse IP de mon serveur
//#define SERVEURNAME "127.0.0.1" // adresse IP de mon serveur

#define QUITTER "QUITTER"
#define SOCKET_ERROR -1

/*client*/
char menu();
void init_client(struct sockaddr_in serveur_addr,struct hostent * serveur_info , long hostAddr,int to_server_socket);
int quit_client(int to_server_socket);
void jeux_reseaux_c();


/*serveur*/
void fin();
int hostname_to_ip(char * hostname , char* ip);
void view_ip();
void init_serveur(int ma_socket,int client_socket,int sock_err,struct sockaddr_in mon_address ,struct sockaddr_in client_address ,unsigned int mon_address_longueur,unsigned int lg);
int quit_serveur(int client_socket,int ma_socket);
void jeux_reseaux_s();
