#include "header/define.h"
#include "highscore.h"
#include <stdio.h>
#include <stdlib.h>


static typedef char* string;
/* fonction qui recupere les 5 premiers scores de chaque joueur*/
void init_highscore(t_highscore hg[10] , string joueur1 , string joueur2){
    for(int i=0;i<10;i++){
        if(i<5){
         strcpy(hg[i]->nom,joueur1,;
        }
        else{
         strcpy(hg[i]->nom,joueur2);
        }
        hg[i].score=-1;
    }
    
}

void write_highscore (t_highscore hg[10],string joueur , int score){
    /* si il y a de la place dans le tableau*/
    for(int i=0;i<10;i++){
        if(hg[i].score==-1){
            strcpy(hg[i]->nom,joueur);
            hg[i].score=score;
            return;
        }
    }
    /* sinon on recherche la plus petite valeur , si c est le score la plus petite valeur , on ne l'ajoute pas*/
    for(int min=score, i=0;i<10;i++){
        min= hg[i].score< =min ?hg[i].score:min;
    }
    if(min==score){
        return
    }else{
        for(int i=0;i<10;i++){
          if(hg[i].score==min){
            strcpy(hg[i]->nom,joueur);
            hg[i].score=score;
            return;
             }
        }
    }

    
}