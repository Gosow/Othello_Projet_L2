/**
 * \file liste.c
 * \brief Fichier qui contient toutes les fonctions de gestion de liste
 * \author Hotaj Mario
 **/


#include "liste.h"
/**
 * \brief Initialisation de la liste
 * \return L'adresse de la liste nouvellement crée
 */
t_liste* init_liste(void){
	t_liste *p = malloc(sizeof(t_liste*));
    p->drapeau = malloc(sizeof(t_elem_coord));
    p->drapeau->x = p->drapeau->y = -1;
    //ON EST POSITIONNÉ SUR LE DRAPEAU qui est la seule valeur
    p->ec = p->drapeau->next = p->drapeau;
	return p;
}



/**
 * \brief Verifie si la liste est vide
 * \param t_liste* l : adresse de la liste a vérifier
 * \return entier vrai ou faux (1 ou 0)
 */
int liste_vide(t_liste* l){
    return (l->drapeau->next==l->drapeau) && (l->ec==l->drapeau);
}



/**
 * \brief Renvoi l'en-tête des coordonnées de la liste
 * \param t_liste* l : adresse de la liste
 * \return l'adresse des coordonnées de l'en-tête de la liste pointées
 */
t_elem_coord* en_tete(t_liste* l){
    return l->drapeau->next;
}



/**
 * \brief Renvoi l'adresse de l'en-tête de la liste
 * \param t_liste* l : adresse de la liste
 */
void en_tete_ec(t_liste* l){
    l->ec=l->drapeau->next;
}




/**
 * \brief Renvoi les coordonnées de la queue de liste
 * \param t_liste* l : adresse de la liste
 * \return l'adresse des coordonnées de la queue de liste
 */
t_elem_coord* en_queue(t_liste* l){
    t_elem_coord *temp;
    temp = en_tete(l);
    if(liste_vide(l)) return l->drapeau;
    while(temp != l->drapeau){
        temp=temp->next;
    };
    return temp;
}




/**
 * \brief Renvoi l'élément suivant de la liste
 * \param t_liste* l : adresse de la liste
 */
void suivant(t_liste* l){
    l->ec=l->ec->next;
} 




/**
 * \brief Renvoi les coordonnées de liste
 * \param int* x : adresse de l'entier x à modifier
 * \param int* y : adresse de l''entier y à modifier
 * \param t_elem_coord* ec : adresse de l'élément courant de la liste'
 */
void coord_elem(int* x, int* y, t_elem_coord* ec){
    *x=ec->x;
    *y=ec->y;
}




/**
 * \brief Ajouter de coordonées dans la liste
 * \param t_liste* l : adresse de la liste
 * \param int x : coordonnée x
 * \param int y : coordonnée y
 */
void ajout_liste(t_liste* l, int x, int y){
    t_elem_coord *temp, *nv= malloc(sizeof(t_elem_coord));
    temp=l->drapeau->next;

    nv->x=x;
    nv->y=y;
    nv->next=temp;

    l->drapeau->next=nv;
}




/**
 * \brief Oter l'élément courant de la liste
 * \param t_liste* l : adresse de la liste
 */
void oter_ec(t_liste* l){
    if(liste_vide(l)) return;
    t_elem_coord* temp = en_tete(l);
    l->drapeau->next=temp->next;
    l->ec=l->drapeau;

    free(temp);
}




/**
 * \brief Supprimer la liste
 * \param t_liste* l : adresse de la liste
 */
void supprimer_liste(t_liste* l){
    if(liste_vide(l)) return;
    while(!liste_vide(l)){
        t_elem_coord *ec = en_tete(l);
        l->drapeau->next=ec->next;
        free(ec);
    }
}




/**
 * \brief Renvoi la coordonnée x de la liste
 * \param t_liste* l : adresse de la liste
 * \return coordonée x
 */
int elem_x(t_liste* l){
    return l->ec->x;
}




/**
 * \brief Renvoi la coordonnée y de la liste
 * \param t_liste* l : adresse de la liste
 * \return coordonée y
 */
int elem_y(t_liste* l){
    return l->ec->y;
}




/**
 * \brief Renvoi les coordonnées de la queue de liste
 * \param t_matrice mat : plateau de jeu
 * \param char joueur : NOIR ou BLANC, joueur
 * \return adresse de la liste
 */
t_liste* liste_coup(t_matrice mat,char joueur){
	int i, j;
	t_liste* res = init_liste();
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(coup_valide(mat,i,j,joueur)){
				ajout_liste(res,i,j);
			}
		}
	}
	return res;
}




/**
 * \brief Parcours de la liste
 * \param t_liste* l : adresse de la liste
 */
void afficher_liste(t_liste *l)
{
    en_tete_ec(l);
    while(l->ec != l->drapeau){
        suivant(l);
    }
}