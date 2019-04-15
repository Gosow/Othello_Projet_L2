#include "header/define.h"
#include "highscore.h"
#include <stdio.h>
#include <stdlib.h>




void main(void){
    t_highscore h[10];
    init_highscore(h,"yac","ordi");
        afficher_hg(h);

    write_highscore(h,"yac",120);
    afficher_hg(h);
}