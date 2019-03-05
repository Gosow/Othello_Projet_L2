#ifndef __TOTEXTURE_H__
#define __TOTEXTURE_H__
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string.h>

SDL_Texture* tex_img_png(char * s, SDL_Renderer* renderer);
SDL_Texture *tex_text(char* font,int size, char* s, SDL_Color color, SDL_Renderer* renderer);

#endif
