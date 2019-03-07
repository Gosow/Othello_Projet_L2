#include "SDL_jeu.h"

int afficher_matriceSDL(t_matrice mat,SDL_Renderer* renderer){
    SDL_Texture *temp;
    int i=0,j=0;
    SDL_Rect imgBtnRect;
    //Chargement de l'image bouton
    SDL_Texture *image_caseNorm_tex = tex_img_png("./img/caseNorm.png",renderer);
    //Chargement de l'image bouton (utilisé quand la souris passe sur l'image)
    SDL_Texture *image_casePoss_tex = tex_img_png("./img/casePoss.png",renderer);
    
    //PION NOIR
    SDL_Texture *image_noir_tex = tex_img_png("./img/noir.png",renderer);
    //PION BLANC
    SDL_Texture *image_blanc_tex = tex_img_png("./img/blanc.png",renderer);
    imgBtnRect.x = 0;
    imgBtnRect.y = 0;
    SDL_QueryTexture(image_caseNorm_tex, NULL, NULL, &(imgBtnRect.w), &(imgBtnRect.h));
    
    for(i=0;i<N;i++){
        imgBtnRect.y = i*82;
        imgBtnRect.x = 0;
        for(j=0;j<N;j++){
            if(coup_valide(mat,i,j,1)){
                temp = image_casePoss_tex;
            }else{
                temp = image_caseNorm_tex;
            }
            SDL_RenderCopy(renderer, temp, NULL, &imgBtnRect);
            if(mat[i][j] == NOIR){
                SDL_RenderCopy(renderer, image_noir_tex, NULL, &imgBtnRect);
            }
            else if(mat[i][j] == BLANC){
                SDL_RenderCopy(renderer, image_blanc_tex, NULL, &imgBtnRect);
            }
            imgBtnRect.x += 82;
        }
    }
}