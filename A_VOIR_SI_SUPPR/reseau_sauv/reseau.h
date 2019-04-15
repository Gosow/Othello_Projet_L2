#ifndef __RESEAU_H__
#define __RESEAU_H__

//SERVEUR

void fin(int sig);
int hostname_to_ip(char * hostname , char* ip);
void view_ip(void);
int fermer_serv(void);
int init_serv(void);
int fin_jeu_serv(void);
unsigned int recv_from_serv(char* msg);
int send_from_serv(char* msg);

//CLIENT

char* envoyer_message(char* msg, char* buffer);
void quitter(int to_server_socket);
int fermer_client(void);
int init_client(void);


#endif