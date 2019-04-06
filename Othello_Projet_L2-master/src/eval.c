
#include "define.h"
#include "gest_matrice.h"
//nombre de possibilites du joueur adverse apres que le joueur en cours ai joué un coup

int nb_possibilites(t_matrice mat , int x , int y , char coul )
{
    int nb=0;
    t_matrice temp;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            temp[i][j]=mat[i][j]

        }
    jouer_coup(temp,x,y,coul);
    for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(coup_valide(mat, coul=="NOIR"?"BLANC":"NOIR", i, j) == 1)
            nb++;
		}
	}
    return nb;

    }
}