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
#include "define.h"
#include "gest_mat.h"

//La fonction main
int main (void) {
    t_matrice m;
    int lig, col, joueur = 1;
    int choix;

//Initialisation du jeux
    init_matrice (m);

    do{
        /* Affichage du menu */
		printf("\nMenu :\n");
		printf(" 1 - Jouer contre Un ami sur le même ordi\n");
		printf(" 2 - Jouer contre l'ordinateur\n");
		printf(" 3 - Jouer en reseaux contre un ami\n");
        printf(" 4 - Quitter\n");

        scanf("%i",&choix);

    /*deroulement*/
    switch (choix)
    {
        case /* constant-expression */1:

            /* code */
                afficher_matrice (m);
            while (!partie_terminee (m)) {
            choisir_coup (m, &lig, &col, joueur);
            jouer_coup (m, lig, col, joueur);
            afficher_matrice (m);
            if (peut_jouer(m, joueur_suivant(joueur)))
            joueur = joueur_suivant (joueur);
            else printf ("\nLe joueur %d passe son tour\n", joueur_suivant(joueur));
         }
            break;
        case 2: /*
          while(joueur == BLANC && peut_jouer(m,joueur)){
                                        tour_ordi(m,&lig,&col);
                                        jouer_ordi(m,&lig,&col,joueur);
                                        jouer_coup(m,lig,col,joueur);
                                        if(peut_jouer(m, joueur_suivant(joueur))) joueur=joueur_suivant(joueur);
                                    }// min max ordi avec fonction*/
                                    //jeu avec l"ordi
        break;
        case 3://Sockets
        break;
        case 4:break;
        default:
            printf("Erreur: votre choix doit etre compris entre 1 et 4\n");
    }
    
    }while(choix!=4);
    printf("Au revoir !\n");
	return EXIT_SUCCESS;
} 