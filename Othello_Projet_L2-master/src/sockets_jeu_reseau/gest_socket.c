/**
 * \file gest_aff.C
 * \brief Fichier qui contient toutes les fonctions hors affichage de la matrice et SDL du jeu
 * \author Alkassoum Yacine
 * \version 2
 * \date 10 mars 2019
 **/

#include "socket.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>






/* Fonction qui verifie si le coup est valide */
int coup_valide_sock (t_matrice m, int lig, int col, char *joueur) {
    int i, j, ok;
    char cj, ca;//cj=couleur joueur, ca=couleur autre

    /** Definition des couleurs pour les 2 joueurs **/
    if (*joueur == NOIR) {
        cj = NOIR;
    } else {
        cj = BLANC;
        ca = NOIR;
    }
    if (!case_existe( lig, col) || m[lig][col] != VIDE) return 0;

    /** Vers le haut **/
    i = lig - 1;
    ok = 0;
    while (case_existe(i, col) && m[i][col] == ca) {
        i--;
        ok = 1;
    }
    if (case_existe(i, col) && m[i][col] == cj && ok == 1) return 1;

    /** Vers le bas **/
    i = lig + 1;
    ok = 0;
    while (case_existe(i, col) && m[i][col] == ca) {
        i++;
        ok = 1;
    }
    if (case_existe(i, col) && m[i][col] == cj && ok == 1) return 1;

    /** Vers la gauche **/
    j = col - 1;
    ok = 0;
    while (case_existe(lig, j) && m[lig][j] == ca) {
        j--;
        ok = 1;
    }
    if (case_existe(lig, j) && m[lig][j] == cj && ok == 1) return 1;

    /** Vers la droite **/
    j = col + 1;
    ok = 0;
    while (case_existe(lig, j) && m[lig][j] == ca) {
        j++;
        ok = 1;
    }
    if (case_existe(lig, j) && m[lig][j] == cj && ok == 1) return 1;

    /** Diagonal  vers le haut **/
    i = lig - 1;
    j = col - 1;
    ok = 0;
    while (case_existe(i, j) && m[i][j] == ca) {
        i--;
        j--;
        ok = 1;
    }
    if (case_existe(i, j) && m[i][j] == cj && ok == 1) return 1;

    /** Diagonal  vers le bas **/
    i = lig + 1;
    j = col + 1;
    ok = 0;
    while (case_existe(i, j) && m[i][j] == ca) {
        i++;
        j++;
        ok = 1;
    }
    if (case_existe(i, j) && m[i][j] == cj && ok == 1) return 1;

    i = lig - 1;
    j = col + 1;
    ok = 0;
    while (case_existe(i, j) && m[i][j] == ca) {
        i--;
        j++;
        ok = 1;
    }
    if (case_existe(i, j) && m[i][j] == cj && ok == 1) return 1;

    i = lig + 1;
    j = col - 1;
    ok = 0;
    while (case_existe(i, j) && m[i][j] == ca) {
        i++;
        j--;
        ok = 1;
    }
    if (case_existe(i, j) && m[i][j] == cj && ok == 1) return 1;

    return 0;
}

/**
 *\brief Fonction qui indique si le joueur peut encore jouer */
int peut_jouer_sock (t_matrice m, char *joueur) {
    int i, j;
    for (i=0; i<N; i++)
        for (j=0; j<N; j++)
            if (coup_valide_sock(m, i, j, joueur)) return 1; /* Le joueur peut encore jouer */

    /* Le joueur ne peut plus jouer */
    return 0;
}

/* Retourne le joueur suivant */
char joueur_suivant_sock (char *joueur) {
    if(*joueur == NOIR){
        *joueur = BLANC;
    }
    else{
        *joueur = NOIR;
    }
    printf ("\nC'est au tour du joueur %c de jouer\n", *joueur);
    return (*joueur);
}

/* Demander le coup du joueur */
void choisir_coup_sock (t_matrice m, int *lig, int *col, char *joueur) {
    char c;
    printf ("\nJoueur %c a vous de jouer\n", *joueur);
    printf ("Choisissez une case (ex: A1) :\n");
    scanf ("\n%c", &c);
    /* On transforme les minuscules en majuscules */
    if ((c >= 'a') && (c < 'a'+N))
        c = c + 'A' - 'a';
    *col = c - 'A';
    scanf ("%d", lig);
    *lig=*lig-1;
    /* On redemande tant que le coup n'est pas valide */
    while (!coup_valide(m, *lig, *col, *joueur)) {
        printf ("\nCe coup n'est pas valide\n");
        printf ("Choisissez une autre case (ex: A1) :\n");
        scanf ("\n%c", &c);
        /* On transforme les minuscules en majuscules */
        if ((c >= 'a') && (c < 'a'+N))
            c = c + 'A' - 'a';
        *col = c - 'A';
        scanf ("%d", lig);
        (*lig)--;
        fprintf(stderr, "lig:%d   col:%d\n", *lig,*col );
    }
    //return c;
}

/* Fonction qui permet de jouer un coup */
void jouer_coup_sock (t_matrice m, int lig, int col, char *joueur) {
    int i, j;
    char cj, ca;

    if (*joueur == BLANC) {
        cj = BLANC;
        ca = NOIR;
    } else {
        cj = NOIR;
        ca = BLANC;
    }
    m[lig][col] = cj;

    /* Vers le haut */
    i = lig - 1;
    while (case_existe(i, col) && m[i][col] == ca) i--;
    if (case_existe(i, col) && m[i][col] == cj) {
        i = lig - 1;
        while (m[i][col] == ca) {
            m[i][col] = cj;
            i--;
        }
    }

    /* Vers le bas */
    i = lig + 1;
    while (case_existe(i, col) && m[i][col] == ca) i++;
    if (case_existe(i, col) && m[i][col] == cj) {
        i = lig + 1;
        while (m[i][col] == ca) {
            m[i][col] = cj;
            i++;
        }
    }
    /* Vers la gauche */
    j = col - 1;
    while (case_existe(lig, j) && m[lig][j] == ca) j--;
    if (case_existe(lig, j) && m[lig][j] == cj) {
        j = col - 1;
        while (m[lig][j] == ca) {
            m[lig][j] = cj;
            j--;
        }
    }
    /* Vers la droite */
    j = col + 1;
    while (case_existe(lig, j) && m[lig][j] == ca) j++;
    if (case_existe(lig, j) && m[lig][j] == cj) {
        j = col + 1;
        while (m[lig][j] == ca) {
            m[lig][j] = cj;
            j++;
        }
    }
    /* Diagonal \ vers le haut */
    i = lig - 1;
    j = col - 1;
    while (case_existe(i, j) && m[i][j] == ca) {
        i--;
        j--;
    }
    if (case_existe(i, j) && m[i][j] == cj) {
        i = lig - 1;
        j = col - 1;
        while (m[i][j] == ca) {
            m[i][j] = cj;
            i--;
            j--;
        }
    }
    /* Diagonal \ vers le bas */
    i = lig + 1;
    j = col + 1;
    while (case_existe(i, j) && m[i][j] == ca) {
        i++;
        j++;
    }
    if (case_existe(i, j) && m[i][j] == cj) {
        i = lig + 1;
        j = col + 1;
        while (m[i][j] == ca) {
            m[i][j] = cj;
            i++;
            j++;
        }
    }
    /* Diagonal / vers le haut */
    i = lig - 1;
    j = col + 1;
    while (case_existe(i, j) && m[i][j] == ca) {
        i--;
        j++;
    }
    if (case_existe(i, j) && m[i][j] == cj) {
        i = lig - 1;
        j = col + 1;
        while (m[i][j] == ca) {
            m[i][j] = cj;
            i--;
            j++;
        }
    }
    /* Diagonal \ vers le bas */
    i = lig + 1;
    j = col - 1;
    while (case_existe(i, j) && m[i][j] == ca) {
        i++;
        j--;
    }
    if (case_existe(i, j) && m[i][j] == cj) {
        i = lig + 1;
        j = col - 1;
        while (m[i][j] == ca) {
            m[i][j] = cj;
            i++;
            j--;
        }
    }
}

/* envoyer_crd() & recep_crd fonction commune a client & serveur */
int envoyer_crd(int socket,t_matrice m, int *lig, int *col, char *joueur,int *score1,int *score2,char *buffer){
  char temp = joueur_suivant(*joueur);

	choisir_coup_sock(m,lig,col,joueur);

  if (peut_jouer(m,temp)){
      jouer_coup(m,*lig,*col,*joueur);

      sprintf(buffer,"%d;%d",lig,col);

	  send(socket,buffer,512,0);
      read(socket,joueur,sizeof(char));
      *joueur = temp;
		  return 0;
	}
	else {
		printf ("\nLe joueur %c passe son tour\n", temp);
		calculer_score(m,score1,score2);
		return 1;
	}
}

int recep_crd(int socket,t_matrice m, int *lig, int *col, char *joueur,char *buffer){
   // memset(buffer, 0, sizeof(buffer));
    recv(socket,buffer,512,0);
	write(socket,joueur,sizeof(char));

    sscanf(buffer,"%d;%d",lig,col);

	jouer_coup(m,*lig,*col,*joueur);
	return 0;
}
