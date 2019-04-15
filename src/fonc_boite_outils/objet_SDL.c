/**
 * \file objet_SDL.c
 * \brief Regroupe les fonctions pour la mise en place des objets SDL
 * \author Mario Hotaj
 */

#include "objet_SDL.h"
#define EGALITE 'E'

static SDL_Color couleurNoire = {0, 0, 0, 0};

/**
 * \brief transforme et positionne l'objet texte afin de pouvoir être
 * \param char* s : texte
 * \param int size : police d'écriture
 * \param int x : position x de l'objet texte
 * \param int y : position y de l'objet texte
 * \return obj : objet SDL
 */
obj obj_text(char* s,int size,int x,int y){
    obj res;

    res.tex = tex_text("src/ttf/PoliceMenu.ttf",size,s,couleurNoire);
    res.rect.x = x;
    res.rect.y = y;

    SDL_QueryTexture(res.tex, NULL, NULL, &(res.rect.w), &(res.rect.h));

    return res;
}




/**
 * \brief Permet de savoir si la souris pointe dans la zone selectionné
 * \param char* lien : chemin d'accès de l'image
 * \param int x : coordonnée x où pointe la souris
 * \param int y : coordonnée y où pointe la souris
 * \return obj : objet SDL
 */
obj obj_img(char* lien,int x,int y){
    obj res;

    res.tex = tex_img_png(lien);
    res.rect.x = x;
    res.rect.y = y;
    
    SDL_QueryTexture(res.tex, NULL, NULL, &(res.rect.w), &(res.rect.h));

    return res;
}




/**
 * \brief Copier dans le renderer l'objet
 * \param obj pt : objet
 * \return entier True ou False (1 ou 0)
 */
int cpy_render(obj pt){
    SDL_RenderCopy(renderer, pt.tex, NULL, &(pt.rect));
    return 0;
}




/**
 * \brief Renvoi la coordonné x de la postion de l'objet
 * \param obj o : objet
 * \return coordonné x de la postion de l'objet
 */
int x_obj(obj o){
    return o.rect.x;
}



/**
 * \brief Renvoi la coordonné y de la postion de l'objet
 * \param obj o : objet
 * \return coordonné y de la postion de l'objet
 */
int y_obj(obj o){
    return o.rect.y;
}




/**
 * \brief Configure SDL_Rect et la position de l'objet
 * \param SDL_Rect r : zone selectionné
 * \param SDL_Texture* t : texture SDL
 * \param int x : position x
 * \param int y : position y
 */
int config_obj(SDL_Rect* r, SDL_Texture* t, int x, int y){
    r->x = x;
    r->y = y;
    SDL_QueryTexture(t, NULL, NULL, &(r->w), &(r->h));
    return 0;
}
