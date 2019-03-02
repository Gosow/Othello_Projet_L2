#ifndef TOTEXTURE_H
#define TOTEXTURE_H

SDL_Texture* tex_img_png(char * s, SDL_Renderer* renderer);
SDL_Texture *tex_text(char* font,int size, char* s, SDL_Color color, SDL_Renderer* renderer);

#endif
