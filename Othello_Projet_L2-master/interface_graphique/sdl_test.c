#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

SDL_Texture* tex_img_png(char * s, SDL_Renderer* renderer){

    SDL_RWops *rwop=SDL_RWFromFile(s, "rb");
	SDL_Surface *image=IMG_LoadPNG_RW(rwop);
	if(!image) {
	     printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
	}
	SDL_Texture *image_btn_tex = SDL_CreateTextureFromSurface(renderer, image); 
	if(!image_btn_tex){
		fprintf(stderr, "Erreur à la création du rendu de l'image : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_FreeSurface(image); /* on a la texture, plus besoin de l'image */
    return image_btn_tex;
}

SDL_Texture *tex_text(char* font,int size, char* s, SDL_Color color, SDL_Renderer* renderer){
    SDL_Rect txtDestRect;
    TTF_Font *policeTitre = NULL;
	if( (policeTitre = TTF_OpenFont(font, size)) == NULL){
        fprintf(stderr, "erreur chargement font\n");
        exit(EXIT_FAILURE);
    }
    SDL_Surface *texte = TTF_RenderUTF8_Blended(policeTitre, s, color);
    if(!texte){
        fprintf(stderr, "Erreur à la création du texte : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Texture *texte_tex = SDL_CreateTextureFromSurface(renderer, texte);
    if(!texte_tex){
        fprintf(stderr, "Erreur à la création du rendu du texte : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_FreeSurface(texte); /* on a la texture, plus besoin du texte */
    TTF_CloseFont(policeTitre); /* Doit être avant TTF_Quit() */
    return texte_tex;
}

int main(int argc, char** argv)
{
	int x,y;
    //Le pointeur vers la fenetre
	SDL_Window* pWindow = NULL;
	//Le pointeur vers la surface incluse dans la fenetre
    SDL_Surface *texte=NULL, *texteMenu[4], *image=NULL, *imageBG=NULL;
	SDL_Renderer *renderer=NULL;
	SDL_Rect txtDestRect, txtMenuRect[4], imgBtnRect, imgBtnHoverRect, imgBGRect;

	// Le pointeur vers notre policeTitre
	TTF_Font *policeTitre = NULL, *policeMenu = NULL;
	// Une variable de couleur noire
	SDL_Color couleurNoire = {0, 0, 0};

    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    } 

	/* Initialisation TTF */
	if(TTF_Init() == -1) {
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}


	/* Création de la fenêtre */
	pWindow = SDL_CreateWindow("Othello : DELUXE EDITION",SDL_WINDOWPOS_UNDEFINED,
												  SDL_WINDOWPOS_UNDEFINED,
												  1080,
												  650,
												  SDL_WINDOW_SHOWN);

	if(!pWindow){
		fprintf(stderr, "Erreur à la création de la fenetre : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}


	renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL){
		fprintf(stderr, "Erreur à la création du renderer\n");
		exit(EXIT_FAILURE);
	}
	SDL_Texture *texte_tex= tex_text("ChowFun2.ttf",100,"Othello",couleurNoire,renderer);
	SDL_Texture *texteMenu_tex[4];
	texteMenu_tex[0] = tex_text("MenuPolice.ttf",40,"Solo",couleurNoire,renderer);
	texteMenu_tex[1] = tex_text("MenuPolice.ttf",40,"Duo",couleurNoire,renderer);
	texteMenu_tex[2] = tex_text("MenuPolice.ttf",40,"En ligne",couleurNoire,renderer);
	texteMenu_tex[3] = tex_text("MenuPolice.ttf",40,"Quitter",couleurNoire,renderer);

	//Position ou sera mis le texte dans la fenêtre 
    txtDestRect.x = 300;
	txtDestRect.y = 10;
	SDL_QueryTexture(texte_tex, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));

	for(int j=0;j<4;j++){
		
		if(j==2 || j==3){
			txtMenuRect[j].x = 480;
		}else{
			txtMenuRect[j].x = 500;
		}
		txtMenuRect[j].y = 165+90*j;
		SDL_QueryTexture(texteMenu_tex[j], NULL, NULL, &(txtMenuRect[j].w), &(txtMenuRect[j].h));
	}


	//Chargement de l'image de fond
	SDL_Texture *image_BG_tex = tex_img_png("./img/OthelloBG.png",renderer);
	//Chargement de l'image bouton
	SDL_Texture *image_btn_tex = tex_img_png("./img/btn.png",renderer);
	//Chargement de l'image bouton (utilisé quand la souris passe sur l'image)
	SDL_Texture *image_btnHover_tex = tex_img_png("./img/btnHover.png",renderer);
	
	SDL_Texture *temp;
	int i=0;
	int numBtn = 0;

	if( pWindow )
	{
		int running = 1; 
		while(running) { 
			SDL_Event e; 
			SDL_GetMouseState(&x,&y);
			if(x<700 && 385<x && y<526 && 130<y) goto etiq1;
			//printf("x:%i y:%i\n",x,y);
			
			while(SDL_PollEvent(&e)) { 
				switch(e.type) { 
					case SDL_QUIT: running = 0; 
					break;
					case SDL_MOUSEBUTTONDOWN:
						//printf("Ok%i\n",i++);
						goto etiq1;
					case SDL_WINDOWEVENT:
						etiq1:
						/* Le fond de la fenêtre sera blanc */
						//SDL_SetRenderDrawColor(renderer, 24, 124, 58, 255);
						SDL_RenderClear(renderer);

						//BACKGROUND
						imgBGRect.x = 0;
						imgBGRect.y = 0;
						SDL_QueryTexture(image_BG_tex, NULL, NULL, &(imgBGRect.w), &(imgBGRect.h));
						SDL_RenderCopy(renderer, image_BG_tex, NULL, &imgBGRect);

                        /* Ajout du texte en noir */
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
								
                        SDL_RenderCopy(renderer, texte_tex, NULL, &txtDestRect);
						SDL_RenderDrawLine(renderer,0,130,1080,130);
						
                        /* Ajout du premier bouton à une certaine position */
                        imgBtnRect.x = 440;
						imgBtnRect.y = 150;
						
						/* Bouton 1 : souris au dessus */
						if(x<620 && 440<x && y<220 && 157<y){
							temp = image_btnHover_tex;
						/* Bouton 1 : souris en dehors */
						}else{
							temp = image_btn_tex;
						}
						SDL_QueryTexture(temp, NULL, NULL, &(imgBtnRect.w), &(imgBtnRect.h));
						SDL_RenderCopy(renderer, temp, NULL, &imgBtnRect);
								
                        /* Ajout des autres boutons à d'autres positions (77 px : hauteur de l'image et 90 px de décalage) */
						imgBtnRect.y += 90;
						if(x<620 && 440<x && y<imgBtnRect.y+77 && imgBtnRect.y<y){
							temp = image_btnHover_tex;
						}else{
							temp = image_btn_tex;
						}
						SDL_RenderCopy(renderer, temp, NULL, &imgBtnRect);
								
						imgBtnRect.y += 90;
						if(x<620 && 440<x && y<imgBtnRect.y+77 && imgBtnRect.y<y){
							temp = image_btnHover_tex;
						}else{
							temp = image_btn_tex;
						}
						SDL_RenderCopy(renderer, temp, NULL, &imgBtnRect);

						imgBtnRect.y += 90;
						if(x<620 && 440<x && y<imgBtnRect.y+77 && imgBtnRect.y<y){
							temp = image_btnHover_tex;
						}else{
							temp = image_btn_tex;
						}
						SDL_RenderCopy(renderer, temp, NULL, &imgBtnRect);

						for(i=0;i<4;i++){
							SDL_RenderCopy(renderer, texteMenu_tex[i], NULL, &(txtMenuRect[i]));
						}

						/* On fait le rendu ! */
                        SDL_RenderPresent(renderer);
					break;
					
				} 
			} 
		}
	} else {
		fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
	}

	//Destruction de la fenetre
	SDL_DestroyWindow(pWindow);

	//TTF_CloseFont(policeTitre); /* Doit être avant TTF_Quit() */
	//TTF_CloseFont(policeMenu); /* Doit être avant TTF_Quit() */
	TTF_Quit();
    SDL_Quit();

    return 0;
}


