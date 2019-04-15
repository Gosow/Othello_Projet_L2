#ifndef __RESEAU_H__
#define __RESEAU_H__
#include <fcntl.h> // open function
#include <unistd.h> // close function
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT_HOTE 1234
#define PORT_EXT 4321
#define PORT 1234
#define IP "127.0.0.1"

void recevoir(char* buffer, int port);
void envoyer(char* buffer, int port);

#endif