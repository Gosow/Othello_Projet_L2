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
#include "../gest_aff.h"
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
int jeux_reseaux_c(t_matrice m,int lig,int col,int joueur,int score1,int score2);

/*serveur*/
void fin();
int hostname_to_ip(char * hostname , char* ip);
void view_ip();
int jeux_reseaux_s(t_matrice m,int lig,int col,int joueur,int score1,int score2);