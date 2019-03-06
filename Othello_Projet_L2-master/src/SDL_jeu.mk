
CC=gcc
OPTS=-g -o
CFLAGS=-W -Wall
SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=./../lib/
SDLINC_DIR=${SDL_DIR}/include
INT_SDL=./interface_graphique/

FICHIER_O=plateau_SDL.o menu_SDL.o main_SDL.o ToTexture.o gest_matrice.o gest_aff.o
LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I${SDLINC_DIR}

PROG=main_SDL

all: othello

othello: ${FICHIER_O}
	${CC} ${OPTS} ${PROG} $(FICHIER_O) ${LIBS} ${INCLUDES} ${CFLAGS}

main_SDL.o: main_SDL.c ${INT_SDL}SDL_jeu.h
	${CC} -o main_SDL.o -c main_SDL.c ${CFLAGS}

ToTexture.o: ${INT_SDL}ToTexture.c ${INT_SDL}SDL_jeu.h
	${CC} -o ToTexture.o -c ${INT_SDL}ToTexture.c ${CFLAGS}

plateau_SDL.o: ${INT_SDL}plateau_SDL.c ${INT_SDL}SDL_jeu.h 
	${CC} -o plateau_SDL.o -c ${INT_SDL}plateau_SDL.c ${CFLAGS}

menu_SDL.o: ${INT_SDL}menu_SDL.c ${INT_SDL}SDL_jeu.h
	${CC} -o menu_SDL.o -c ${INT_SDL}menu_SDL.c ${CFLAGS}

gest_matrice.o: gest_matrice.c gest_matrice.h
	${CC} -o gest_matrice.o -c gest_matrice.c ${CFLAGS}

gest_aff.o: gest_aff.c gest_aff.h
	${CC} -o gest_aff.o -c gest_aff.c ${CFLAGS}

clean:
	rm -f *.o

javel:
	rm -f *.o
	rm -f ${PROG}


