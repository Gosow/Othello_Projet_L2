#include "define.h"
#include "min_max.h"
#include "gest_matrice.h"
#include "liste.h"

//gcc min_max.c min_max.h gest_matrice.c liste.c gest_matrice.h define.h

/*
test DE L'ALPHA BETA
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



/*
void ajouter_liste(t_list_coord* dest,int x, int y){
	t_list_coord* ec = dest;
	t_list_coord* temp = malloc(sizeof(t_list_coord*));
	temp->x=x;
	temp->y=y;
	temp->next=NULL;
	while(ec->next ) ec=ec->next;
	ec->next=temp;
}
*/

/*
t_liste * creer_liste(void)
{
		new->ec=new;
	new->drapeau=new;
	new->ec->x=
}*/

/*
void supprimer_liste(t_list_coord* l){
	t_list_coord *temp;
	while(l != NULL){
		temp=l->next;
		free(l);
		l = temp;
	}
}
*/

void tour_ordi(t_matrice m, int* x, int* y){
	t_liste* l = liste_coup(m,BLANC);
	afficher_liste(l);
	en_tete_ec(l);
	//ec = l;	
	//t_coord pos;
	int v, max=-MAX_SCORE;
	t_matrice temp,mat;
	copie_mat(m,mat);
	while(!liste_vide(l)){
		//afficher_matrice(mat);
		// ICI temp = mat;
		copie_mat(mat,temp);
		//afficher_matrice(temp);
		jouer_coup(temp, elem_x(l), elem_y(l), BLANC);
		
		v = alphabeta(temp,DEPTH,-MAX_SCORE,MAX_SCORE,MIN);
		// ICI mat = temp;
		//copie_mat(temp,mat);
	
		//fprintf(stderr,"SCORE : %d\n",v);
		if(v > max){
			max=v;
			*x=elem_x(l);
			*y=elem_y(l);

		}
		oter_ec(l);
		suivant(l);
		//ec = ec->next; 
	}
	//supprimer_liste(l);
	//return pos;
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

int alphabeta(t_matrice m, int depth, int alpha, int beta, char noeud)
{
	t_liste *l;
	t_matrice temp,mat;
	copie_mat(m,mat);
	//afficher_matrice(mat);

	if (partie_termineebis(mat) || depth <= 0){
		//fprintf(stderr,"FINI : ter:%d | prof:%d",partie_termineebis(mat),depth <= 0);
		if(noeud == MAX) return eval(mat,NOIR);
		return eval(mat,BLANC);
	}
	if(noeud == MAX){ //Programme
		l = liste_coup(mat,BLANC);
		//fprintf(stderr,"liste BLANC\n");
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
		//supprimer_liste(en_tete);
		//free(temp);
		//free(mat);
		return alpha;
    } 
    else { //type MIN = adversaire
		l = liste_coup(mat,NOIR);
		//fprintf(stderr,"liste NOIR\n");
		afficher_liste(l);
		en_tete_ec(l);
		
		//jouer_coup(mat,bestMove.x, bestMove.y, BLANC);
		
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
			//list_coord = list_coord->next;
		}
		//supprimer_liste(en_tete);
		//free(temp);
		//free(mat);
    	return beta;
    }
}
/*
int main(void)
{
	t_matrice m;
	init_matrice(m);
    int lig, col;
	char joueur = BLANC;
    int choix;
    int score1=0,score2=0;

	afficher_matrice (m);
	while (!partie_terminee (m)) {
		if(joueur == NOIR){
			choisir_coup (m, &lig, &col, joueur);
		}else{
			tour_ordi(m,&lig,&col);
		}
		jouer_coup (m, lig, col, joueur);
		afficher_matrice (m);
		if (peut_jouer(m, joueur_suivant(joueur))){
		joueur = joueur_suivant (joueur);
		}
		else{ 
		printf ("\nLe joueur %d passe son tour\n", joueur_suivant(joueur));
		calculer_score(m,&score1,&score2);
		printf("il y a %d pions du joueur 1 \n et %d du joueur 2 \n",score1,score2);
		}
	}
}
*/
/*
//fonction qui retourne le nombre de points par rapport a un coup, plus le return est grand et plus le coup est interressant
int point(t_matrice m , char couleur)
{	
	int pt_coins=250;//points des coins(rapportent le plus)
	int pt_ctr_2=75;//points cotes plt
	int pt_ctr_1=125;// point pour les cotés du plateau cotes du plateau
	int pt_centre_plt = 8;//points pour le centre du plateau
    int i,j;//compteurs ines/jonnes
    int cpt,calc;//compteurs de points
    int b_d=0, h_d=0,b_g=0,h_g=0;//haut gauche/droit , bas gauche/droit
    //chaque case jouable est susceptible de rapporter des points
	for(i=0;i<N;i++){
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
