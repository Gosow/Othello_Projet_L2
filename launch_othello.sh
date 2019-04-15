#!/bin/bash
cd src/
make -f SDL_jeu.mk mrproper
make -f SDL_jeu.mk
./main_SDL
make -f SDL_jeu.mk javel
exit 0