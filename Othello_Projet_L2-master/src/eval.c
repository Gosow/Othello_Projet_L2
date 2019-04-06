
#include "define.h"
#include "gest_matrice.h"
//nombre de possibilites du joueur adverse apres que le joueur en cours ai joué un coup

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
int eval(t_matrice mat, char couleur,int *etat){

	int i, j, cpt_final = 0;
	int haut_G = 0, haut_D = 0, bas_G = 0, bas_D = 0;
	char adv = couleur == NOIR ? BLANC : NOIR;
		/** La mobilité : chaque case jouable rapporte des pts **/

	if(*etat <=12){
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
	*etat++;
}
if(et)

return cpt_final;
}
