#include "./interface_graphique/SDL_jeu.h"

int main(void)
{
    /* Initialisation simple */
    
    init_matrice(mat);
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }


	/* Initialisation TTF */
	if(TTF_Init() == -1) {
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}

    /*Initialisation Mixer*/
    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096)==-1){
        fprintf(stderr, "Erreur à l'initailisation de l'audio\n");
        exit(EXIT_FAILURE);
    }

    music = Mix_LoadMUS("./music/test.ogg");
    if(music == NULL){
        fprintf(stderr, "Erreur du chargement de l'audio : %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
        
    }
    song=1;
    Mix_PlayMusic(music,-1);

    menu_SDL();
    
    Mix_FreeMusic(music);
    Mix_CloseAudio();
	TTF_Quit();
    SDL_Quit();

    return 0;
}
