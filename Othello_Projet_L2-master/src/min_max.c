#include "define.h"
#include "min_max.h"
#include "gest_aff.h"
#include "gest_matrice.h"




//fonction qui retourne le nombre de points par rapport a un coup, plus le return est grand et plus le coup est interressant
int point(t_matrice m , int couleur)
{	
	int pt_coins=250;//points des coins(rapportent le plus)
	int pt_ctr_2=75;//points cotes plt
	int pt_ctr_1=125;// point pour les cotés du plateau cotes du plateau
	int pt_centre_plt = 8;//points pour le centre du plateau
    int i,j;//compteurs lignes/colonnes
    int cpt,calc;//compteurs de points
    int b_d=0, h_d=0,b_g=0,h_g=0;//haut gauche/droit , bas gauche/droit
    /*chaque case jouable est susceptible de rapporter des points*/
	for(i=0;i<N;i++){
		for(j=0;j<N;j++)
		{
			if(coup_valide(m,i,j,couleur)==1)
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
			cpt -= pt_ctr_1;
		
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

int alphabeta(int profondeur, int alpha, int beta)
{
if (game_over or profondeur <= 0)
return eval();
move meilleur_coup;
for (chaque coup possible m) {
jouer le coup m;
int score = -alphabeta(profondeur - 1, -beta, -alpha)
annuler le coup m;
if (score >= alpha){
alpha = score ;
meilleur_coup = m ;
if (alpha >= beta)
break;
}
}
return alpha;
}

int Min_Max(t_matrice m,int profondeur,int couleur){

	if(partie_terminee(m) || profondeur <=0)
		return point(m,couleur):
	for()
}

void ajouter_liste(t_liste_coord* dest,t_liste_coord* src){
	t_liste_coord* ec = dest;
	while(ec != NULL) ec=ec->next;
	if()
}

t_liste_coord liste_coup(t_matrice mat,int joueur){
	int i, j;
	t_liste_coord* res = malloc(sizeof(t_liste_coord*));
	for(i;i<N;i++){
		for(j;j<N;j++){
			if(coup_valide(mat,i,j,joueur)){
				ajouter_liste()
			}
		}
	}
}

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
	}
	return max;
}