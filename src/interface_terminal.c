/**
 * \file gest_aff.C
 * \brief Fichier qui contient toutes les fonctions hors affichage de la matrice et SDL du jeu
 * \author Alkassoum Yacine
 * \version 2
 * \date 10 mars 2019
 **/

#include "header/define.h"
#include "fonc_boite_outils/gest_matrice.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 *\brief LaFonction afficher_matrice est la fonction qui  affiche la grille de jeu
**/
void afficher_matrice (t_matrice m) {
    int i, j;
    char a = 'A';

    /** Lettres **/
    printf ("\n");
    for (i=0; i<N; i++) {
        printf ("  %c ", a);
        a++;
    }

    /** Grille **/
    printf ("\n+");
    for (i=0; i<N; i++)
        printf ("---+");
    printf ("\n");
    for (i=0; i<N; i++) {
        printf ("|");
        for (j=0; j<N; j++)
            if (m[i][j] == BLANC)
                printf ("\033[31m %c \033[0m|", m[i][j]); /** Les blancs en rouge **/
            else
                printf ("\033[34m %c \033[0m|", m[i][j]); /** Les noirs en bleu **/
        printf (" %d\n+", i+1);
        for (j=0; j<N; j++)
            printf ("---+");
        printf ("\n");
    }
}


/* Demander le coup du joueur */
void choisir_coup (t_matrice m, int *lig, int *col, char joueur) {
    char c;
    printf ("\nJoueur %c a vous de jouer\n", joueur);
    printf ("Choisissez une case (ex: A1) :\n");
    scanf ("\n%c", &c);
    /* On transforme les minuscules en majuscules */
    if ((c >= 'a') && (c < 'a'+N))
        c = c + 'A' - 'a';
    (*col) = c - 'A';
    scanf ("%d", lig);
    (*lig)--;
    /* On redemande tant que le coup n'est pas valide */
    while (!coup_valide (m, *lig, *col, joueur)) {
        printf ("\nCe coup n'est pas valide\n");
        printf ("Choisissez une autre case (ex: A1) :\n");
        scanf ("\n%c", &c);
        /* On transforme les minuscules en majuscules */
        if ((c >= 'a') && (c < 'a'+N))
            c = c + 'A' - 'a';
        (*col) = c - 'A';
        scanf ("%d", lig);
        (*lig)--;
    }
}

/* Verifie si la partie est terminee */
int partie_terminee (t_matrice m) {
    int i, j, nb_noir, nb_blanc, cpt;

    /* On compte les pions noirs et les blancs */
    nb_noir = 0;
    nb_blanc = 0;
    for (i=0; i<N; i++) {
        for (j=0; j<N; j++) {
            if (m[i][j] == VIDE && (peut_jouer(m, 1) || peut_jouer(m, 2))) {
                return 0; /* La partie n'est pas finie */
            } else {
                if (m[i][j] == NOIR) nb_noir++;
                else if (m[i][j] == BLANC) nb_blanc++;
            }
        }
    }

    /* Fin de partie, on affiche le gagnant */
    if (nb_noir > nb_blanc)
        printf ("\nLe joueur 1 a gagne !!!\n");
    else if (nb_blanc > nb_noir)
        printf ("\nLe joueur 2 a gagne !!!\n");
    else printf ("\nLes deux joueurs sont a egalite\n");

    /* RAngement des pions par couleur et affichage de la grille */
    cpt = 0;
    for (i=0; i<N; i++)
        for (j=0; j<N; j++) {
            if (cpt < nb_noir)
                m[i][j] = NOIR;
            else if ((cpt >= nb_noir) && (cpt < nb_noir + nb_blanc -1))
                m[i][j] = BLANC;
            else m[i][j] = VIDE;
                cpt++;
        }
    afficher_matrice (m);
    printf ("\n");
    return 1;
}
