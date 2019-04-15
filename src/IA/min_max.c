/**
 * \file min_max.c
 * \brief Fichier qui contient toutes les fonctions qui permettent à l'ordinateur de jouer
 * \author Alkassoum Yacine, Hotaj Mario
 * \date 15 avril 2019
 */


#include "min_max.h"

/**
 * \brief Nous indique si la partie est terminée
 * \param t_matrice m : plateau de jeu
 * \return VRAI ou FAUX (1 ou 0)
 */
int partie_termineebis(t_matrice mat){
    int i, j;
    for (i=0; i<N; i++) {
        for (j=0; j<N; j++) {
            if (mat[i][j] == VIDE && ((peut_jouer(mat, BLANC) || peut_jouer(mat, NOIR)))) {
                return 0; /* La partie n'est pas finie */
            }
        }
    }
	return 1;
}




/**
 * \brief Tour le plus intéressant que l'IA va jouer
 * \param t_matrice m : plateau de jeu
 * \param int* x : adresse de la position x que l'on va modifier
 * \param int* y : adresse de la position y que l'on va modifier
 */
void tour_ordi(t_matrice m, int* x, int* y){
	t_liste* l = liste_coup(m,BLANC);
	afficher_liste(l);
	en_tete_ec(l);
	int v, max=-MAX_SCORE;
	t_matrice temp;
	while(!liste_vide(l)){
		copie_mat(m,temp);
		jouer_coup(temp, elem_x(l), elem_y(l), BLANC);
		
		v = alphabeta(temp,DEPTH,-MAX_SCORE,MAX_SCORE,MIN);
		if(v > max){
			max=v;
			fprintf(stderr," MAX : %d\n",max);
			*x=elem_x(l);
			*y=elem_y(l);

		}
		oter_ec(l);
		suivant(l);
	}
}




/**
 * \brief Score MIN ou MAX avec la méthode alpha-beta
 * \param t_matrice m : plateau de jeu
 * \param int depth : profondeur de recherche
 * \param int alpha, int beta
 * \param char noeud : MIN ou MAX
 */
int alphabeta(t_matrice m, int depth, int alpha, int beta, char noeud)
{
	t_liste *l;
	t_matrice temp,mat;
	copie_mat(m,mat);

	if (partie_termineebis(mat) || depth <= 0){
		if(noeud == MAX) return eval(mat,NOIR);
		return eval(mat,BLANC);
	}
	if(noeud == MAX){ //Programme
		l = liste_coup(mat,BLANC);
		afficher_liste(l);
		en_tete_ec(l);
    	while(!liste_vide(l)){ //pour tous les coups possibles
			copie_mat(mat,temp);

			jouer_coup(temp, elem_x(l), elem_y(l), BLANC);
        	int score = alphabeta(temp, depth - 1, alpha, beta, MIN);

			copie_mat(temp,mat);

        	if (score > alpha) {
            	alpha = score;
            	if (alpha >= beta)
            	   break;
        	}
			oter_ec(l);
			suivant(l);
			
      	}
		return alpha;
    } 
    else { //type MIN = adversaire
		l = liste_coup(mat,NOIR);
		afficher_liste(l);
		en_tete_ec(l);
		
		while(!liste_vide(l)){
			
			// ICI temp = mat;
			copie_mat(mat,temp);
			jouer_coup(temp, elem_x(l), elem_y(l), NOIR);
			int score = alphabeta(temp, depth - 1, alpha, beta, MAX);
			
			// ICI mat = temp;
			copie_mat(temp,mat);

			if (score < beta) {
				beta = score;
				if (alpha >= beta)
					break;
			}
			oter_ec(l);
			suivant(l);
		}
    	return beta;
    }
}

