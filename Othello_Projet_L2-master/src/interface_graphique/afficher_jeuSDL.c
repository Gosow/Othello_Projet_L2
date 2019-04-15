/**
 * \file afficher_jeuSDL.c
 * \brief Regroupe les fonctions pour la mise en place du jeu dans un environnement graphique.
 * \author Mario Hotaj
 * \date 4 mars 2019
 */

#include "SDL_jeu.h"
#define EGALITE 'E'

static SDL_Texture *image_caseNorm_tex;
static SDL_Texture *image_casePoss_tex;
static SDL_Texture *image_noir_tex;
static SDL_Texture *image_blanc_tex;
static SDL_Texture *image_cible_tex;
static SDL_Rect imgBtnRect;
static SDL_Color couleurNoire = {0, 0, 0, 0};
/**
 * \fn void init_jeuSDL(SDL_Renderer* renderer)
 * \brief Initialise tout les données nécessaire pour l'affichage du plateau
 * \param SDL_Renderer* renderer : renderer de la page.
 * \return void
 */
void init_jeuSDL(void){
    image_caseNorm_tex = tex_img_png("./img/caseNorm.png",renderer);
    image_casePoss_tex = tex_img_png("./img/casePoss.png",renderer);
    //PION NOIR
    image_noir_tex = tex_img_png("./img/noir.png",renderer);
    //PION BLANC
    image_blanc_tex = tex_img_png("./img/blanc.png",renderer);
    image_cible_tex = tex_img_png("./img/cible.png",renderer);
    //POSITION ET TAILLE CASE
    imgBtnRect.x = 0;
    imgBtnRect.y = 0;
    SDL_QueryTexture(image_caseNorm_tex, NULL, NULL, &(imgBtnRect.w), &(imgBtnRect.h));
}

/**
 * \fn afficher_matriceSDL(int* joueur)
 * \brief Affiche le plateau de jeu avec les pions et affiche les coup possible en fonctions du tour du joueur
 * \param t_matrice mat, char joueur.
 * \return void
 */
void afficher_matriceSDL(t_matrice mat, char joueur, int afficher_seul){
    if(afficher_seul){
        //SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 24, 124, 58, 255);
        SDL_RenderClear(renderer);
    }
    SDL_Texture *temp;
    int i=0,j=0;

    for(i=0;i<N;i++){
        imgBtnRect.y = i*82;
        imgBtnRect.x = 0;
        for(j=0;j<N;j++){
            if(joueur != ' ' && coup_valide(mat,i,j,joueur)){
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
    if(afficher_seul) SDL_RenderPresent(renderer);
}

/**
 * \fn afficher_matriceSDL(int* joueur)
 * \brief La fonction permet de savoir si le jeu est terminé ou non.
 * \param t_matrice
 * \return entier
 */
int partie_termineeSDL(t_matrice mat){
        int i, j, nb_noir, nb_blanc, cpt;

    /* On compte les pions noirs et les blancs */
    nb_noir = 0;
    nb_blanc = 0;
    for (i=0; i<N; i++) {
        for (j=0; j<N; j++) {
            if (mat[i][j] == VIDE && ((peut_jouer(mat, NOIR) || peut_jouer(mat, BLANC)))) {
                return 0; /* La partie n'est pas finie */
            } else {
                if (mat[i][j] == NOIR) nb_noir++;
                else if (mat[i][j] == BLANC) nb_blanc++;
            }
        }
    }

    /* Rangement des pions par couleur et affichage de la grille */
    cpt = 0;
    for (i=0; i<N; i++){
        imgBtnRect.y = i*82;
        imgBtnRect.x = 0;
        for (j=0; j<N; j++) {
            SDL_RenderCopy(renderer, image_caseNorm_tex, NULL, &imgBtnRect);
            if (cpt < nb_noir)
                SDL_RenderCopy(renderer, image_noir_tex, NULL, &imgBtnRect);
            else if ((cpt >= nb_noir) && (cpt < nb_noir + nb_blanc))
                SDL_RenderCopy(renderer, image_blanc_tex, NULL, &imgBtnRect);
            cpt++;
            imgBtnRect.x += 82;
        }
    }
    return 1;
}

/**
 * \fn afficher_matriceSDL(int* joueur)
 * \brief La fonction permet de savoir qui a gagné, et aussi si on a match nul.
 * \param t_matrice
 * \return char soit NOIR, BLANC ou EGALITE qui sont des constantes contenant un caractère.
 */
char afficher_gagnant(t_matrice mat){
    int nb_noir, nb_blanc;
    calculer_score(mat,&nb_noir,&nb_blanc);
    /* Fin de partie, on affiche le gagnant */
    if (nb_noir > nb_blanc) return NOIR;
    else if (nb_blanc > nb_noir) return BLANC;
    else return EGALITE;
};



void afficher_cibleSDL(t_matrice mat, int x,int y){
    SDL_Texture *temp;
    int i=0,j=0;
    SDL_SetRenderDrawColor(renderer, 24, 124, 58, 255);
    SDL_RenderClear(renderer);
    
    for(i=0;i<N;i++){
        imgBtnRect.y = i*82;
        imgBtnRect.x = 0;
        for(j=0;j<N;j++){
            if(i==x && j==y){
                temp = image_cible_tex;
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
    SDL_RenderPresent(renderer);
    sleep(1);
}

int pointe(SDL_Rect r, int x, int y){
    return x>= r.x && x<= (r.x+r.w) && y>=r.y &&y<=(r.y+r.h);
}

int config_obj(SDL_Rect* r, SDL_Texture* t, int x, int y){
    r->x = x;
    r->y = y;
    SDL_QueryTexture(t, NULL, NULL, &(r->w), &(r->h));
    return 0;
}

int choix_type(void){
    const SDL_MessageBoxButtonData buttons[] = {
        { /* .flags, .buttonid, .text */        0, 0, "rejoindre une partie" },
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "héberger une partie" },
        { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "retour" },
    };
    const SDL_MessageBoxColorScheme colorScheme = {
        { /* .colors (.r, .g, .b) */
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
            { 255,   0,   0 },
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
            {   0, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
            { 255, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
            {   0,   0, 255 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            { 255,   0, 255 }
        }
    };
    const SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION, /* .flags */
        NULL, /* .window */
        "À vous de voir ;)", /* .title */
        "Voulez vous créer une partie ou rejoindre une partie déjà crée ?", /* .message */
        SDL_arraysize(buttons), /* .numbuttons */
        buttons, /* .buttons */
        &colorScheme /* .colorScheme */
    };
    int buttonid;


    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
        SDL_Log("Erreur de l'affichage de la box");
        return 1;
    }
    fprintf(stderr,"btn : %d\n",buttonid);
    if (buttonid == -1) {
        SDL_Log("no selection");
    } else {
        SDL_Log("selection was %s", buttons[buttonid].text);
    }
    return buttonid;
}

void aff_joueur_parti(void){
    const SDL_MessageBoxButtonData buttons[] = {
        { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "OK" },
    };
    const SDL_MessageBoxColorScheme colorScheme = {
        { /* .colors (.r, .g, .b) */
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
            { 255,   0,   0 },
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
            {   0, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
            { 255, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
            {   0,   0, 255 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            { 255,   0, 255 }
        }
    };
    const SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION, /* .flags */
        NULL, /* .window */
        "Oh non ! Votre adversaire vient de quitter la partie !", /* .title */
        "Votre adversaire a quitté la partie, votre trop haut niveau étant la cause ;) Mais pas de panique vous pouvez jouer contre notre IA, au moins elle ne partira pas...", /* .message */
        SDL_arraysize(buttons), /* .numbuttons */
        buttons, /* .buttons */
        &colorScheme /* .colorScheme */
    };

    if (SDL_ShowMessageBox(&messageboxdata, NULL) < 0) {
        SDL_Log("Erreur de l'affichage de la box");
    }
}


//OBJETS 
obj obj_text(char* s,int size,int x,int y){
    obj res;
  
    res.tex = tex_text("./ttf/PoliceMenu.ttf",size,s,couleurNoire,renderer);
    res.rect.x = x;
    res.rect.y = y;

    SDL_QueryTexture(res.tex, NULL, NULL, &(res.rect.w), &(res.rect.h));

    return res;
}

obj obj_img(char* lien,int x,int y){
    obj res;

    res.tex = tex_img_png(lien,renderer);
    res.rect.x = x;
    res.rect.y = y;
    
    SDL_QueryTexture(res.tex, NULL, NULL, &(res.rect.w), &(res.rect.h));

    return res;
}

int cpy_render(obj pt){
    SDL_RenderCopy(renderer, pt.tex, NULL, &(pt.rect));
    return 0;
}

int x_obj(obj o){
    return o.rect.x;
}

int y_obj(obj o){
    return o.rect.y;
}
