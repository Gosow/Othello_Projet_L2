/*
remplacer arret par tpartie terminee
ajouter un enum pour que les tableaux soient plus clair
creer structure

*/




/**
 * \file plateau_SDL.c
 * \brief Fichier qui contient la fonction qui regroupe toutes les fonctions utilisé pour l'interface graphique pour pouvoir jouer.
 * \author Mario Hotaj
 * \date 10 mars 2019 (dernière modif.)
 */

#include "SDL_jeu.h"
#define OUI 1
#define NON 0

#define LOCAL -1
#define CLIENT 0
#define SERVEUR 1

enum texte {J1, J2, A_VOUS, GAGNEE, PERDU, EGALITE, SCORE};
enum image {PION = 0, REPLAY= 0, HOME, VOIR};

/**
 * \fn int lancement_jeu(int modeJeu,t_matrice mat)
 * \brief Lance le jeu en fonction du mode choisie
 * \param modeJeu : le mode jeu choisi selon SOLO, DUO ou ONLINE.
 * \return entier
 */
int lancement_jeu(int modeJeu, int type){
    char* msg[512];
    srand(time(NULL));
    if(modeJeu==QUITTER) return 0;
    t_matrice mat, mat_final;
    init_matrice(mat);
    int x,y,score_j1=0,score_j2=0,i;
    char gagnant;
    //Le pointeur vers la fenetre
    //SDL_Window* pWindow = NULL;
    //Le pointeur vers la surface incluse dans la fenetre
   // SDL_Renderer *renderer=NULL;
    char score_aff[20];
    // Une variable de couleur noire
    SDL_Color couleurNoire = {0, 0, 0, 0};
    //Initialisation du username
    char *pseudo=getenv("USER");
    if(pseudo==NULL) return EXIT_FAILURE;
    
    /* Création de la fenêtre */
    /*pWindow = SDL_CreateWindow("Othello : DELUXE EDITION",SDL_WINDOWPOS_UNDEFINED,
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
    }*/
    SDL_Rect rectText[7];
    SDL_Rect rectImg[7];
    SDL_Texture *texteJoueur_tex[7];
    

    rectImg[0].x=rectText[J1].x=670;
    rectText[J2].x=930;
    
    rectText[J1].y=rectText[J2].y=110;
    
    rectText[GAGNEE].y = rectText[PERDU].y = rectText[EGALITE].y = 150;
    
    rectText[SCORE].x=800;
    rectText[SCORE].y=10;
    
    rectImg[0].y = rectImg[1].y = rectImg[2].y = 560;
    rectImg[1].x=980;
    rectImg[2].x = 820;
    SDL_Rect pion;
    pion.x=800;
    pion.y=10;

    SDL_Texture * image_noir_tex = tex_img_png("./img/noir.png",renderer);
    SDL_Texture *image_blanc_tex = tex_img_png("./img/blanc.png",renderer);
    SDL_Texture *image_noirTour_tex = tex_img_png("./img/noirTour.png",renderer);
    SDL_Texture *image_blancTour_tex = tex_img_png("./img/blancTour.png",renderer);
    SDL_Texture *image_replay_tex = tex_img_png("./img/replay.png",renderer);
    SDL_Texture *image_home_tex = tex_img_png("./img/home.png",renderer);
    SDL_Texture *image_voir_tex = tex_img_png("./img/voir.png",renderer);
    SDL_QueryTexture(image_noir_tex, NULL, NULL, &(pion.w), &(pion.h));
    SDL_QueryTexture(image_replay_tex, NULL, NULL, &(rectImg[0].w), &(rectImg[0].h));
    SDL_QueryTexture(image_home_tex, NULL, NULL, &(rectImg[1].w), &(rectImg[1].h));
    SDL_QueryTexture(image_home_tex, NULL, NULL, &(rectImg[2].w), &(rectImg[2].h));


    texteJoueur_tex[J1] = tex_text("./ttf/PoliceMenu.ttf",40,pseudo,couleurNoire,renderer);
    texteJoueur_tex[J2] = tex_text("./ttf/PoliceMenu.ttf",40,"Joueur 2",couleurNoire,renderer);
    texteJoueur_tex[A_VOUS] = tex_text("./ttf/PoliceMenu.ttf",40,"(à vous)",couleurNoire,renderer);
    texteJoueur_tex[GAGNEE] = tex_text("./ttf/PoliceMenu.ttf",40,"GAGNÉ !!",couleurNoire,renderer);
    texteJoueur_tex[PERDU] = tex_text("./ttf/PoliceMenu.ttf",40,"PERDU...",couleurNoire,renderer);
    texteJoueur_tex[EGALITE] = tex_text("./ttf/PoliceMenu.ttf",40,"ÉGALITÉ :)",couleurNoire,renderer);
    for(i=0;i<6;i++){
        SDL_QueryTexture(texteJoueur_tex[i], NULL, NULL, &(rectText[i].w), &(rectText[i].h));
    }
    char joueur;

    if(rand()%2 || modeJeu==SOLO) joueur=NOIR;
    else joueur=BLANC;

    int joueur_sauv=joueur;
    init_jeuSDL();
    int arret=NON;

    if(modeJeu == ONLINE){
        if(type == SERVEUR){
            init_serv();
            recv();
        }
        else if(type == CLIENT){
            init_client();
        }
    }




        int running = 1;
        while(running) {
            //SDL_GetMouseState(&x,&y);
            //fprintf(stderr,"x : %d | y : %d\n",x,y);
            SDL_Event e;           
            do {
                switch(e.type) {
                    case SDL_QUIT: running = 0;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        SDL_GetMouseState(&x,&y);
                        //fprintf(stderr,"Mouse Button down \n");
                        //REPLAY
                        if(pointe(rectImg[0],x,y)){
                            init_matrice(mat);
                            arret=NON;
                            joueur=joueur_sauv;
                        }
                       if(pointe(rectImg[1],x,y)){
                            running=0;
                            //if(pWindow != NULL) SDL_DestroyWindow(pWindow);
                            //init_matrice(mat);
                            menu_SDL();
                        }
                        // 82 px taille d'une case
                        if(!arret){
                            if(x<=656 && y<=656){
                                x=x/82;
                                y=y/82;
                                if(coup_valide(mat,y,x,joueur)){
                                    jouer_coup(mat,y,x,joueur);
                                    if(peut_jouer(mat,joueur_suivant(joueur))) joueur=joueur_suivant(joueur);

                                    while(modeJeu == SOLO && joueur == BLANC && peut_jouer(mat,BLANC)){
                                        tour_ordi(mat,&x,&y);
                                        afficher_cibleSDL(mat, x, y);
                                        jouer_coup(mat,x,y,BLANC);
                                        if(peut_jouer(mat, NOIR)) joueur=joueur_suivant(joueur);
                                    }
                                }
                                
                            }
                        }else if(pointe(rectImg[2],x,y)){
                                SDL_RenderClear(renderer);

                                afficher_matriceSDL(mat_final,NULL);

                                SDL_RenderCopy(renderer, image_voir_tex, NULL, &(rectImg[2]));

                                SDL_RenderPresent(renderer);
                                sleep(4);
                            
                        }
                        

                    default:
                        SDL_RenderClear(renderer);
                        /* Le fond de la fenêtre sera vert */
                        
                        
                        SDL_SetRenderDrawColor(renderer, 24, 124, 58, 255);

                        SDL_RenderCopy(renderer, texteJoueur_tex[J1], NULL, &(rectText[J1]));
                        SDL_RenderCopy(renderer, texteJoueur_tex[J2], NULL, &(rectText[J2]));
                        
                        calculer_score(mat,&score_j1,&score_j2);
                        //afficher_matrice(mat);
                        sprintf(score_aff, "%d - %d", score_j1,score_j2);
                        
                        texteJoueur_tex[SCORE] = tex_text("./ttf/PoliceMenu.ttf",55,score_aff,couleurNoire,renderer);

                        SDL_QueryTexture(texteJoueur_tex[SCORE], NULL, NULL, &(rectText[SCORE].w), &(rectText[SCORE].h));
                        
                        /* Le fond de la fenêtre sera vert */
                        SDL_SetRenderDrawColor(renderer, 24, 124, 58, 255);
                        
                        /* On fait le rendu ! */
                        if (partie_termineeSDL(mat)){
                            arret=OUI;
                            copie_mat(mat,mat_final);
                            //VOIR
                            SDL_RenderCopy(renderer, image_voir_tex, NULL, &(rectImg[2]));
                            afficher_gagnant(mat);
                        }
                        else afficher_matriceSDL(mat, joueur);

                        //printf("%c\n",afficher_gagnant(mat,renderer));
                        pion.x=680;
                        pion.y=10;
                        rectText[A_VOUS].y=150;
                        if(!partie_termineeSDL(mat)){
                            SDL_RenderCopy(renderer, joueur == NOIR ? image_noirTour_tex : image_noir_tex, NULL, &pion);
                            pion.x+=270;
                            SDL_RenderCopy(renderer, joueur == BLANC ? image_blancTour_tex : image_blanc_tex, NULL, &pion);
                            rectText[A_VOUS].x=rectText[joueur == NOIR ? J1 : J2].x;
                            SDL_RenderCopy(renderer, texteJoueur_tex[A_VOUS], NULL, &(rectText[A_VOUS]));
                        }else{
                            //A FACTORISER
                            gagnant=afficher_gagnant(mat);
                            if(gagnant==NOIR){
                                SDL_RenderCopy(renderer, image_noirTour_tex, NULL, &pion);
                                pion.x+=270;
                                SDL_RenderCopy(renderer, image_blanc_tex, NULL, &pion);
                                rectText[GAGNEE].x=rectText[J1].x;
                                rectText[PERDU].x=rectText[J2].x;
                                SDL_RenderCopy(renderer, texteJoueur_tex[GAGNEE], NULL, &(rectText[GAGNEE]));
                                SDL_RenderCopy(renderer, texteJoueur_tex[PERDU], NULL, &(rectText[PERDU]));

                            }else if(gagnant==BLANC){
                                SDL_RenderCopy(renderer, image_noir_tex, NULL, &pion);
                                pion.x+=270;
                                SDL_RenderCopy(renderer, image_blancTour_tex, NULL, &pion);
                                rectText[GAGNEE].x=rectText[J2].x;
                                rectText[PERDU].x=rectText[J1].x;
                                SDL_RenderCopy(renderer, texteJoueur_tex[GAGNEE], NULL, &(rectText[GAGNEE]));
                                SDL_RenderCopy(renderer, texteJoueur_tex[PERDU], NULL, &(rectText[PERDU]));
                            }else{
                                SDL_RenderCopy(renderer, image_noirTour_tex, NULL, &pion);
                                pion.x+=270;
                                SDL_RenderCopy(renderer, image_blancTour_tex, NULL, &pion);
                                rectText[EGALITE].x=rectText[J1].x;
                                SDL_RenderCopy(renderer, texteJoueur_tex[EGALITE], NULL, &(rectText[EGALITE]));
                                rectText[EGALITE].x=rectText[J2].x;
                                SDL_RenderCopy(renderer, texteJoueur_tex[EGALITE], NULL, &(rectText[EGALITE]));
                            }
                        }

                        SDL_RenderCopy(renderer, texteJoueur_tex[SCORE], NULL, &(rectText[SCORE]));
                        SDL_RenderCopy(renderer, image_replay_tex, NULL, &(rectImg[0]));
                        SDL_RenderCopy(renderer, image_home_tex, NULL, &(rectImg[1]));

                        SDL_RenderPresent(renderer);
                        break;
                }
            }while(SDL_PollEvent(&e));
        }

    
    //Destruction de la fenetre
    //if(pWindow != NULL) SDL_DestroyWindow(pWindow);
    return 0;
}
/*SI JOUEUR NOIR et JE SUIS SERVEUR
    ATTENTE QUE LE CLIENT JOUE
        PRENDRE LES COORD
        AFFICHER CIBLE CLIENT
    
    VOIR SI JE PEUX JOUER UN COUP
        SI JE LE PEUX, JOUER LE COUP ET ENVOYER LES COORDONNE
        SINON ENVOYER DES COORDONNE NEGATIVE

SINON JOEUR BLANC ET CLIENT
    AFFICHER CIBLE COUP
    AFFICHER MATRICE
    JOUER LE COUP SI JE PEUX SINON RENVOYER COORD NEGATIVE
    ATTENDRE QUE LE SERVEUR JOUE



    */