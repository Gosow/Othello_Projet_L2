
CC=gcc
OPTS=-g -o
CFLAGS=-W -Wall
SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=./../lib/
SDLINC_DIR=${SDL_DIR}/include
INT_SDL=./interface_graphique/

FICHIER_O=plateau_SDL.o menu_SDL.o main_SDL.o ToTexture.o gest_matrice.o afficher_jeuSDL.o min_max.o liste.o client.o serveur.o
LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer
INCLUDES=-I${SDLINC_DIR}

PROG=main_SDL

all: javel othello

othello: ${FICHIER_O}
	${CC} ${OPTS} ${PROG} $(FICHIER_O) ${LIBS} ${INCLUDES} ${CFLAGS}
	#rm -f *.o
	#./main_SDL

main_SDL.o: main_SDL.c ${INT_SDL}SDL_jeu.h
	${CC} ${OPTS} main_SDL.o -c main_SDL.c ${CFLAGS}

ToTexture.o: ${INT_SDL}ToTexture.c ${INT_SDL}SDL_jeu.h
	${CC} ${OPTS} ToTexture.o -c ${INT_SDL}ToTexture.c ${CFLAGS}

plateau_SDL.o: ${INT_SDL}plateau_SDL.c ${INT_SDL}SDL_jeu.h 
	${CC} ${OPTS} plateau_SDL.o -c ${INT_SDL}plateau_SDL.c ${CFLAGS}

menu_SDL.o: ${INT_SDL}menu_SDL.c ${INT_SDL}SDL_jeu.h
	${CC} ${OPTS} menu_SDL.o -c ${INT_SDL}menu_SDL.c ${CFLAGS}

afficher_jeuSDL.o : ${INT_SDL}afficher_jeuSDL.c ${INT_SDL}SDL_jeu.h
	${CC} ${OPTS} afficher_jeuSDL.o -c ${INT_SDL}afficher_jeuSDL.c ${CFLAGS}

gest_matrice.o: gest_matrice.c gest_matrice.h
	${CC} ${OPTS} gest_matrice.o -c gest_matrice.c ${CFLAGS}

min_max.o: min_max.c min_max.h
	${CC} ${OPTS} min_max.o -c min_max.c ${CFLAGS}

liste.o: liste.c liste.h
	${CC} ${OPTS} liste.o -c liste.c ${CFLAGS}

client.o: ${INT_SDL}reseau/client.c ${INT_SDL}reseau/reseau.h
	${CC} ${OPTS} client.o -c ${INT_SDL}reseau/client.c ${CFLAGS}

serveur.o: ${INT_SDL}reseau/serveur.c ${INT_SDL}reseau/reseau.h
	${CC} ${OPTS} serveur.o -c ${INT_SDL}reseau/serveur.c ${CFLAGS}

clean:
	rm -f *.o

javel:
	rm -f *.o
	rm -f ${PROG}


