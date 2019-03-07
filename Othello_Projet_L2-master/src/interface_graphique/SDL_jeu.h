#ifndef __SDL_JEU_H__
#define __SDL_JEU_H__
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../gest_aff.h"
#include "../gest_matrice.h"
#include "../define.h"
#include <string.h>
#define SOLO 0
#define DUO 1
#define ONLINE 2
#define QUITTER 3

//TEXTURE
SDL_Texture* tex_img_png(char * s, SDL_Renderer* renderer);
SDL_Texture* tex_text(char* font,int size, char* s, SDL_Color color, SDL_Renderer* renderer);

//AFFICHAGE MATRICE
int afficher_matriceSDL(t_matrice mat,SDL_Renderer* renderer);

//JEU : INTERFACE GRAPHIQUE
int lancement_jeu(int modeJeu,t_matrice mat);
int menu_SDL(t_matrice mat);
#endif
