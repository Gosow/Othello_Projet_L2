/* prototypes*/
#include "define.h"





void init_matrice (t_matrice m);
int case_existe (int lig, int col);
int coup_valide (t_matrice m, int lig, int col, int joueur) ;
int peut_jouer (t_matrice m, int joueur) ;
int joueur_suivant (int joueur) ;
void choisir_coup (t_matrice m, int *lig, int *col, int joueur) ;
int partie_terminee (t_matrice m) ;
void jouer_coup (t_matrice m, int lig, int col, int joueur) ;
