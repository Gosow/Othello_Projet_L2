/* prototypes*/
#include "../define.h"
#include "../gest_matrice.h"


int coup_valide_sock (t_matrice m, int lig, int col, char *joueur) ;
int peut_jouer_sock (t_matrice m, char *joueur);
char joueur_suivant_sock (char *joueur) ;
void choisir_coup_sock(t_matrice m, int *lig, int *col, char *joueur) ;
void jouer_coup_sock (t_matrice m, int lig, int col, char *joueur) ;
int envoyer_crd(int socket,t_matrice m, int *lig, int *col, char *joueur,int *score1,int *score2,char *buffer);
int recep_crd(int socket,t_matrice m, int *lig, int *col, char *joueur,char *buffer);
void envoyer_message(int socket);