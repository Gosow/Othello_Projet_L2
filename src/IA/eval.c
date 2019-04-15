/**
 * \file eval.c
 * \brief Fichier qui contient toutes les fonctions qui permettent les évaluations
 * \author Alkassoum Yacine, Hotaj Mario
 * \date 15 avril 2019
 */

#include "eval.h"

/**
 * \brief Calcul de la force d'une position
 * \param t_matrice m : plateau de jeu
 * \param char couleur : NOIR ou BLANC, couleur du joueur choisi
 * \return Entier représentant la force de la position
 */
int force(t_matrice m, char couleur){
    int i, total=0;
    //Les coins + diagonale
    total += (m[0][0] == couleur ? 500 : 0);
    total -= (m[1][1] == couleur ? 250 : 0);
    
    total += (m[0][N-1] == couleur ? 500 : 0);
    total -= (m[1][N-2] == couleur ? 250 : 0);
    
    total += (m[N-1][0] == couleur ? 500 : 0);
    total -= (m[N-2][1] == couleur ? 250 : 0);
    
    total += (m[N-1][N-1] == couleur ? 500 : 0);
    total -= (m[N-2][N-2] == couleur ? 250 : 0);
    
    //coté du coin
    //coin haut-gauche
    total -= (m[0][1] == couleur ? 150 : 0);
    total -= (m[1][0] == couleur ? 150 : 0);
    //coin haut-droite
    total -= (m[0][N-2] == couleur ? 150 : 0);
    total -= (m[N-1][1] == couleur ? 150 : 0);
    //coin bas-gauche
    total -= (m[N-2][0] == couleur ? 150 : 0);
    total -= (m[1][N-1] == couleur ? 150 : 0);
    //coin bas-droite
    total -= (m[N-2][N-1] == couleur ? 150 : 0);
    total -= (m[N-1][N-1] == couleur ? 150 : 0);
    
    for(i=0;i<N-1;i+=N-1){
        
        total += (m[i][3] == couleur ? 10 : 0);
        total += (m[i][4] == couleur ? 10 : 0);
        total += (m[3][i] == couleur ? 10 : 0);
        total += (m[4][i] == couleur ? 10 : 0);
        
        total += (m[i][2] == couleur ? 30 : 0);
        total += (m[i][5] == couleur ? 30 : 0);
        total += (m[2][i] == couleur ? 30 : 0);
        total += (m[5][i] == couleur ? 30 : 0);
    }
    
    for(i=2;i<5;i+=3){
        total += (m[i][3] == couleur ? 2 : 0);
        total += (m[i][4] == couleur ? 2 : 0);
        total += (m[3][i] == couleur ? 2 : 0);
        total += (m[4][i] == couleur ? 2 : 0);
    }
    
    total += (m[2][2] == couleur ? 1 : 0);
    total += (m[2][N-3] == couleur ? 1 : 0);
    total += (m[N-3][2] == couleur ? 1 : 0);
    total += (m[N-3][N-3] == couleur ? 1 : 0);
    
    total += (m[3][3] == couleur ? 16 : 0);
    total += (m[3][4] == couleur ? 16 : 0);
    total += (m[4][3] == couleur ? 16 : 0);
    total += (m[4][4] == couleur ? 16 : 0);
    return total;
}




/**
 * \brief Compte le nombre de coup possible
 * \param t_matrice m : plateau de jeu
 * \param char couleur : NOIR ou BLANC, couleur du joueur choisi
 * \return Nombre de coup possible
 */
int nb_coup_poss(t_matrice mat ,char coul )
{
    int nb=0;
    t_matrice temp;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            temp[i][j]=mat[i][j];
            
        }
    }
    
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(coup_valide(temp, coul, i, j) == 1) nb++;
        }
    }
    return nb;
}




/**
 * \brief Evaluation de la position
 * \param t_matrice m : plateau de jeu
 * \param char couleur : NOIR ou BLANC, couleur du joueur choisi
 * \return Score de la position
 */
int eval(t_matrice mat, char couleur){
    
    int etat, nb_noir, nb_blanc;
    //char adv = couleur == NOIR ? BLANC : NOIR;
    float cpt_final=0, materiel, nb_coup_adv, nb_coup_jr, pt_force;
    calculer_score(mat, &nb_noir, &nb_blanc);
    etat = nb_noir + nb_blanc;
    
    /** Le matériel : la différence de pions rapporte des pts **/
    if(couleur == NOIR) materiel = nb_noir - nb_blanc;
    else materiel = nb_blanc - nb_noir;
    
    /** Verifier si la personne a peu de coup possible à faire **/
    nb_coup_adv = nb_coup_poss(mat,couleur == NOIR ? BLANC : NOIR);
    
    /** La mobilité : chaque case jouable rapporte des pts **/
    nb_coup_jr = nb_coup_poss(mat,couleur);
    
    /** La force : la possession de certaines cases rapporte des pts **/
    pt_force = force(mat,couleur == NOIR ? BLANC : NOIR) - force(mat,couleur);
    
    
    
    float avancement = etat/60;
    
    if(partie_termineebis(mat)) return materiel*100;
    
    cpt_final += pt_force * (1.0-avancement) * (etat <= 20 ? 200 : 1);
    cpt_final -= nb_coup_adv * (1.0 - avancement);
    cpt_final += materiel * 200 * avancement;
    return (int)cpt_final;
}
