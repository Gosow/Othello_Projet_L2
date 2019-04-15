#ifndef __OBJET_SDL_H__
#define __OBJET_SDL_H__
#include "../interface_graphique/SDL_jeu.h"

typedef struct obj_s{
    SDL_Texture *tex;
    SDL_Rect rect;
}obj;

extern SDL_Window* pWindow;
extern SDL_Renderer *renderer;

//GESTION OBJET
obj obj_text(char* s,int size,int x,int y);
obj obj_img(char* lien,int x,int y);
int cpy_render(obj pt);
int x_obj(obj o);
int y_obj(obj o);

#endif
