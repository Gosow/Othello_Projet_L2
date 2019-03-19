#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "gest_matrice.h"

t_liste* init_liste(void){
	t_liste *p = malloc(sizeof(t_liste*));
    p->drapeau = malloc(sizeof(t_elem_coord));
    p->drapeau->x = p->drapeau->y = -1;
    //ON EST POSITIONNÉ SUR LE DRAPEAU qui est la seule valeur
    p->ec = p->drapeau->next = p->drapeau;
	return p;
}
int liste_vide(t_liste* l){
    fprintf(stderr,"liste vide:%d\n",(l->drapeau->next==l->drapeau) && (l->ec==l->drapeau));
    return (l->drapeau->next==l->drapeau) && (l->ec==l->drapeau);
}

t_elem_coord* en_tete(t_liste* l){
    return l->drapeau->next;
}

void en_tete_ec(t_liste* l){
    l->ec=l->drapeau->next;
}

t_elem_coord* en_queue(t_liste* l){
    t_elem_coord *temp;
    temp = en_tete(l);
    if(liste_vide(l)) return l->drapeau;
    while(temp != l->drapeau){
        fprintf(stderr,"x:%d, y:y%d\n",temp->x,temp->y);
        temp=temp->next;
    };
    
    return temp;
}

void suivant(t_liste* l){
    l->ec=l->ec->next;
} 

void coord_elem(int* x, int* y, t_elem_coord* ec){
    *x=ec->x;
    *y=ec->y;
}
void ajout_liste(t_liste* l, int x, int y){
    t_elem_coord *temp, *nv= malloc(sizeof(t_elem_coord));
    temp=l->drapeau->next;

    nv->x=x;
    nv->y=y;
    nv->next=temp;

    l->drapeau->next=nv;

    /*
    t_elem_coord *temp = malloc(sizeof(t_elem_coord));

    temp->x=x;
    temp->y=y;
    temp->next=l->drapeau;
    fprintf(stderr,"x:%d, y:y%d\n",en_queue(l)->x,en_queue(l)->y);
    en_queue(l)->next=temp;*/
}

void oter_ec(t_liste* l){
    if(liste_vide(l)) return;
    t_elem_coord* temp = en_tete(l);
    l->drapeau->next=temp->next;
    l->ec=l->drapeau;

    free(temp);
}
void supprimer_liste(t_liste* l){
    if(liste_vide(l)) return;
    while(!liste_vide(l)){
        t_elem_coord *ec = en_tete(l);
        l->drapeau->next=ec->next;
        free(ec);
    }
}

int elem_x(t_liste* l){
    return l->ec->x;
}

int elem_y(t_liste* l){
    return l->ec->y;
}

t_liste* liste_coup(t_matrice mat,char joueur){
	int i, j;
	t_liste* res = init_liste();
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			//printf(" \n Liste : %d %d \n ",i,j);
			if(coup_valide(mat,i,j,joueur)){
				ajout_liste(res,i,j);
				//printf(" \n Liste : %d %d \n ",i,j);
			}
		}
	}
	return res;
}

void afficher_liste(t_liste *l,char c)
{
    en_tete_ec(l);
    while(l->ec != l->drapeau){
        fprintf(stderr,"%c joue: x:%d y:%d\n",c,elem_x(l),elem_y(l));
        suivant(l);
    }
	/*t_list_coord *temp=t;
	while(temp){
		printf("x: %d y %d  %c  QUI JOUE MON GAAAARS \n",temp->x,temp->y,c);
		temp=temp->next;

	}*/
}