#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fonc_boite_outils/outils.h"
#include "define.h"
#include "gest_matrice.h"
/*
int high_score(t_matrice m) {
  if(!partie_terminee(m)) {
    return 0;
  }
  i=0;
  else {
    int i,j;
    int max=
    int *score1=0;
    int *score2=0;
    for(i=0;i<N;i++){
      for(j=0;j<N;j++){
        if (m[i][j] == NOIR)
          *score1 += 1;
        else if (m[i][j] == BLANC)
          *score2 += 1 ;
      }
    }
    int top[5]={0};
    i=0;
    FILE *f=fopen("high_scores.txt","r");
    while(i<5 && !eof(f)){
      fscanf(f,%i,top[i]);
      i++;
    }
    fclose(f);
    int score_gagnant = max(*score1,*score2);

    for(i=5;i>0 && top[i] < score_gagnant;i++){
      if(top[i] < score_gagnant){
        top[i]=score_gagnant;
      }
    }

    fct_tridecroitableau(top,5);

    FILE *f=fopen("high_scores.txt","w");
    fclose(f);
    i=0;
    FILE *f=fopen("high_scores.txt","r");
    while(i<5 && !eof(f)){
      fscanf(f,%i,top[i]);
      i++;
    }

  }
}
*/