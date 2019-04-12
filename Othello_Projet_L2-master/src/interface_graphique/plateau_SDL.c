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

enum texte {J1, J2, A_VOUS, GAGNEE, PERDU, EGALITE, SCORE, ATTENTE};
enum image {PION = 0, REPLAY= 0, HOME, VOIR};

static SDL_Rect rectText[8], rectImg[7], pion;
static int x ,y ,score_j1 = 0 , score_j2 = 0 ,i ,arret=NON, running = 1;
static t_matrice mat_final, mat;
static SDL_Color couleurNoire = {0, 0, 0, 0};
static SDL_Texture *image_noir_tex,
    *image_blanc_tex,
    *image_noirTour_tex,
    *image_blancTour_tex,
    *image_replay_tex,
    *image_home_tex,
    *image_voir_tex,
    *texteJoueur_tex[8];
static char joueur, joueur_sauv, gagnant, score_aff[20];;
static char *joueur1, *joueur2, joueur_vous;
int type;
/**
 * \fn int lancement_jeu(int modeJeu,t_matrice mat)
 * \brief Lance le jeu en fonction du mode choisie
 * \param modeJeu : le mode jeu choisi selon SOLO, DUO ou ONLINE.
 * \return entier
 */
int lancement_jeu(int modeJeu, int type_online){
    char msg[1024];
    //char joueur1[20] ="J1", joueur2[20]="J2", *joueur_vous;
    //t_matrice mat;
    type = type_online;
    
    
    joueur1 = malloc(sizeof(char)*50);
    joueur2 = malloc(sizeof(char)*50);
    if(modeJeu == ONLINE){
        fprintf(stderr,"\n1\n");
        if(type == SERVEUR){
            joueur1=getenv("USER");
            fprintf(stderr,"\n JOUEUR : %s\n",joueur1);
            if(joueur1 == NULL) strcpy(joueur1,"Serveur");
            fprintf(stderr,"\n2\n");
            recevoir(joueur2,PORT_HOTE);
            envoyer(joueur1,PORT_EXT);

        }
        else if(type == CLIENT){
            joueur2=getenv("USER");
            fprintf(stderr,"\n JOUEUR : %s\n",joueur2);
            if(joueur1 == NULL) strcpy(joueur1,"Client");
            fprintf(stderr,"\n6\n");
            envoyer(joueur2,PORT_HOTE);
            recevoir(joueur1,PORT_EXT);
            fprintf(stderr,"\n7\n");
        }
    }else{
        joueur1=getenv("USER");
        joueur2="Joueur 2";
    }

    
    srand(time(NULL));
    if(modeJeu==QUITTER) return 0;
    
    init_matrice(mat);
    
    
    //Le pointeur vers la fenetre
    //SDL_Window* pWindow = NULL;
    //Le pointeur vers la surface incluse dans la fenetre
   // SDL_Renderer *renderer=NULL;
    
    // Une variable de couleur noire
    
    //Initialisation du username
    //char *pseudo=getenv("USER");
    //if(pseudo==NULL) return EXIT_FAILURE;
    
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
    
    

    rectImg[REPLAY].x=rectText[J1].x=670;
    rectText[J2].x=930;
    
    rectText[J1].y=rectText[J2].y=110;
    
    rectText[GAGNEE].y = rectText[PERDU].y = rectText[EGALITE].y = 150;
    
    rectText[SCORE].x = 800;
    rectText[SCORE].y = 10;
    
    rectImg[REPLAY].y = rectImg[HOME].y = rectImg[VOIR].y = 560;
    rectImg[HOME].x = 980;
    rectImg[VOIR].x = 820;

    rectImg[ATTENTE].x = 670;
    rectImg[ATTENTE].y = 300;

    pion.x=800;
    pion.y=10;

    image_noir_tex = tex_img_png("./img/noir.png",renderer);
    image_blanc_tex = tex_img_png("./img/blanc.png",renderer);
    image_noirTour_tex = tex_img_png("./img/noirTour.png",renderer);
    image_blancTour_tex = tex_img_png("./img/blancTour.png",renderer);
    image_replay_tex = tex_img_png("./img/replay.png",renderer);
    image_home_tex = tex_img_png("./img/home.png",renderer);
    image_voir_tex = tex_img_png("./img/voir.png",renderer);

    SDL_QueryTexture(image_noir_tex, NULL, NULL, &(pion.w), &(pion.h));
    SDL_QueryTexture(image_replay_tex, NULL, NULL, &(rectImg[REPLAY].w), &(rectImg[REPLAY].h));
    SDL_QueryTexture(image_home_tex, NULL, NULL, &(rectImg[HOME].w), &(rectImg[HOME].h));
    SDL_QueryTexture(image_home_tex, NULL, NULL, &(rectImg[VOIR].w), &(rectImg[VOIR].h));


    texteJoueur_tex[J1] = tex_text("./ttf/PoliceMenu.ttf",40,joueur1,couleurNoire,renderer);
    texteJoueur_tex[J2] = tex_text("./ttf/PoliceMenu.ttf",40,joueur2,couleurNoire,renderer);
    texteJoueur_tex[A_VOUS] = tex_text("./ttf/PoliceMenu.ttf",40,"(à vous)",couleurNoire,renderer);
    texteJoueur_tex[GAGNEE] = tex_text("./ttf/PoliceMenu.ttf",40,"GAGNÉ !!",couleurNoire,renderer);
    texteJoueur_tex[PERDU] = tex_text("./ttf/PoliceMenu.ttf",40,"PERDU...",couleurNoire,renderer);
    texteJoueur_tex[EGALITE] = tex_text("./ttf/PoliceMenu.ttf",40,"ÉGALITÉ :)",couleurNoire,renderer);
    texteJoueur_tex[ATTENTE] = tex_text("./ttf/PoliceMenu.ttf",40,"En attente du tour \nde votre adversaire ..",couleurNoire,renderer);
    for(i=0;i<6;i++){
        SDL_QueryTexture(texteJoueur_tex[i], NULL, NULL, &(rectText[i].w), &(rectText[i].h));
    }

    

    //Couleur aléatoire si DUO, sinon noir commence
    if(modeJeu==DUO) joueur = (rand()%2 ? NOIR : BLANC);
    else joueur=NOIR;
    
    //Notre couleur si on joue en ligne
    if(modeJeu == ONLINE){
        joueur_vous = type == SERVEUR ? BLANC : NOIR;
    }
    joueur_sauv=joueur;
    /*objet_SDL attente;
    attente.tex = texteJoueur_tex[ATTENTE];
    attente.rect = rectText[ATTENTE];*/
    init_jeuSDL();
    
    i=0;
    
    fprintf(stderr,"MACOULEUR : %c\n",joueur_vous);


    

        while(running) {
            //SDL_GetMouseState(&x,&y);
            //fprintf(stderr,"x : %d | y : %d\n",x,y);
            SDL_Event e;           
            do {
                switch(e.type) {
                    case SDL_QUIT: running = 0;
                        if(modeJeu == ONLINE) envoyer("-2;-2", PORT_HOTE);
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        SDL_GetMouseState(&x,&y);
                        //fprintf(stderr,"Mouse Button down \n");
                        //REPLAY
                        if(pointe(rectImg[REPLAY],x,y) && modeJeu != ONLINE){
                            init_matrice(mat);
                            arret=NON;
                            joueur=joueur_sauv;
                        }
                       if(pointe(rectImg[HOME],x,y)){
                            running=0;
                            //if(pWindow != NULL) SDL_DestroyWindow(pWindow);
                            //init_matrice(mat);
                            if(modeJeu == ONLINE) envoyer("-2;-2", PORT_HOTE);
                            menu_SDL();
                        }
                        // 82 px taille d'une case
                        if(!arret){
                            if(x<=656 && y<=656){
                                x=x/82;
                                y=y/82;

                                if(coup_valide(mat,y,x,joueur) && modeJeu != ONLINE){
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
                        }else if(pointe(rectImg[VOIR],x,y)){
                                SDL_RenderClear(renderer);

                                afficher_matriceSDL(mat_final,' ',NON);

                                SDL_RenderCopy(renderer, image_voir_tex, NULL, &(rectImg[VOIR]));

                                SDL_RenderPresent(renderer);
                                sleep(4);
                        }
                        if(modeJeu == ONLINE){
                            //jouer_coup(mat,y,x,joueur_vous);
                            memset(msg, '\0', sizeof(msg));
                            SDL_GetMouseState(&x,&y);
                            x /= 82;
                            y /= 82;
                            sprintf(msg,"%d;%d",x,y);
                            //SDL_GetMouseState(&x,&y);
                            fprintf(stderr,"\n A ENVOYER : '%s' x: %d y: %d\n",msg,x,y);
                            fprintf(stderr,"%d %d %d %d %d %d\n", type == CLIENT, peut_jouer(mat,joueur), coup_valide(mat,y,x,joueur), e.type == SDL_MOUSEBUTTONDOWN, joueur_vous==joueur);
                            if(type == CLIENT && joueur_vous==joueur){
                                if(peut_jouer(mat,joueur) && coup_valide(mat,y,x,joueur)){
                                    jouer_coup(mat,y,x,joueur_vous);
                                    fprintf(stderr,"\n ENVOIE : '%s' x: %d y: %d\n",msg,x,y);
                                    envoyer(msg, PORT_HOTE);
                                    memset(msg, '\0', sizeof(msg));
                                    type = !type;
                                    joueur = joueur_suivant(joueur);
                                    //recevoir(msg, PORT_EXT);
                                }else if(!peut_jouer(mat,joueur)){
                                    envoyer("-1;-1", PORT_HOTE);
                                }
                            }
                        }
                        

                    default:
                        //fprintf(stderr,"JE SUIS DANS LA BOUCLE");
                        if(modeJeu == ONLINE && type ==SERVEUR) afficher_matriceSDL(mat,' ',OUI);
                        else affichage_partie(mat,modeJeu);
                        
                        if(modeJeu == ONLINE){
                            /*jouer_coup(mat,y,x,joueur_vous);
                            memset(msg, '\0', sizeof(msg));
                            SDL_GetMouseState(&x,&y);
                            x /= 82;
                            y /= 82;
                            sprintf(msg,"%d;%d",x,y);
                            SDL_GetMouseState(&x,&y);
                            fprintf(stderr,"\n A ENVOYER : '%s' x: %d y: %d\n",msg,x,y);
                            */
                            if(type == SERVEUR){
                                memset(msg, '\0', sizeof(msg));
                                afficher_matriceSDL(mat,' ',OUI);
                                recevoir(msg, PORT_HOTE );
                                sscanf(msg,"%d;%d",&y,&x);
                                if(x > 0 && y > 0){
                                    jouer_coup(mat,x,y,joueur);
                                    afficher_cibleSDL(mat,x,y);
                                }else if(x == -1){
                                    joueur = joueur_suivant(joueur);
                                    //alerter(que le joeur a quitté la partie)
                                }else if(x == -2){
                                    menu_SDL();
                                }
                                //envoyer(msg, PORT_EXT);
                                type = !type;
                                joueur = joueur_suivant(joueur);
                            }
                        }
                        
                        break;
                    }
                }
            while(SDL_PollEvent(&e));
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

APPEL RECURSSIF SI ON RECOMMENCE
    */

int affichage_partie(t_matrice mat,int modeJeu){
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
        SDL_RenderCopy(renderer, image_voir_tex, NULL, &(rectImg[VOIR]));
        afficher_gagnant(mat);
    }
    else afficher_matriceSDL(mat, joueur, NON);

    //printf("%c\n",afficher_gagnant(mat,renderer));
    pion.x=680;
    pion.y=10;
    rectText[A_VOUS].y=150;
    if(!partie_termineeSDL(mat)){
        SDL_RenderCopy(renderer, joueur == NOIR ? image_noirTour_tex : image_noir_tex, NULL, &pion);
        pion.x+=270;
        SDL_RenderCopy(renderer, joueur == BLANC ? image_blancTour_tex : image_blanc_tex, NULL, &pion);
        rectText[A_VOUS].x=rectText[joueur == NOIR ? J1 : J2].x;
        if(!(modeJeu == ONLINE) || joueur == joueur_vous) SDL_RenderCopy(renderer, texteJoueur_tex[A_VOUS], NULL, &(rectText[A_VOUS]));
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
    if(modeJeu != ONLINE) SDL_RenderCopy(renderer, image_replay_tex, NULL, &(rectImg[REPLAY]));
    SDL_RenderCopy(renderer, image_home_tex, NULL, &(rectImg[HOME]));

    SDL_RenderPresent(renderer);
}