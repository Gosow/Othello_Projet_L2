#include <stdio.h>
#include "othello.h"



//La fonction main
int main (int argc,char **argv) {
    t_matrice m;
    int lig, col, joueur = 1;

//Initialisation du jeux
    init_matrice (m);
    afficher_matrice (m);

    
    /*deroulement*/
    while (!partie_terminee (m)) {
        choisir_coup (m, &lig, &col, joueur);
        jouer_coup (m, lig, col, joueur);
        afficher_matrice (m);
        if (peut_jouer(m, joueur_suivant(joueur)))
            joueur = joueur_suivant (joueur);
        else printf ("\nLe joueur %d passe son tour\n", joueur_suivant(joueur));
    }
    return 0;
} 
