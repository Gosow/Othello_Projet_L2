/**
 * \file menu_SDL.c
 * \brief Affichage du menu sur une fenêtre grâce à la SDL 2
 * \author Mario Hotaj
 * \date 2 mars 2019
 */
#include "SDL_jeu.h"
#define PLAY 1
#define PAUSE 0
/**
 * \fn int menu_SDL(void)
 * \brief Fonction qui va nous afficher le menu grâce à la SDL et afficher les différent mode de jeu, la lecture de la musique et quitter le jeu.
 * \param rien
 * \return entier
 */
int menu_SDL(void){
    int x,y, i=0, j=0,choix;
    char bvn[80] ="Bienvenue ";
    //Le pointeur vers la fenetre
    SDL_Window* pWindow = NULL;
    //Le pointeur vers la surface incluse dans la fenetre
    SDL_Renderer *renderer=NULL;
    SDL_Rect txtDestRect, txtBvnRect, txtMenuRect[4], imgBtnRect, imgBGRect, musicRect;
    
    // Une variable de couleur noire
    SDL_Color couleurNoire = {0, 0, 0, 0};
    //Initialisation du username
    char *pseudo=getenv("USER");
    if(pseudo==NULL) return EXIT_FAILURE;
    strcat(bvn,pseudo);
    
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
    SDL_Texture *texte_tex = tex_text("./ttf/PoliceTitre.ttf",100,"Othello",couleurNoire,renderer);
    SDL_Texture *user_tex = tex_text("./ttf/PoliceMenu.ttf",30,bvn,couleurNoire,renderer);
    


    SDL_Rect rect_highscore[6];
    SDL_Texture *hs[6];
    hs[0] = tex_text("./ttf/PoliceMenu.ttf",30,"Highscore :",couleurNoire,renderer);
    hs[1] = tex_text("./ttf/PoliceMenu.ttf",17,"1. 64 - mario",couleurNoire,renderer);
    hs[2] = tex_text("./ttf/PoliceMenu.ttf",17,"2. 64 - mario",couleurNoire,renderer);
    hs[3] = tex_text("./ttf/PoliceMenu.ttf",17,"3. 64 - mario",couleurNoire,renderer);
    hs[4] = tex_text("./ttf/PoliceMenu.ttf",17,"4. 64 - mario",couleurNoire,renderer);
    hs[5] = tex_text("./ttf/PoliceMenu.ttf",17,"5. 64 - mario",couleurNoire,renderer);
    //HIGHSCORE
    config_obj(&rect_highscore[0], hs[0], 900, 10);
    
    for(i=1; i<6; i++){
        config_obj(&rect_highscore[i], hs[i], 940, 17*(i+1));
    }

    
    SDL_Texture *texteMenu_tex[4];
    texteMenu_tex[0] = tex_text("./ttf/PoliceMenu.ttf",40,"Solo",couleurNoire,renderer);
    texteMenu_tex[1] = tex_text("./ttf/PoliceMenu.ttf",40,"Duo",couleurNoire,renderer);
    texteMenu_tex[2] = tex_text("./ttf/PoliceMenu.ttf",40,"En ligne",couleurNoire,renderer);
    texteMenu_tex[3] = tex_text("./ttf/PoliceMenu.ttf",40,"Quitter",couleurNoire,renderer);
    
    //Position ou sera mis le texte dans la fenêtre
    //TITRE
    config_obj(&txtDestRect, texte_tex, 300, 10);
    
    //BIENVENUE USERNAME
    config_obj(&txtBvnRect, user_tex, 10, 10);
    
    //MENU
    for(j=0;j<4;j++){
        config_obj(&txtMenuRect[j], texteMenu_tex[j], j==2 || j==3 ? 480 : 500, 165+90*j);
        /*
        if(j==2 || j==3){
            txtMenuRect[j].x = 480;
        }else{
            txtMenuRect[j].x = 500;
        }
        txtMenuRect[j].y = 165+90*j;
        SDL_QueryTexture(texteMenu_tex[j], NULL, NULL, &(txtMenuRect[j].w), &(txtMenuRect[j].h));
        */
    }
    
    
    //Chargement de l'image de fond
    SDL_Texture *image_BG_tex = tex_img_png("./img/OthelloBG.png",renderer);
    //Chargement de l'image bouton
    SDL_Texture *image_btn_tex = tex_img_png("./img/btn.png",renderer);
    //Chargement de l'image bouton (utilisé quand la souris passe sur l'image)
    SDL_Texture *image_btnHover_tex = tex_img_png("./img/btnHover.png",renderer);
    //IMAGE PLAY
    SDL_Texture *image_play_tex = tex_img_png("./img/play.png",renderer);
    //IMAGE PAUSE
    SDL_Texture *image_pause_tex = tex_img_png("./img/pause.png",renderer);

    SDL_Texture *temp;
    SDL_Texture *temp_music = image_play_tex;
    //Musique
    config_obj(&musicRect, temp_music, 1000, 570);

    if( pWindow )
    {
        int running = 1;
        while(running) {
            SDL_Event e;
            SDL_GetMouseState(&x,&y);
            if(x<700 && 385<x && y<526 && 130<y) goto affichage;
            //printf("x:%i y:%i\n",x,y);
            
            while(SDL_PollEvent(&e)) {
                switch(e.type) {
                    case SDL_QUIT: running = 0;break;
                    case SDL_MOUSEBUTTONDOWN:
                        if(pointe(musicRect, x, y)){
                            song = !(song);
                        }
                    case SDL_WINDOWEVENT:
                    affichage:
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
                        SDL_RenderCopy(renderer, user_tex, NULL, &txtBvnRect);
                        
                        SDL_RenderDrawLine(renderer,0,130,1080,130);
                        
                        //Positionnement du premier bouton
                        imgBtnRect.x = 440;
                        imgBtnRect.y = 150;
                        SDL_QueryTexture(image_btnHover_tex, NULL, NULL, &(imgBtnRect.w), &(imgBtnRect.h));
                        for(i=0;i<4;i++){
                            if(pointe(imgBtnRect,x,y)){
                                temp = image_btnHover_tex;
                                if(e.type == SDL_MOUSEBUTTONDOWN){
                                    if(i==2){
                                        choix = choix_type(pWindow);
                                        fprintf(stderr,"CHOIX : %d",choix);
                                        if(choix != 2){
                                            SDL_DestroyWindow(pWindow);
                                            Mix_PauseMusic();
                                            lancement_jeu(i,choix);
                                            return 0;
                                        }
                                    }else{
                                        SDL_DestroyWindow(pWindow);
                                        Mix_PauseMusic();
                                        lancement_jeu(i,-1);
                                        return 0;
                                    }                                    
                                }
                            }else{
                                temp = image_btn_tex;
                            }
                            SDL_RenderCopy(renderer, temp, NULL, &imgBtnRect);
                            SDL_RenderCopy(renderer, texteMenu_tex[i], NULL, &(txtMenuRect[i]));
                            imgBtnRect.y += 90;
                        }

                        if(song==PLAY){
                            temp_music = image_pause_tex;
                            Mix_ResumeMusic();
                        }else{
                            temp_music = image_play_tex;
                            Mix_PauseMusic();
                        }
                        SDL_RenderCopy(renderer, temp_music, NULL, &musicRect);

                        for(i=0;i<6;i++){
                            SDL_RenderCopy(renderer, hs[i], NULL, &rect_highscore[i]);
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



