
SDL_Texture* tex_img_png(char * s, SDL_Renderer renderer){

    SDL_RWops *rwop=SDL_RWFromFile("./img/btn.png", "rb");
	image=IMG_LoadPNG_RW(rwop);
	if(!image) {
	     printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
	}
	SDL_Texture *image_tex = SDL_CreateTextureFromSurface(renderer, image); 
	if(!image_tex){
		fprintf(stderr, "Erreur à la création du rendu de l'image : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_FreeSurface(image); /* on a la texture, plus besoin de l'image */
    return image_tex;
}

SDL_Texture tex_text(char* font,int size, char* s, SDL_Color color, int x, int y, SDL_Renderer* renderer){
    SDL_Rect txtDestRect;
    if( (policeTitre = TTF_OpenFont(font, size)) == NULL){
        fprintf(stderr, "erreur chargement font\n");
        exit(EXIT_FAILURE);
    }
    SDL_Surface *texte = TTF_RenderUTF8_Blended(policeTitre, s, color);
    if(!texte){
        fprintf(stderr, "Erreur à la création du texte : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Texture *texte_tex = SDL_CreateTextureFromSurface(renderer, texte);
    if(!texte_tex){
        fprintf(stderr, "Erreur à la création du rendu du texte : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_FreeSurface(texte); /* on a la texture, plus besoin du texte */
    /* Position ou sera mis le texte dans la fenêtre */
    txtDestRect.x = x;
    txtDestRect.y = y;
    SDL_QueryTexture(texte_tex, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));
    TTF_CloseFont(policeTitre); /* Doit être avant TTF_Quit() */
    return texte_tex;
}