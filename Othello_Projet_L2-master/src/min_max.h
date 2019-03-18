#ifndef __MIN_MAX_H
#define __MIN_MAX_H__
#define JNOIR 1
#define JBLANC 2
#include "define.h"
#include <stdio.h>
#include <stdlib.h>
#include "gest_aff.h"
#include "gest_matrice.h"

int eval(t_matrice m, char c);
t_list_coord* liste_coup(t_matrice mat , int joueur);
#endif
