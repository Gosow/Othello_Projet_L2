#include "./interface_graphique/SDL_jeu.h"

int main(int argc, char** argv)
{
    /* Initialisation simple */
    t_matrice mat;
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

    menu_SDL(mat);
    
	TTF_Quit();
    SDL_Quit();

    return 0;
}
