#include "outils.h"


const double epsilon = 1e-10;


inline int bool_max_equals(int a , int b)
{
    //retourne 1 si a est superieur ou egale a b
    if (a >= b)
        return 1;
    else
        return 0;
}

inline int min(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}
inline int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}


int int_cmp(const void* p1, const void* p2)
{
    int i1 = *(const int*)p1;
    int i2 = *(const int*)p2;
    if (i1 < i2)  return -1;
    if (i1 > i2)  return +1;
    return 0;
}

int float_cmp(const void* p1, const void* p2)
{
    double diff = *(double*)p1 - *(double*)p2;
    if (fabs(diff) < epsilon)
        return 0;
    return (diff < 0.) ? -1 : +1;
}

void fct_tridecroitableau(int tableau[], int tailletableau){
     int valeurtemporaire, i, j;

     for (i=0; i<tailletableau; i++){
        for(j=i; j<tailletableau; j++){
            if(tableau[j]>tableau[i]){
                valeurtemporaire = tableau[i];
                tableau[i] = tableau[j];
                tableau[j] = valeurtemporaire;
            }
        }
      }
}
