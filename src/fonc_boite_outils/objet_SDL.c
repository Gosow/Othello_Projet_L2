/**
 * \file afficher_jeuSDL.c
 * \brief Regroupe les fonctions pour la mise en place du jeu dans un environnement graphique.
 * \author Mario Hotaj
 * \date 4 mars 2019
 */

#include "objet_SDL.h"
#define EGALITE 'E'

static SDL_Color couleurNoire = {0, 0, 0, 0};

obj obj_text(char* s,int size,int x,int y){
    obj res;
  
    res.tex = tex_text("src/ttf/PoliceMenu.ttf",size,s,couleurNoire,renderer);
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
