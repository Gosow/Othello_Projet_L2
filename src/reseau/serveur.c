/**
 * \file serveur.c
 * \brief Fichier qui contient la fonction serveur du réseau.
 * \author Fatnassi Mendy, Mario Hotaj
 * \date 15 avril 2019 (dernière modif.)
 * \version 2
 */

#include "reseau.h"

/**
 * \brief Mise en route du serveur pour reception
 * \param char* msg : adresse pour la recption du message
 * \param int port : port de communication
 */
void recevoir(char* msg,int port){
	char buffer[1024];
  int sockfd;
  struct sockaddr_in si_me, si_other;
  //char buffer[1024];
  socklen_t addr_size;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  memset(&si_me, '\0', sizeof(si_me));
  si_me.sin_family = AF_INET;
  si_me.sin_port = htons(port);
  si_me.sin_addr.s_addr = inet_addr(IP);

  bind(sockfd, (struct sockaddr*)&si_me, sizeof(si_me));
  addr_size = sizeof(si_other);
  recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)& si_other, &addr_size);
  printf("[+]Data Received: %s", buffer);
  memset(msg, '\0', sizeof(*msg));
	strcpy(msg,buffer);
  close(sockfd);
}