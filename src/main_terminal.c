/**
 * \file main.c
 * \brief Programme Principale en console terminale 
 * \author Alkassoum Yacine
 * \version 1
 * \date 02 avril 2019
 * */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sockets_jeu_reseau/socket.h"


//La fonction main
int main (int argc,char **argv) {
    t_matrice m;
    int lig, col,choix ,score1=0,score2=0;
    char joueur;


//Initialisation du jeux
    init_matrice (m);

    do{
        /* Affichage du menu */
		printf("\nMenu :\n");
		printf(" 1 - Jouer contre Un ami sur le mÃªme ordi\n");
		printf(" 2 - Jouer contre l'ordinateur\n");
		printf(" 3 - Jouer en reseaux contre un ami\n");
        printf(" 4 - Quitter\n");

        scanf("%i",&choix);

    /*deroulement*/
    switch (choix){
        case /* constant-expression */1:
            /* code */
            afficher_matrice (m);
            while (!partie_terminee (m)) {
              choisir_coup (m, &lig, &col, joueur);
              jouer_coup (m, lig, col, joueur);
              afficher_matrice (m);
              if (peut_jouer(m, joueur_suivant(joueur))){
                joueur = joueur_suivant (joueur);
              }
              else{

                printf ("\nLe joueur %d passe son tour\n", joueur_suivant(joueur));

                printf ("\nLe joueur %c passe son tour\n", joueur_suivant(joueur));
                calculer_score(m,&score1,&score2);
                printf("il y a %d pions du joueur 1 \n et %d du joueur 2 \n",score1,score2);
              }
            }
            break;
        case 2: // min max ordi avec fonction
        break;
        case 3:

        break;
        case 4:break;
        default:
            printf("Erreur: votre choix doit etre compris entre 1 et 4\n");
    }

    }while(choix!=4);
    printf("Au revoir !\n");
	return EXIT_SUCCESS;
    }