#include "define.h"
#include "min_max.h"
#include "gest_aff.h"
#include "gest_matrice.h"




//fonction qui retourne le nombre de points par rapport a un coup, plus le return est grand et plus le coup est interressant


int point(t_matrice m , int couleur)
{	
	int pt_coins=500;//points des coins(rapportent le plus)
	int pt_ctr_2=150;//points cotes plt
	int pt_ctr_1=250;// point pour les cotés du plateau cotes du plateau
	int pt_centre_plt = 16;//points pour le centre du plateau
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
		cpt_final += pt_coins;
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
	return cpt_final;
    
}
