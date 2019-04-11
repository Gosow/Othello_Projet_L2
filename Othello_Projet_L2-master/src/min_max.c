//Version ALPHA
#include "define.h"
#include "min_max.h"
#include "gest_matrice.h"
#include "liste.h"

//gcc min_max.c min_max.h gest_matrice.c liste.c gest_matrice.h define.h







int nb_possibilites_adv(t_matrice mat , int x , int y , char coul )
{
    int nb=0;
    t_matrice temp;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            temp[i][j]=mat[i][j];

        }
    jouer_coup(temp,x,y,coul);
    for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(coup_valide(temp, coul=="NOIR"?"BLANC":"NOIR", i, j) == 1)
            nb++;
		}
	}
    return nb;

    }
}

// nb possibilites jouables apres un coup par le joueur coul
int nb_possibilite(t_matrice mat , int x , int y , char couleur){


    int nb=0;
    t_matrice temp;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            temp[i][j]=mat[i][j];

        }
    jouer_coup(temp,x,y,couleur);
    for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(coup_valide(temp, couleur, i, j) == 1)
            nb++;
		}
	}
    return nb;
    }
}

int force(t_matrice m, char couleur){
    int i, total=0;
    //Les coins + diagonale
        total += (m[0][0] == couleur ? 500 : 0);
        total -= (m[1][1] == couleur ? 250 : 0);

        total += (m[0][N-1] == couleur ? 500 : 0);
        total -= (m[1][N-2] == couleur ? 250 : 0);
        
        total += (m[N-1][0] == couleur ? 500 : 0);
        total -= (m[N-2][1] == couleur ? 250 : 0);
        
        total += (m[N-1][N-1] == couleur ? 500 : 0);
        total -= (m[N-2][N-2] == couleur ? 250 : 0);

    //coté du coin
        //coin haut-gauche
            total -= (m[0][1] == couleur ? 150 : 0);
            total -= (m[1][0] == couleur ? 150 : 0);
        //coin haut-droite
            total -= (m[0][N-1] == couleur ? 150 : 0);
            total -= (m[N][1] == couleur ? 150 : 0);
        //coin bas-gauche
            total -= (m[N-1][0] == couleur ? 150 : 0);
            total -= (m[1][N] == couleur ? 150 : 0);
        //coin bas-droite
            total -= (m[N][N-1] == couleur ? 150 : 0);
            total -= (m[N-1][N] == couleur ? 150 : 0);
    
    for(i=0;i<N-1;i+=N-1){
        
        total += (m[i][3] == couleur ? 10 : 0);
        total += (m[i][4] == couleur ? 10 : 0);
        total += (m[3][i] == couleur ? 10 : 0);
        total += (m[4][i] == couleur ? 10 : 0);

        total += (m[i][2] == couleur ? 30 : 0);
        total += (m[i][5] == couleur ? 30 : 0);
        total += (m[2][i] == couleur ? 30 : 0);
        total += (m[5][i] == couleur ? 30 : 0);
    }

    for(i=2;i<5;i+=3){
        total += (m[i][3] == couleur ? 2 : 0);
        total += (m[i][4] == couleur ? 2 : 0);
        total += (m[3][i] == couleur ? 2 : 0);
        total += (m[4][i] == couleur ? 2 : 0);
    }

    total += (m[2][2] == couleur ? 1 : 0);
    total += (m[2][N-3] == couleur ? 1 : 0);
    total += (m[N-3][2] == couleur ? 1 : 0);
    total += (m[N-3][N-3] == couleur ? 1 : 0);

    total += (m[3][3] == couleur ? 16 : 0);
    total += (m[3][4] == couleur ? 16 : 0);
    total += (m[4][3] == couleur ? 16 : 0);
    total += (m[4][4] == couleur ? 16 : 0);
	return total;
}

int nb_coup_poss(t_matrice mat ,char coul )
{
    int nb=0;
    t_matrice temp;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            temp[i][j]=mat[i][j];

        }
    }

    for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(coup_valide(temp, coul, i, j) == 1) nb++;
		}
	}
    return nb;
}

int eval(t_matrice mat, char couleur){

	int i, j, etat;
	int nb_noir, nb_blanc;
	char adv = couleur == NOIR ? BLANC : NOIR;
    float cpt_final=0, materiel, nb_coup_adv, nb_coup_jr, pt_force;
	calculer_score(mat, &nb_noir, &nb_blanc);
    etat = nb_noir + nb_blanc;
    
        /** Le matériel : la différence de pions rapporte des pts **/
	if(couleur == NOIR) materiel = nb_noir - nb_blanc;
	else materiel = nb_blanc - nb_noir;

        /** Verifier si la personne a peu de coup possible à faire **/
    nb_coup_adv = nb_coup_poss(mat,couleur == NOIR ? BLANC : NOIR);

		/** La mobilité : chaque case jouable rapporte des pts **/
    nb_coup_jr = nb_coup_poss(mat,couleur);

        /** La force : la possession de certaines cases rapporte des pts **/
    pt_force = force(mat,couleur == NOIR ? BLANC : NOIR) - force(mat,couleur);



    float avancement = etat/60;
	
    if(partie_termineebis(mat)) return materiel*100;
    
    cpt_final += pt_force * (1.0-avancement) * (etat <= 20 ? 200 : 1);
    cpt_final -= nb_coup_adv * (1.0 - avancement);
    cpt_final += materiel * 200 * avancement;
	//fprintf(stderr,"pt %c: %d",couleur,(int)cpt_final);
    return (int)cpt_final;
}





































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
	t_matrice temp;
	while(!liste_vide(l)){
		//afficher_matrice(mat);
		// ICI temp = mat;
		copie_mat(m,temp);
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
/*
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
*/
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

int fonc_eval(t_matrice mat, char couleur){

	int i, j, cpt_final = 0;
	int haut_G = 0, haut_D = 0, bas_G = 0, bas_D = 0;
	char adv = couleur == NOIR ? BLANC : NOIR;
		/** La mobilité : chaque case jouable rapporte des pts **/

	if(partie_termineebis(mat)){
		return (cpt_final=eval(mat,couleur)*100) ;
	}


	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(coup_valide(mat, couleur, i, j) == 1)
				cpt_final += 2;
			if(coup_valide(mat,adv,i, j) == 1)
				cpt_final -= 2;
		}
	}


		/** Le matériel : la différence de pions rapporte des pts **/
	
	int noir, blanc;
	calculer_score(mat, &noir, &blanc);
	if(couleur == NOIR) cpt_final += noir - blanc;
	else cpt_final += blanc - noir;

		/** La force : la possession de certaines cases rapporte des pts **/
		/** Pts pour les coins du plateau **/
	if(mat[0][0] == couleur){
		haut_G = 1;
		cpt_final += 500;
	}
	if(mat[N-1][N-1] == couleur){
		bas_D = 1;
		cpt_final += 500;
	}
	if(mat[0][N-1] == couleur){
		haut_D = 1;
		cpt_final += 500;
	}
	if(mat[N-1][0] == couleur){
		bas_G = 1;
		cpt_final += 500;
	}

		/** Pts pour les cotés du plateau **/
	if(haut_G == 1){
		i = 1;
		j = 1;
		while(mat[0][j] == couleur && j < N-1){
			cpt_final += 250;
			j++;
		}
		while(mat[i][0] == couleur && i < N-1){
			cpt_final += 250;
			i++;
		}	
	}
	else{
		i = 1;
		j = 1;
		if(mat[i][j] == couleur)
			cpt_final -= 250;
		while(j < N-1){
			if(mat[0][j] == couleur)
				cpt_final -= 150;
			j++;
		}
		while(i < N-1){
			if(mat[i][0] == couleur)
				cpt_final -= 150;
			i++;
		}
	}
	if(bas_D == 1){
		i = N-2;
		j = N-2;
		while(mat[N-1][j] == couleur && j > 0){
			cpt_final += 250;
			j--;
		}
		while(mat[i][N-1] == couleur && i > 0){
			cpt_final += 250;
			i--;
		}	
	}
	else{
		i = N-2;
		j = N-2;
		if(mat[i][j] == couleur)
			cpt_final -= 250;
		while(j > 0){
			if(mat[N-1][j] == couleur)
				cpt_final -= 150;
			j--;
		}
		while(i > 0){
			if(mat[i][N-1] == couleur)
				cpt_final += 150;
			i--;
		}
	}
	if(haut_D == 1){
		i = 1;
		j = N-2;
		while(mat[0][j] == couleur && j > 0){
			cpt_final += 250;
			j--;
		}
		while(mat[i][N-1] == couleur && i < N-1){
			cpt_final += 250;
			i++;
		}	
	}
	else{
		i = 1;
		j = N-2;
		if(mat[i][j] == couleur)
			cpt_final -= 250;
		while(j > 0){
			if(mat[0][j] == couleur)
				cpt_final -= 150;
			j--;
		}
		while(i < N-1){
			if(mat[i][N-1] == couleur)
				cpt_final -= 150;
			i++;
		}
	}
	if(bas_G == 1){
		i = N-2;
		j = 1;
		while(mat[N-1][j] == couleur && j < N-1){
			cpt_final += 250;
			j++;
		}
		while(mat[i][0] == couleur && i > 0){
			cpt_final += 250;
			i--;
		}	
	}
	else{
		i = N-2;
		j = 1;
		if(mat[i][j] == couleur)
			cpt_final -= 250;
		while(j < N-1){
			if(mat[N-1][j] == couleur)
				cpt_final -= 150;
			j++;
		}
		while(i > 0){
			if(mat[i][0] == couleur)
				cpt_final -= 150;
			i--;
		}
	}

		/** Pts pour le centre du plateau **/
	if(mat[N/2][N/2] == couleur)
		cpt_final += 16;
	if(mat[(N/2)-1][N/2] == couleur)
		cpt_final += 16;
	if(mat[N/2][(N/2)-1] == couleur)
		cpt_final += 16;
	if(mat[(N/2)-1][(N/2)-1] == couleur)
		cpt_final += 16;

		/** Verifier si la personne à peu de coup possible à faire **/

		/** Faire la distinction entre partie fini et avantage dans le jeu **/

		/** On renvoie le compteur final **/
	return cpt_final;
}


