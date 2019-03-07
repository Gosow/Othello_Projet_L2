#include "SDL_jeu.h"

int lancement_jeu(int modeJeu,t_matrice mat){
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
    int joueur=1;
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
                        afficher_matriceSDL(mat,renderer,&joueur);
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
