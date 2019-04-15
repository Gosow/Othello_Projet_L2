/**
 * \file client.c
 * \brief Fichier qui contient la fonction client du réseau.
 * \author Fatnassi Mendy, Mario Hotaj
 * \date 15 avril 2019 (dernière modif.)
 */

#include "reseau.h"

/**
 * \brief Mise en route du client pour envoi
 * \param char* msg : message à envoyer
 * \param int port : port de communication
 */
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