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


static int x ,y ,score_j1 = 0 , score_j2 = 0 ,i ,arret=NON;
static t_matrice mat_final, mat;
static char joueur, joueur_sauv, gagnant, score_aff[20];;
static char *joueur1, *joueur2, joueur_vous;
//int type;
static obj text_tab[8];
static obj img_noir, img_noirTour, img_blanc, img_blancTour, img_replay, img_home, img_voir;

SDL_Texture *image_BG_tex;
SDL_Rect bg_rect={0,0,0,0};

void init_obj(void){
    img_noir = obj_img("src/img/noir.png",670,10);
    img_noirTour = obj_img("src/img/noirTour.png",670,10);
    img_blanc = obj_img("src/img/blanc.png",670+270,10);
    img_blancTour = obj_img("src/img/blancTour.png",670+270,10);
    img_replay = obj_img("src/img/replay.png",670,560);
    img_home = obj_img("src/img/home.png",980,560);
    img_voir = obj_img("src/img/voir.png",820,560);
    
    text_tab[A_VOUS] = obj_text("(à vous)",40,-1,150);
    text_tab[GAGNEE] = obj_text("GAGNÉ !!",40,-1,150);
    text_tab[PERDU] = obj_text("PERDU...",40,-1,150);
    text_tab[EGALITE] = obj_text("ÉGALITÉ :)",40,-1,150);
    text_tab[SCORE] = obj_text("2 - 2",40,800,10);
    text_tab[ATTENTE] = obj_text("En attente du tour de votre adversaire ...",20,670,300);

    image_BG_tex = tex_img_png("src/img/OthelloBG.png",renderer);
    SDL_QueryTexture(image_BG_tex, NULL, NULL, &(bg_rect.w), &(bg_rect.h));
}


/**
 * \fn int lancement_jeu(int modeJeu,t_matrice mat)
 * \brief Lance le jeu en fonction du mode choisie
 * \param modeJeu : le mode jeu choisi selon SOLO, DUO ou ONLINE.
 * \return entier
 */
int lancement_jeu(int modeJeu, int type){ 
    int running = 1;
    char msg[1024];    
    
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
        joueur2= (modeJeu == SOLO ? "Super IA" : "Joueur 2");
    }
    text_tab[J1] = obj_text(joueur1,40,670,110);
    text_tab[J2] = obj_text(joueur2,40,930,110);

    
    srand(time(NULL));
    //if(modeJeu==QUITTER) return 0;
    
    init_matrice(mat);

    //Couleur aléatoire si DUO, sinon noir commence
    if(modeJeu==DUO) joueur = (rand()%2 ? NOIR : BLANC);
    else joueur=NOIR;
    
    //Notre couleur si on joue en ligne
    if(modeJeu == ONLINE){
        joueur_vous = type == SERVEUR ? BLANC : NOIR;
    }
    joueur_sauv=joueur;
    //init_jeuSDL();
    
    i=0;
    
    fprintf(stderr,"MACOULEUR : %c '%c'\n",joueur_vous,joueur);

    /* Le fond de la fenêtre sera vert */

        while(running) {
            SDL_Event e;           
            while(SDL_PollEvent(&e)){
                switch(e.type) {
                    case SDL_QUIT:
                        if(modeJeu == ONLINE) envoyer("-2;-2", PORT_HOTE);
                        exit(0);
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        SDL_GetMouseState(&x,&y);
                        //REPLAY
                        if(pointe(img_replay.rect,x,y) && modeJeu != ONLINE){
                            init_matrice(mat);
                            arret=NON;
                            joueur=joueur_sauv;
                        }
                       if(pointe(img_home.rect,x,y)){
                            running=0;
                            if(modeJeu == ONLINE) envoyer("-2;-2", PORT_HOTE);
                            return 0;
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
                        }else if(pointe(img_voir.rect,x,y)){
                                SDL_RenderClear(renderer);
                                afficher_matriceSDL(mat_final,' ',NON);
                                cpy_render(img_voir);
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
                        clear();
                        if(modeJeu == ONLINE && type == SERVEUR) afficher_matriceSDL(mat,' ',OUI);
                        else affichage_partie(mat,modeJeu);
                        
                        if(modeJeu == ONLINE){
                            if(type == SERVEUR){
                                memset(msg, '\0', sizeof(msg));
                                afficher_matriceSDL(mat,' ',OUI);
                                cpy_render(text_tab[ATTENTE]);
                                SDL_RenderPresent(renderer);
                                recevoir(msg, PORT_HOTE );
                                sscanf(msg,"%d;%d",&y,&x);
                                if(x > 0 && y > 0){
                                    jouer_coup(mat,x,y,joueur);
                                    afficher_cibleSDL(mat,x,y);
                                }else if(x == -1){
                                    joueur = joueur_suivant(joueur);
                                    //alerter(que le joueur a quitté la partie)
                                }else if(x == -2){
                                    aff_joueur_parti();
                                    return 0;//menu_SDL();
                                }
                                //envoyer(msg, PORT_EXT);
                                type = !type;
                                joueur = joueur_suivant(joueur);
                            }
                        }
                        afficher();
                        break;
                }
            }
        }
    return 0;
}


int affichage_partie(t_matrice mat,int modeJeu){
    /* Le fond de la fenêtre sera vert */
    
    SDL_SetRenderDrawColor(renderer, 24, 124, 58, 255);
    clear();
    cpy_render(text_tab[J1]);
    cpy_render(text_tab[J2]);

    calculer_score(mat,&score_j1,&score_j2);
    sprintf(score_aff, "%d - %d", score_j1, score_j2);
    text_tab[SCORE] = obj_text(score_aff,55,x_obj(text_tab[SCORE]),y_obj(text_tab[SCORE]));

    /* Le fond de la fenêtre sera vert */
    //SDL_SetRenderDrawColor(renderer, 24, 124, 58, 255);
    
    
    /* On fait le rendu ! */
    if (partie_termineeSDL(mat)){
        arret=OUI;
        copie_mat(mat,mat_final);
        //VOIR
        cpy_render(img_voir);
        afficher_gagnant(mat);
    }
    else afficher_matriceSDL(mat, joueur, NON);

    if(!partie_termineeSDL(mat)){
        cpy_render(joueur == NOIR ? img_noirTour : img_noir);
        cpy_render(joueur == BLANC ? img_blancTour : img_blanc);
        text_tab[A_VOUS].rect.x = joueur == NOIR ? x_obj(img_noir) : x_obj(img_blanc);
        if(!(modeJeu == ONLINE) || joueur == joueur_vous) cpy_render(text_tab[A_VOUS]);
    }else{
        gagnant=afficher_gagnant(mat);
        cpy_render(gagnant == NOIR ? img_noirTour : img_noir);
        cpy_render(gagnant == BLANC ? img_blancTour : img_blanc);

        if(gagnant == EGALITE){
            text_tab[EGALITE].rect.x=x_obj(img_noir);
            cpy_render(text_tab[EGALITE]);
            text_tab[EGALITE].rect.x=x_obj(img_blanc);
            cpy_render(text_tab[EGALITE]);

        }else{
            text_tab[GAGNEE].rect.x=x_obj(gagnant == NOIR ? img_noir : img_blanc);
            cpy_render(text_tab[GAGNEE]);
            text_tab[PERDU].rect.x=x_obj(gagnant != NOIR ? img_noir : img_blanc);
            cpy_render(text_tab[PERDU]);
        }
    }
    cpy_render(text_tab[SCORE]);
    cpy_render(img_home);
    if(modeJeu != ONLINE) cpy_render(img_replay);
    return 0;
}