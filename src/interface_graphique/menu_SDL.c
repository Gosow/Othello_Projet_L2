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
    SDL_Rect txtDestRect, txtBvnRect, txtMenuRect[4], imgBtnRect, imgBGRect, musicRect;
    
    // Une variable de couleur noire
    SDL_Color couleurNoire = {0, 0, 0, 0};
    //Initialisation du username
    char *pseudo=getenv("USER");
    if(pseudo==NULL) return EXIT_FAILURE;
    strcat(bvn,pseudo);
    
    SDL_Texture *texte_tex = tex_text("src/ttf/PoliceTitre.ttf",100,"Othello",couleurNoire);
    SDL_Texture *user_tex = tex_text("src/ttf/PoliceMenu.ttf",30,bvn,couleurNoire);

    SDL_Rect rect_highscore[6];
    SDL_Texture *hs[6];
    hs[0] = tex_text("src/ttf/PoliceMenu.ttf",30,"Highscore :",couleurNoire);
    hs[1] = tex_text("src/ttf/PoliceMenu.ttf",17,"1. 64 - mario",couleurNoire);
    hs[2] = tex_text("src/ttf/PoliceMenu.ttf",17,"2. 64 - mario",couleurNoire);
    hs[3] = tex_text("src/ttf/PoliceMenu.ttf",17,"3. 64 - mario",couleurNoire);
    hs[4] = tex_text("src/ttf/PoliceMenu.ttf",17,"4. 64 - mario",couleurNoire);
    hs[5] = tex_text("src/ttf/PoliceMenu.ttf",17,"5. 64 - mario",couleurNoire);
    //HIGHSCORE
    config_obj(&rect_highscore[0], hs[0], 900, 10);
    
    for(i=1; i<6; i++){
        config_obj(&rect_highscore[i], hs[i], 940, 17*(i+1));
    }
    
    SDL_Texture *texteMenu_tex[4];
    texteMenu_tex[0] = tex_text("src/ttf/PoliceMenu.ttf",40,"Solo",couleurNoire);
    texteMenu_tex[1] = tex_text("src/ttf/PoliceMenu.ttf",40,"Duo",couleurNoire);
    texteMenu_tex[2] = tex_text("src/ttf/PoliceMenu.ttf",40,"En ligne",couleurNoire);
    texteMenu_tex[3] = tex_text("src/ttf/PoliceMenu.ttf",40,"Quitter",couleurNoire);
    
    //Position ou sera mis le texte dans la fenêtre
    //TITRE
    config_obj(&txtDestRect, texte_tex, 300, 10);
    
    //BIENVENUE USERNAME
    config_obj(&txtBvnRect, user_tex, 10, 10);
    
    //MENU
    for(j=0;j<4;j++){
        config_obj(&txtMenuRect[j], texteMenu_tex[j], j==2 || j==3 ? 480 : 500, 165+90*j);
    }
    
    //Chargement de l'image de fond
    SDL_Texture *image_BG_tex = tex_img_png("src/img/OthelloBG.png");
    //Chargement de l'image bouton
    SDL_Texture *image_btn_tex = tex_img_png("src/img/btn.png");
    //Chargement de l'image bouton (utilisé quand la souris passe sur l'image)
    SDL_Texture *image_btnHover_tex = tex_img_png("src/img/btnHover.png");
    //IMAGE PLAY
    SDL_Texture *image_play_tex = tex_img_png("src/img/play.png");
    //IMAGE PAUSE
    SDL_Texture *image_pause_tex = tex_img_png("src/img/pause.png");

    SDL_Texture *temp;
    SDL_Texture *temp_music = image_play_tex;
    //Musique
    config_obj(&musicRect, temp_music, 1000, 570);
    
        int running = 1;
        SDL_Event e;
        while(running) {
            
            SDL_GetMouseState(&x,&y);
            if(x<700 && 385<x && y<526 && 130<y) goto affichage;
            
            while(SDL_PollEvent(&e)){
                switch(e.type) {
                    case SDL_QUIT: return 0;
                    case SDL_MOUSEBUTTONDOWN:
                        if(pointe(musicRect, x, y)){
                            song = !(song);
                        }
                    default:
                    affichage:
                        clear();
                        
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
                        
                        if(song!=PLAY){
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

                        //Positionnement du premier bouton
                        imgBtnRect.x = 440;
                        imgBtnRect.y = 150;
                        SDL_QueryTexture(image_btnHover_tex, NULL, NULL, &(imgBtnRect.w), &(imgBtnRect.h));
                        for(i=0;i<4;i++){
                            if(pointe(imgBtnRect,x,y)){
                                temp = image_btnHover_tex;
                                if(e.type == SDL_MOUSEBUTTONDOWN){
                                    if(i==2){
                                        choix = choix_type();
                                        if(choix != 2){
                                            Mix_PauseMusic();
                                            lancement_jeu(i,choix);
                                            clear();
                                            break;
                                        }
                                    }else if(i==QUITTER) return 0;
                                    else{
                                        Mix_PauseMusic();
                                        lancement_jeu(i,-1);
                                        clear();
                                        break;
                                    }                                    
                                }
                            }else{
                                temp = image_btn_tex;
                            }
                            SDL_RenderCopy(renderer, temp, NULL, &imgBtnRect);
                            SDL_RenderCopy(renderer, texteMenu_tex[i], NULL, &(txtMenuRect[i]));
                            imgBtnRect.y += 90;
                        }

                        /* On fait le rendu ! */
                        afficher();
                        break;
                }
            }
        }
    return 0;
}