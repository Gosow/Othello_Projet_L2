#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL_image.h"

//compilation SDL2 : gcc matrice.c $(sdl2-config --cflags --libs) -o matrice


int main(int argc, char **argv)
{	
    
    SDL_Event evenements;
    int terminer=0;
    

   // Initialisation de la SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr,"Erreur lors de la création de la fenetre %s\n",SDL_GetError());
        SDL_Quit();
        
        return -1;
    }



    // Boucle principale
    //SDL_Delay(5000)
    while(!terminer)
    {
	SDL_WaitEvent(&evenements);
		
	if(evenements.window.event == SDL_WINDOWEVENT_CLOSE)
	    terminer = 1;
    }
	
	
    // On quitte la SDL
	/*SDL_FreeSurface(image);
    SDL_DestroyWindow(fenetre);*/
    SDL_Quit();
	
    return 0;
}