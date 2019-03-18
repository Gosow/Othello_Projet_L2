#include "define.h"
#include "min_max.h"
#include "gest_aff.h"
#include "gest_matrice.h"

static t_coord bestMove;


/*
//fonction qui retourne le nombre de points par rapport a un coup, plus le return est grand et plus le coup est interressant
int point(t_matrice m , int couleur)
{	
	int pt_coins=250;//points des coins(rapportent le plus)
	int pt_ctr_2=75;//points cotes plt
	int pt_ctr_1=125;// point pour les cotés du plateau cotes du plateau
	int pt_centre_plt = 8;//points pour le centre du plateau
    int i,j;//compteurs ines/jonnes
    int cpt,calc;//compteurs de points
    int b_d=0, h_d=0,b_g=0,h_g=0;//haut gauche/droit , bas gauche/droit
    /*chaque case jouable est susceptible de rapporter des points*/
/*	for(i=0;i<N;i++){
		for(j=0;j<N;j++)
		{
			if(coup_valide(m,i,j,couleur))
			{
				cpt+=2;
			}

		}
	}

	//la difference de nombre entre les pions rapporte aussi des points

		calc+=//fonction qui compte le nombre de pions d une couleur donnée;
		calc-=//meme fonction avec une operation ternaire ppour prendre l inverse , ou un if

		cpt+= calc;

		//le fait d'avoir certaines cases rapporte plus de points que d autres
		//exemple les coins

	if(m[N-1][N-1] == couleur){
		b_d = 1;
		cpt += pt_coins;
	}
	
	
	if(m[0][N-1] == couleur){
		h_d = 1;
		cpt += pt_coins;
	}
	if(m[0][0] == couleur){
		h_g = 1;
		cpt += pt_coins;
	}
	if(m[N-1][0] == couleur){
		b_g = 1;
		cpt += pt_coins;
	}
	

	//points des cotés de plateau

	if(h_g != 1){
		i = 1;
		j = 1;
		if(m[i][j] == couleur)
			cpt -= pt_ctr_1;
		while(i < N-1){
			if(m[i][0] == couleur)
				cpt -= pt_ctr_2;
			i++;
		}
		while(j < N-1){
			if(m[0][j] == couleur)
				cpt -= pt_ctr_2;
			j++;
		}
	
	}
	else {
		i = 1;
		j = 1;
		while(m[i][0] == couleur && i < N-1){
			cpt += pt_ctr_1;
			i++;
		}
		while(m[0][j] == couleur && j < N-1){
			cpt += pt_ctr_1;
			j++;
		}
		

	}
	if(1 == b_d){
		i = N-2;
		j = N-2;
		while(m[i][N-1] == couleur && i > 0){
			cpt += pt_ctr_1;
			i--;
		}
		while(m[N-1][j] == couleur && j > 0){
			cpt += pt_ctr_1;
			j--;
		}
			
	}
	else{
		i = N-2;
		j = N-2;
		if(m[i][j] == couleur)
			cpt -= pt_ctr_1;
		
		while(i > 0){
			if(m[i][N-1] == couleur)
				cpt += pt_ctr_2;
			i--;
		}
	
		while(j > 0){
			if(m[N-1][j] == couleur)
				cpt -= pt_ctr_2;
			j--;
		}
	}
	
	if(1==h_d){
		j = N-2;
		i = 1;

		while(m[i][N-1] == couleur && i < N-1){
			cpt += pt_ctr_1;
			i++;
		}
		while(m[0][j] == couleur && j > 0){
			cpt += pt_ctr_1;
			j--;
		}
		
	}
	else{
		j = N-2;
		i = 1;
		
		if(m[i][j] == couleur)
			cpt -= pt_ctr_1;
		
		while(i < N-1){
			if(m[i][N-1] == couleur)
				cpt -= pt_ctr_2;
			i++;
		}
		while(j > 0){
			if(m[0][j] == couleur)
				cpt -= pt_ctr_2;
			j--;
		}
	}
	if( 1 ==  b_d ){
		j = 1;
		i = N-2;
		
		while(m[i][0] == couleur && i > 0){
			cpt += pt_ctr_1;
			i--;
		}	

		while(m[N-1][j] == couleur && j < N-1){
			cpt += pt_ctr_1;
			j++;
		}
	}
	else{
		
		j = 1;
		i = N-2;
		if(m[i][j] == couleur)
			cpt -= pt_ctt_list_coordt_list_coordr_1;
		
		while(i > 0){
			if(m[i][0] == couleur)
				cpt -= pt_ctr_2;
			i--;
		}
		while(j < N-1){
			if(m[N-1][j] == couleur)
				cpt -= pt_ctr_2;
			j++;
		}
	}

		// ET ici le centre du plateau(moins de points)


	if(m[N/2][(N/2)-1] == couleur)
		cpt += pt_centre_plt;
	if(m[(N/2)-1][N/2] == couleur)
		cpt += pt_centre_plt;
	if(m[N/2][N/2] == couleur)
		cpt += pt_centre_plt;
	if(m[(N/2)-1][(N/2)-1] == couleur)
		cpt += pt_centre_plt;
//retourne le compteur
	return cpt;
}
*/
/*int adversaire(t_matrice etat_courant, int profondeur, int alpha){

	t_matrice mat = etat_courant	;
	int min = 9999;int v;
	t_list_coord *entete , *ec;

	if(!profondeur || !entete){	
		return eval(mat);								
	}
								
	while(!ec->next)
	{
		jouer_coup(mat,ec->x,ec->y,2);
		if(partie_terminee(mat))return eval(m,couleur);
		t_list_coordmat=etat_courant;
		ec=ec->next;
	}
	ec=entete;
	while(!ec->next){
		mat=etat_courant;
		joueur_coup(mat,ec->x,ec->y,2);
		v=ordi(mat,alpha,profondeur-1);
		min=v<min?v:min;
	}
	return min;	
}										

*/
/*
int ordi(t_matrice etat_courant, int beta, int profondeur){
	int max=-10000, v;
	t_matrice mat = etat_courant;
	t_list_coord *entete, *ec;
	entete=liste_coup(etat_courant);
	ec=entete;

	if(profondeur == 0 || entete == NULL) return eval(mat);

	while(ec->next != NULL){
		jouer_coup(mat,ec->x,ec->y,2);
		if(partie_terminee(mat)) return eval(mat);
		mat = etat_courant;
		ec=ec->next;
	}

	//On met l'élément courant dans l'entete
	ec=entete;
	while(ec->next != NULL){
		mat = etat_courant;
		jouer_coup(mat,ec->x,ec->y,2);
		v=adversaire(mat,beta,profondeur-1);
		if(v>max) max = v;
		if(max>beta) return max;
		ec = ec->next;
	}
	supprimer_liste(entete);
	return max;
}






/*
test DE L'ALPHA BETA
*/



void ajouter_liste(t_list_coord* dest,int x, int y){
	t_list_coord* ec = dest;
	t_list_coord* temp = malloc(sizeof(t_list_coord*));
	temp->x=x;
	temp->y=y;
	temp->next=NULL;
	while(ec != NULL) ec=ec->next;
	ec->next=temp;
}

t_list_coord* liste_coup(t_matrice mat,int joueur){
	int i, j;
	t_list_coord* res = malloc(sizeof(t_list_coord*));
	for(i;i<N;i++){
		for(j;j<N;j++){
			if(coup_valide(mat,i,j,joueur)){
				ajouter_liste(res,i,j);
			}
		}
	}
	return res;
}

void supprimer_liste(t_list_coord* l){
	t_list_coord *temp;
	while(l != NULL){
		temp=l->next;
		free(l);
		l = temp;
	}
}





t_coord tour_ordi(t_matrice mat, int alpha, int beta){
	t_list_coord* list_coord = liste_coup(mat,JBLANC), *ec;
	ec = list_coord;	
	t_coord pos;
	int v, max=-MAX_SCORE;

	while(ec->next != NULL){
		v = alphabeta(mat,DEPTH,-MAX_SCORE,MAX_SCORE,BLANC);
		if(v > max){
			max=v;
			pos.x=ec->x;
			pos.y=ec->y;

		}
		ec = ec->next;
	}
	supprimer_liste(list_coord);
	return pos;
}

int eval(t_matrice m, char c){
	int i, j, cmpt=0;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(m[i][j]==c) cmpt++; 
			else if(m[i][j] != VIDE) cmpt--;
		}
	}
	return cmpt;
};

int alphabeta(t_matrice mat, int depth, int alpha, int beta, int noeud)
{
	t_list_coord *en_tete,*list_coord;
	t_matrice temp;

	if (partie_terminee(mat) || depth <= 0)
		if(noeud == MAX) return eval(mat,BLANC);
		return eval(mat,NOIR);

	if(noeud == MAX){ //Programme
		en_tete = list_coord = liste_coup(mat,JBLANC);
		jouer_coup(mat,bestMove.x, bestMove.y, JBLANC);
    	while(list_coord->next != NULL){
        	jouer_coup(temp, list_coord->x, list_coord->y, JNOIR);
        	int score = alphabeta(temp, depth - 1, alpha, beta, MIN);
        	// ICI temp = mat;
			for(int tt=0;tt<N;tt++)
				for(int ttt=0;ttt<N;ttt++)
					temp[tt][ttt]=mat[tt][ttt];
        	if (score > alpha) {
            	alpha = score;
            	bestMove.x = list_coord->x;
				bestMove.y = list_coord->y;
            	if (alpha >= beta)
            	   break;
        	}
			list_coord = list_coord->next;
      	}
		supprimer_liste(en_tete);
		return alpha;
    } 
    else { //type MIN = adversaire
		en_tete = list_coord = liste_coup(mat,JNOIR);
		jouer_coup(mat,bestMove.x, bestMove.y, JNOIR);
		while(list_coord->next != NULL){
			jouer_coup(temp, list_coord->x, list_coord->y, JBLANC);
			int score = alphabeta(temp, depth - 1, alpha, beta, MAX);
			// ICI temp = mat;
			for(int tt=0;tt<N;tt++)
				for(int ttt=0;ttt<N;ttt++)
					temp[tt][ttt]=mat[tt][ttt];
			if (score < beta) {
				beta = score;
				bestMove.x = list_coord->x;
				bestMove.y = list_coord->y;
				if (alpha >= beta)
					break;
			}
			list_coord = list_coord->next;
		}
		supprimer_liste(en_tete);
    	return beta;
    }
}

void main(void)
{	t_matrice i;
	init_matrice(i);
	t_coord c = tour_ordi(i,MAX_SCORE,-MAX_SCORE);
	fprintf(stderr,"test min max \n");
	printf("%d %d \n ", c.x,c.y);
	
}