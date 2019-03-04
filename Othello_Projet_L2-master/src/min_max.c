#include "define.h"
#include "min_max.h"
#include "gest_aff.h"
#include "gest_matrice.h"




//fonction qui retourne le nombre de points par rapport a un coup, plus le return est grand et plus le coup est interressant


int point(t_matrice m , int couleur)
{
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

    
}
