#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "reseau.h"

void envoyer(char* msg,int port){
	char buffer[1024];
	strcpy(buffer,msg);
  int sockfd;
  struct sockaddr_in serverAddr;
  //socklen_t addr_size;

  sockfd = socket(PF_INET, SOCK_DGRAM, 0);
  memset(&serverAddr, '\0', sizeof(serverAddr));

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port);
  serverAddr.sin_addr.s_addr = inet_addr(IP);
  memset(buffer, '\0', sizeof(*buffer));
  sscanf(msg,"%s",buffer);
  printf("\n[+]Data BEFORE Send: %s\n", buffer);
  sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
  printf("\n[+]Data Send: %s\n", buffer);
  close(sockfd);
}