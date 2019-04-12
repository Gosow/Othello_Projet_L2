#ifndef __RESEAU_H__
#define __RESEAU_H__
#define PORT_HOTE 1234
#define PORT_EXT 4321
#define PORT 1234
#define IP "127.0.0.1"

void recevoir(char* buffer, int port);
void envoyer(char* buffer, int port);

#endif