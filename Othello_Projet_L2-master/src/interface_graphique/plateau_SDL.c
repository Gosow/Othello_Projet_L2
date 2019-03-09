#include "SDL_jeu.h"
#define OUI 1
#define NON 0

int lancement_jeu(int modeJeu,t_matrice mat){
    srand(time(NULL));
    if(modeJeu==QUITTER) return 0;
    int x,y,score_j1=0,score_j2=0,i;
    char gagnant;
    //Le pointeur vers la fenetre
    SDL_Window* pWindow = NULL;
    //Le pointeur vers la surface incluse dans la fenetre
    SDL_Surface *textePseudo=NULL, *texteJoueur[4], *image=NULL, *imageBG=NULL;
    SDL_Renderer *renderer=NULL;
    SDL_Rect txtDestRect, txtBvnRect, txtJeuRect[4], imgBtnRect, imgBtnHoverRect, imgBGRect;
    char* score_aff[20];
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
    SDL_Rect rectTEST[7];
    SDL_Texture *texteJoueur_tex[7];

    rectTEST[0].x=670;
    rectTEST[0].y=rectTEST[1].y=110;
    rectTEST[1].x=930;
    rectTEST[3].y = rectTEST[4].y = rectTEST[5].y = 150;
    rectTEST[6].x=800;
    rectTEST[6].y=10;
    SDL_Rect pion;
    pion.x=800;
    pion.y=10;

    SDL_Texture *image_noir_tex = tex_img_png("./img/noir.png",renderer);
    SDL_Texture *image_blanc_tex = tex_img_png("./img/blanc.png",renderer);
    SDL_Texture *image_noirTour_tex = tex_img_png("./img/noirTour.png",renderer);
    SDL_Texture *image_blancTour_tex = tex_img_png("./img/blancTour.png",renderer);
    SDL_QueryTexture(image_noir_tex, NULL, NULL, &(pion.w), &(pion.h));

    texteJoueur_tex[0] = tex_text("./ttf/PoliceMenu.ttf",40,"Joueur 1",couleurNoire,renderer);
    texteJoueur_tex[1] = tex_text("./ttf/PoliceMenu.ttf",40,"Joueur 2",couleurNoire,renderer);
    texteJoueur_tex[2] = tex_text("./ttf/PoliceMenu.ttf",40,"(à vous)",couleurNoire,renderer);
    texteJoueur_tex[3] = tex_text("./ttf/PoliceMenu.ttf",40,"GAGNÉ !!",couleurNoire,renderer);
    texteJoueur_tex[4] = tex_text("./ttf/PoliceMenu.ttf",40,"PERDU...",couleurNoire,renderer);
    texteJoueur_tex[5] = tex_text("./ttf/PoliceMenu.ttf",40,"ÉGALITÉ :)",couleurNoire,renderer);
    for(i=0;i<6;i++){
        SDL_QueryTexture(texteJoueur_tex[i], NULL, NULL, &(rectTEST[i].w), &(rectTEST[i].h));
    }
    //printf("TEST: x:%i, y:%i\n",rectTEST[2].x,rectTEST[2].y);
    //Position ou sera mis le texte dans la fenêtre
    
    //Chargement de l'image de fond
    SDL_Texture *image_BG_tex = tex_img_png("./img/OthelloBG.png",renderer);
    int joueur=rand()%2+1;
    init_texture(renderer);
    int arret=NON;
    if( pWindow )
    {
        int running = 1;
        while(running) {
            SDL_Event e;           
            while(SDL_PollEvent(&e)) {
                switch(e.type) {
                    case SDL_QUIT: running = 0;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        SDL_GetMouseState(&x,&y);
                        // 82 px taille d'une case
                        if(!arret){
                            if(x<=656 && y<=656){
                                x=x/82;
                                y=y/82;
                                //printf("x:%d | y:%d\n",x,y);
                                /*if(!peut_jouer(mat,joueur)&&peut_jouer(mat,joueur%2+1)){
                                    joueur=joueur_suivant(joueur);
                                }*/
                                //printf("x:%i, y:%i\n",x,y);
                                if(coup_valide(mat,y,x,joueur) && arret==NON){
                                    jouer_coup(mat,y,x,joueur);
                                    joueur=joueur_suivant(joueur);
                                    if(!peut_jouer(mat,joueur)&&peut_jouer(mat,joueur%2+1)){
                                        joueur=joueur_suivant(joueur);
                                    }
                                }
                                
                            }
                        }
                    case SDL_WINDOWEVENT:
                        SDL_RenderClear(renderer);
                        /* Le fond de la fenêtre sera vert */
                        SDL_SetRenderDrawColor(renderer, 24, 124, 58, 255);

                        SDL_RenderCopy(renderer, texteJoueur_tex[0], NULL, &(rectTEST[0]));
                        SDL_RenderCopy(renderer, texteJoueur_tex[1], NULL, &(rectTEST[1]));
                        
                        calculer_score(mat,&score_j1,&score_j2);
                        sprintf(score_aff, "%d - %d", score_j1,score_j2);
                        
                        texteJoueur_tex[6] = tex_text("./ttf/PoliceMenu.ttf",55,score_aff,couleurNoire,renderer);

                        SDL_QueryTexture(texteJoueur_tex[6], NULL, NULL, &(rectTEST[6].w), &(rectTEST[6].h));
                        
                        /* Le fond de la fenêtre sera vert */
                        SDL_SetRenderDrawColor(renderer, 24, 124, 58, 255);

                        /* On fait le rendu ! */
                        if (partie_termineeSDL(mat)){
                            arret=OUI;
                            afficher_gagnant(mat,renderer);
                        }
                        else afficher_matriceSDL(mat,renderer,&joueur);

                        printf("%c\n",afficher_gagnant(mat,renderer));
                        pion.x=680;
                        pion.y=10;
                        rectTEST[2].y=150;
                        if(!partie_termineeSDL(mat)){
                            if(joueur==1){
                                SDL_RenderCopy(renderer, image_noirTour_tex, NULL, &pion);
                                pion.x+=270;
                                SDL_RenderCopy(renderer, image_blanc_tex, NULL, &pion);
                                rectTEST[2].x=rectTEST[0].x;

                            }else{
                                SDL_RenderCopy(renderer, image_noir_tex, NULL, &pion);
                                pion.x+=270;
                                SDL_RenderCopy(renderer, image_blancTour_tex, NULL, &pion);
                                rectTEST[2].x=rectTEST[1].x;
                            }
                            SDL_RenderCopy(renderer, texteJoueur_tex[2], NULL, &(rectTEST[2]));
                        }else{
                            gagnant=afficher_gagnant(mat,renderer);
                            if(gagnant==NOIR){
                                SDL_RenderCopy(renderer, image_noirTour_tex, NULL, &pion);
                                pion.x+=270;
                                SDL_RenderCopy(renderer, image_blanc_tex, NULL, &pion);
                                rectTEST[3].x=rectTEST[0].x;
                                rectTEST[4].x=rectTEST[1].x;
                                SDL_RenderCopy(renderer, texteJoueur_tex[3], NULL, &(rectTEST[3]));
                                SDL_RenderCopy(renderer, texteJoueur_tex[4], NULL, &(rectTEST[4]));

                            }else if(gagnant==BLANC){
                                SDL_RenderCopy(renderer, image_noir_tex, NULL, &pion);
                                pion.x+=270;
                                SDL_RenderCopy(renderer, image_blancTour_tex, NULL, &pion);
                                rectTEST[3].x=rectTEST[1].x;
                                rectTEST[4].x=rectTEST[0].x;
                                SDL_RenderCopy(renderer, texteJoueur_tex[3], NULL, &(rectTEST[3]));
                                SDL_RenderCopy(renderer, texteJoueur_tex[4], NULL, &(rectTEST[4]));
                            }else{
                                SDL_RenderCopy(renderer, image_noirTour_tex, NULL, &pion);
                                pion.x+=270;
                                SDL_RenderCopy(renderer, image_blancTour_tex, NULL, &pion);
                                rectTEST[5].x=rectTEST[1].x;
                                SDL_RenderCopy(renderer, texteJoueur_tex[3], NULL, &(rectTEST[5]));
                                rectTEST[5].x=rectTEST[0].x;
                                SDL_RenderCopy(renderer, texteJoueur_tex[4], NULL, &(rectTEST[5]));
                            }
                        }
                        SDL_RenderCopy(renderer, texteJoueur_tex[6], NULL, &(rectTEST[6]));
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
