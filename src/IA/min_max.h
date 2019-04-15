#ifndef __MIN_MAX_H__
#define __MIN_MAX_H__

#include "eval.h"
#include "../header/define.h"
#include "../header/include.h"
#include "../fonc_boite_outils/gest_matrice.h"
#include "../fonc_boite_outils/liste.h"

int eval(t_matrice m, char c);
void tour_ordi(t_matrice mat, int* x, int* y);
int alphabeta(t_matrice mat, int depth, int alpha, int beta, char noeud);
int point(t_matrice m , char couleur);
int fonc_eval(t_matrice mat, char couleur);
int partie_termineebis(t_matrice mat);

#endif
