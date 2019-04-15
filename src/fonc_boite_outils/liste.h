#include "../header/include.h"
#include "../header/define.h"
#include "./gest_matrice.h"

t_liste* init_liste(void);
int liste_vide(t_liste* l);
t_elem_coord* en_tete(t_liste* l);
void en_tete_ec(t_liste* l);
t_elem_coord* en_queue(t_liste* l);
void suivant(t_liste* l);
void coord_elem(int* x, int* y, t_elem_coord* ec);
void ajout_liste(t_liste* l, int x, int y);
void oter_ec(t_liste* l);
void supprimer_liste(t_liste* l);
int elem_x(t_liste* l);
int elem_y(t_liste* l);
t_liste* liste_coup(t_matrice mat,char joueur);
void afficher_liste(t_liste *l);