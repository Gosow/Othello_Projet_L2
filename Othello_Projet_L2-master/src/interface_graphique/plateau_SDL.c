#include "SDL_jeu.h"

int lancement_jeu(int modeJeu,t_matrice mat){
    srand(time(NULL));
    if(modeJeu==QUITTER) return 0;
    int x,y;
    //Le pointeur vers la fenetre
    SDL_Window* pWindow = NULL;
    //Le pointeur vers la surface incluse dans la fenetre
    SDL_Surface *textePseudo=NULL, *texteJoueur[4], *image=NULL, *imageBG=NULL;
    SDL_Renderer *renderer=NULL;
    SDL_Rect txtDestRect, txtBvnRect, txtJeuRect[4], imgBtnRect, imgBtnHoverRect, imgBGRect;
    
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
    SDL_Rect rectTEST[2];
    SDL_Texture *texteJoueur_tex[4];

    rectTEST[0].x=rectTEST[1].x=800;
    rectTEST[0].y=50;
    rectTEST[1].y=110;
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
    SDL_QueryTexture(texteJoueur_tex[0], NULL, NULL, &(rectTEST[0].w), &(rectTEST[0].h));
    SDL_QueryTexture(texteJoueur_tex[1], NULL, NULL, &(rectTEST[1].w), &(rectTEST[1].h));
    SDL_QueryTexture(texteJoueur_tex[2], NULL, NULL, &(rectTEST[2].w), &(rectTEST[2].h));
    printf("TEST: x:%i, y:%i\n",rectTEST[2].x,rectTEST[2].y);
    //Position ou sera mis le texte dans la fenêtre
    
    //Chargement de l'image de fond
    SDL_Texture *image_BG_tex = tex_img_png("./img/OthelloBG.png",renderer);
    int joueur=rand()%2+1;
    init_texture(renderer);

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
                        if(x<=656 && y<=656){
                            x=x/82;
                            y=y/82;
                            printf("x:%i, y:%i\n",x,y);
                            if(coup_valide(mat,y,x,joueur)){
                                jouer_coup(mat,y,x,joueur);
                                joueur=joueur_suivant(joueur);
                            }
                        }
                    case SDL_WINDOWEVENT:
                        SDL_RenderClear(renderer);
                        SDL_RenderCopy(renderer, texteJoueur_tex[0], NULL, &(rectTEST[0]));
                        SDL_RenderCopy(renderer, texteJoueur_tex[1], NULL, &(rectTEST[1]));

                        if(joueur==1){
                            pion.x=690;
                            pion.y=10;
                            SDL_RenderCopy(renderer, image_noirTour_tex, NULL, &pion);
                            pion.y+=90;
                            SDL_RenderCopy(renderer, image_blanc_tex, NULL, &pion);

                            rectTEST[2].x=930;
                            rectTEST[2].y=rectTEST[0].y;
                            SDL_RenderCopy(renderer, texteJoueur_tex[2], NULL, &(rectTEST[2]));
                            
                        }else{
                            pion.x=690;
                            pion.y=10;
                            SDL_RenderCopy(renderer, image_noir_tex, NULL, &pion);
                            pion.y+=90;
                            SDL_RenderCopy(renderer, image_blancTour_tex, NULL, &pion);
                            rectTEST[2].x=930;
                            rectTEST[2].y=rectTEST[1].y;
                            SDL_RenderCopy(renderer, texteJoueur_tex[2], NULL, &(rectTEST[2]));
                        }
                        afficher_matriceSDL(mat,renderer,&joueur);
                        
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
