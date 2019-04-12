#ifndef __MIN_MAX_H__
#define __MIN_MAX_H__

#include "define.h"
#include <stdio.h>
#include <stdlib.h>
#include "gest_matrice.h"

int eval(t_matrice m, char c);
void tour_ordi(t_matrice mat, int* x, int* y);
int alphabeta(t_matrice mat, int depth, int alpha, int beta, char noeud);
int point(t_matrice m , char couleur);
int fonc_eval(t_matrice mat, char couleur);
int partie_termineebis(t_matrice mat);

#endif
