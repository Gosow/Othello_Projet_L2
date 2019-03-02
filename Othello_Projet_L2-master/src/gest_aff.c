#include "define.h"
#include "gest_aff.h"
#include <stdlib.h>
#include <stdio.h>








/* Fonction qui nous affiche la grille */
void afficher_matrice (t_matrice m) {
    int i, j;
    char a = 'A';

    /* Lettres */
    printf ("\n");
    for (i=0; i<N; i++) {
        printf ("  %c ", a);
        a++;
    }

    /* Grille */
    printf ("\n+");
    for (i=0; i<N; i++)
        printf ("---+");
    printf ("\n");
    for (i=0; i<N; i++) {
        printf ("|");
        for (j=0; j<N; j++)
            if (m[i][j] == BLANC)
                printf ("\033[31m %c \033[0m|", m[i][j]); /* Les blancs en rouge */
            else
                printf ("\033[34m %c \033[0m|", m[i][j]); /* Les noirs en bleu */
        printf (" %d\n+", i+1);
        for (j=0; j<N; j++)
            printf ("---+");
        printf ("\n");
    }
}
