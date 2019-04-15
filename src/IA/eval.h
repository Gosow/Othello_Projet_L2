#ifndef __EVAL_H__
#define __EVAL_H__
#include "../header/define.h"
#include "../fonc_boite_outils/gest_matrice.h"
#include "min_max.h"

int force(t_matrice m, char couleur);
int nb_coup_poss(t_matrice mat ,char coul);
int eval(t_matrice mat, char couleur);

#endif
