/* Largeur de la grille */
#define N 8


/* Pions du jeu */
#define VIDE ' '
#define NOIR 'X'  /* joueur 1 */
#define BLANC 'O' /* joueur 2 */

/* Type du plateau de jeu */
typedef char t_matrice[N][N];





void init_matrice (t_matrice m);
void afficher_matrice (t_matrice m) ;
int case_existe (int lig, int col);
int coup_valide (t_matrice m, int lig, int col, int joueur) ;
int peut_jouer (t_matrice m, int joueur) ;
int joueur_suivant (int joueur) ;
void choisir_coup (t_matrice m, int *lig, int *col, int joueur) ;
int partie_terminee (t_matrice m) ;
void jouer_coup (t_matrice m, int lig, int col, int joueur) ;
