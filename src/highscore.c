#include "header/define.h"
#include "highscore.h"
#include <stdio.h>
#include <stdlib.h>



/* fonction qui recupere les 5 premiers scores de chaque joueur*/
void init_highscore(t_highscore hg[10] , char * joueur1 , char * joueur2){
    for(int i=0;i<10;i++){
        if(i<=4){
        
         strcpy(hg[i].name,joueur1);
        }
        else{
         strcpy(hg[i].name,joueur2);
        }
        hg[i].score=-1;
    }
    
}

void write_highscore (t_highscore hg[10],char * joueur , int score){
    /* si il y a de la place dans le tableau*/
    for(int i=0;i<10;i++){
        if(hg[i].score==-1){
            strcpy(hg[i].name,joueur);
            hg[i].score=score;
            return;
        }
    }
    /* sinon on recherche la plus petite valeur , si c est le score la plus petite valeur , on ne l'ajoute pas*/
    int min=score;
    for(int  i=0;i<10;i++){
        min= hg[i].score <=min ?hg[i].score:min;
    }
    if(min==score){
        return;
    }else{
        for(int i=0;i<10;i++){
          if(hg[i].score==min){
            strcpy(hg[i].name,joueur);
            hg[i].score=score;
            return;
             }
        }
    }

    
}
void echanger_hg(t_highscore *a , t_highscore *b){
    t_highscore temp;
                temp = *a;
                *a = *b;
                *b = temp;
}
void trier_hg(t_highscore g[10]){
    t_highscore temp;
     
 
     for (int i=0; i<10; i++)
     {
        for(int j=i; j<10; j++)
        {
            if(g[j].score <g[i].score) 
            {

                echanger_hg(&g[i],&g[j]);
                
            }
        }
 
     }

}

void afficher_hg(t_highscore g[10]){
    trier_hg(g);
    for(int i=0;i<10;i++){
        printf("\n name: %s , score : %d ", g->name , g->score);

    }
}