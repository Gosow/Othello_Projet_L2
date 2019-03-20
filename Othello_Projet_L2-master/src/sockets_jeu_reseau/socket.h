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
#include "../gest_matrice.h"
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
void envoyer_crd(int to_server_socket);
void quitter(int to_server_socket);
int jeux_reseaux_c(t_matrice m,int lig,int col,char joueur,int score1,int score2);
<<<<<<< HEAD
int quit_serveur(int client_socket,int ma_socket);
void init_client(struct sockaddr_in serveur_addr,struct hostent * serveur_info , long hostAddr,int to_server_socket);

=======
>>>>>>> 84f5893d3ca755d15f5b9aca278b00ff12f891cf

/*serveur*/
void fin();
int hostname_to_ip(char * hostname , char* ip);
void view_ip();
int jeux_reseaux_s(t_matrice m,int lig,int col,char joueur,int score1,int score2);
<<<<<<< HEAD
int quit_serveur(int client_socket,int ma_socket);
void init_serveur(int ma_socket,int client_socket,int sock_err,struct sockaddr_in mon_address ,struct sockaddr_in client_address ,unsigned int mon_address_longueur,unsigned int lg);
=======
>>>>>>> 84f5893d3ca755d15f5b9aca278b00ff12f891cf
