#include "SDL_jeu.h"
#define EGALITE 'E'

static SDL_Texture *image_caseNorm_tex;
static SDL_Texture *image_casePoss_tex;
static SDL_Texture *image_noir_tex;
static SDL_Texture *image_blanc_tex;
static SDL_Rect imgBtnRect;
static SDL_Renderer *renderer_temp;

void init_texture(SDL_Renderer* renderer){
    image_caseNorm_tex = tex_img_png("./img/caseNorm.png",renderer);
    image_casePoss_tex = tex_img_png("./img/casePoss.png",renderer);
    //PION NOIR
    image_noir_tex = tex_img_png("./img/noir.png",renderer);
    //PION BLANC
    image_blanc_tex = tex_img_png("./img/blanc.png",renderer);
    //POSITION ET TAILLE CASE
    imgBtnRect.x = 0;
    imgBtnRect.y = 0;
    SDL_QueryTexture(image_caseNorm_tex, NULL, NULL, &(imgBtnRect.w), &(imgBtnRect.h));
    //
    renderer_temp=renderer;
}

void afficher_matriceSDL(t_matrice mat,SDL_Renderer* renderer,int* joueur){
    SDL_Texture *temp;
    int i=0,j=0;

    for(i=0;i<N;i++){
        imgBtnRect.y = i*82;
        imgBtnRect.x = 0;
        for(j=0;j<N;j++){
            if(coup_valide(mat,i,j,*joueur)){
                temp = image_casePoss_tex;
            }else{
                temp = image_caseNorm_tex;
            }
            SDL_RenderCopy(renderer, temp, NULL, &imgBtnRect);
            if(mat[i][j] == NOIR){
                SDL_RenderCopy(renderer, image_noir_tex, NULL, &imgBtnRect);
            }
            else if(mat[i][j] == BLANC){
                SDL_RenderCopy(renderer, image_blanc_tex, NULL, &imgBtnRect);
            }
            imgBtnRect.x += 82;
        }
    }
}

int partie_termineeSDL(t_matrice m){
        int i, j, nb_noir, nb_blanc, cpt;

    /* On compte les pions noirs et les blancs */
    nb_noir = 0;
    nb_blanc = 0;
    for (i=0; i<N; i++) {
        for (j=0; j<N; j++) {
            if (m[i][j] == VIDE && ((peut_jouer(m, 1) || peut_jouer(m, 2)))) {
                return 0; /* La partie n'est pas finie */
            } else {
                if (m[i][j] == NOIR) nb_noir++;
                else if (m[i][j] == BLANC) nb_blanc++;
            }
        }
    }

    /* Rangement des pions par couleur et affichage de la grille */
    cpt = 0;
    for (i=0; i<N; i++){
        imgBtnRect.y = i*82;
        imgBtnRect.x = 0;
        for (j=0; j<N; j++) {
            SDL_RenderCopy(renderer_temp, image_caseNorm_tex, NULL, &imgBtnRect);
            if (cpt < nb_noir)
                SDL_RenderCopy(renderer_temp, image_noir_tex, NULL, &imgBtnRect);
            else if ((cpt >= nb_noir) && (cpt < nb_noir + nb_blanc))
                SDL_RenderCopy(renderer_temp, image_blanc_tex, NULL, &imgBtnRect);
            cpt++;
            imgBtnRect.x += 82;
        }
    }
    return 1;
}

void damier_gagnantSDL(){
    
};

char afficher_gagnant(t_matrice mat, SDL_Renderer* renderer){
    int i, j, nb_noir, nb_blanc, cpt;
    SDL_Rect rect;
    char winner;
    calculer_score(mat,&nb_noir,&nb_blanc);
    /* Fin de partie, on affiche le gagnant */
    if (nb_noir > nb_blanc) return NOIR;
    else if (nb_blanc > nb_noir) return BLANC;
    else EGALITE;
};