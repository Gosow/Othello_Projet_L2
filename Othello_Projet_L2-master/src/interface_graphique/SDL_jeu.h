#ifndef __SDL_JEU_H__
#define __SDL_JEU_H__
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "../gest_matrice.h"
#include "../define.h"
#include "../min_max.h"
#include "./reseau/reseau.h"
#include <string.h>
#include <time.h>
#define SOLO 0
#define DUO 1
#define ONLINE 2
#define QUITTER 3

extern SDL_Window* pWindow;
extern SDL_Renderer *renderer;
Mix_Music *music;
//t_matrice mat;

int song;
//TEXTURE
SDL_Texture* tex_img_png(char * s, SDL_Renderer* renderer);
SDL_Texture* tex_text(char* font,int size, char* s, SDL_Color color, SDL_Renderer* renderer);
void init_jeuSDL(void);

//AFFICHAGE MATRICE / JEU
void afficher_matriceSDL(t_matrice mat, char joueur);
void afficher_cibleSDL(t_matrice mat, int x,int y);
int partie_termineeSDL(t_matrice mat);
char afficher_gagnant(t_matrice mat);
int affichage_partie(t_matrice mat,int modeJeu);

//JEU : INTERFACE GRAPHIQUE
int lancement_jeu(int modeJeu, int type);
int menu_SDL(void);
int pointe(SDL_Rect r, int x, int y);
int config_obj(SDL_Rect* r, SDL_Texture* t, int x, int y);
int choix_type(SDL_Window* pWindow);

#endif
