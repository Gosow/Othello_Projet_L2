
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
}