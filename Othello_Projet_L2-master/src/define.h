/* Largeur de la grille */
#ifndef __DEFINE_H__
#define __DEFINE_H__
#define N 8
/* Pions du jeu */
#define VIDE ' '
#define NOIR 'X'  /* joueur 1 */
#define BLANC 'O' /* joueur 2 */

/* Type du plateau de jeu */
typedef char t_matrice[N][N];

/* Liste de coordonnées */
typedef struct s_list_coord t_list_coord;
typedef struct s_list_coord{
	int x;
	int y;
	struct t_list_coord * next;
};
#endif

