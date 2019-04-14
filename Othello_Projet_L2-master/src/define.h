/* Largeur de la grille */
#ifndef __DEFINE_H__
#define __DEFINE_H__
#define N 8
#define DEPTH 5
#define MAX_SCORE 64
/* Pions du jeu */
#define VIDE ' '
#define NOIR 'X'  /* joueur 1 */
#define BLANC 'O' /* joueur 2 */
#define MAX 'O'
#define MIN 'X'

/* Type du plateau de jeu */
typedef char t_matrice[N][N];

/* Liste de coordonnées */
//typedef struct s_list_coord t_list_coord;
typedef struct s_elem_coord{
	int x;
	int y;
	struct s_elem_coord* next;
}t_elem_coord;

typedef struct s_liste{
	t_elem_coord * drapeau;
	t_elem_coord *ec ;
}t_liste;



#endif

