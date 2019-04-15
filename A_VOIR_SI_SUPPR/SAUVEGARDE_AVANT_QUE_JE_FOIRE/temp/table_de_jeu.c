//
//  table_de_jeu.c
//  
//
//  Created by Mario Hotaj on 05/03/2019.
//

#include "table_de_jeu.h"

int lancement_jeu(int modeJeu){
    if(modeJeu==QUITTER) return 0;
    int x,y;
    //Le pointeur vers la fenetre
    SDL_Window* pWindow = NULL;
    //Le pointeur vers la surface incluse dans la fenetre
    SDL_Surface *textePseudo=NULL, *texteMenu[2], *image=NULL, *imageBG=NULL;
    SDL_Renderer *renderer=NULL;
    SDL_Rect txtDestRect, txtBvnRect, txtMenuRect[4], imgBtnRect, imgBtnHoverRect, imgBGRect;
    
    // Le pointeur vers notre policeTitre
    TTF_Font *policeTitre = NULL, *policeMenu = NULL;
    // Une variable de couleur noire
    SDL_Color couleurNoire = {0, 0, 0};
    //Initialisation du username
    char *pseudo=getenv("USER");
    if(pseudo==NULL) return EXIT_FAILURE;
    
    /* Création de la fenêtre */
    pWindow = SDL_CreateWindow("Othello : DELUXE EDITION",SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               1080,
                               655,
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
    
    //Position ou sera mis le texte dans la fenêtre
    
    //Chargement de l'image de fond
    SDL_Texture *image_BG_tex = tex_img_png("./img/OthelloBG.png",renderer);
    //Chargement de l'image bouton
    SDL_Texture *image_caseNorm_tex = tex_img_png("./img/caseNorm.png",renderer);
    //Chargement de l'image bouton (utilisé quand la souris passe sur l'image)
    SDL_Texture *image_casePoss_tex = tex_img_png("./img/casePoss.png",renderer);
    
    //PION NOIR
    SDL_Texture *image_noir_tex = tex_img_png("./img/noir.png",renderer);
    //PION BLANC
    SDL_Texture *image_blanc_tex = tex_img_png("./img/blanc.png",renderer);
    
    SDL_Texture *temp;
    int i=0,j=0;
    int numBtn = 0;
    
    if( pWindow )
    {
        int running = 1;
        while(running) {
            SDL_Event e;
            while(SDL_PollEvent(&e)) {
                switch(e.type) {
                    case SDL_QUIT: running = 0;
                        break;
                    case SDL_WINDOWEVENT:
                        /* Le fond de la fenêtre sera vert */
                        
                        SDL_RenderClear(renderer);
                        SDL_SetRenderDrawColor(renderer, 24, 124, 58, 255);
                        
                        //Positionnement du premier bouton
                        imgBtnRect.x = 0;
                        imgBtnRect.y = 0;
                        SDL_QueryTexture(image_caseNorm_tex, NULL, NULL, &(imgBtnRect.w), &(imgBtnRect.h));
                        
                        for(i=0;i<8;i++){
                            imgBtnRect.x = i*82;
                            imgBtnRect.y = 0;
                            for(j=0;j<8;j++){
                                if(1){
                                    temp = image_caseNorm_tex;
                                }else{
                                    temp = image_casePoss_tex;
                                }
                                SDL_RenderCopy(renderer, temp, NULL, &imgBtnRect);
                                SDL_RenderCopy(renderer, image_noir_tex, NULL, &imgBtnRect);
                                imgBtnRect.y += 82;
                            }
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
    if(pWindow != NULL) SDL_DestroyWindow(pWindow);
    return 0;
}
