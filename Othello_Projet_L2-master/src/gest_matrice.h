/* prototypes*/
#include "define.h"


void init_matrice (t_matrice m);
void afficher_matrice (t_matrice m) ;
int case_existe (int lig, int col);
int coup_valide (t_matrice m, int lig, int col, int joueur) ;
int peut_jouer (t_matrice m, int joueur) ;
int joueur_suivant (char joueur) ;
void choisir_coup (t_matrice m, int *lig, int *col, int joueur) ;
int partie_terminee (t_matrice m) ;
void jouer_coup (t_matrice m, int lig, int col, int joueur) ;
void calculer_score(t_matrice m,int *score1 , int *score2);
void copie_mat(t_matrice src, t_matrice dest);