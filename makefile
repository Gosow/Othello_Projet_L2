
CC=gcc
OPTS=-g -o
CFLAGS=-W -Wall
SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=./lib/
SDLINC_DIR=${SDL_DIR}/include
INT_SDL=./src/interface_graphique/
IA=./src/IA/
RES=./src/reseau/
OUTIL=./src/fonc_boite_outils/

FICHIER_O=plateau_SDL.o menu_SDL.o main_SDL.o ToTexture.o gest_matrice.o objet_SDL.o afficher_jeuSDL.o eval.o min_max.o liste.o client.o serveur.o
LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer
INCLUDES=-I${SDLINC_DIR}

PROG=main_SDL

all: javel othello

othello: ${FICHIER_O}
	#rm ./obj/*.o
	${CC} ${OPTS} ${PROG} $(FICHIER_O) ${LIBS} ${INCLUDES} ${CFLAGS}
	mv *.o obj/
	mv main_SDL bin/
	

main_SDL.o: ./src/main_SDL.c ${INT_SDL}SDL_jeu.h
	${CC} ${OPTS} main_SDL.o -c ./src/main_SDL.c ${CFLAGS}

ToTexture.o: ${OUTIL}ToTexture.c ${INT_SDL}SDL_jeu.h
	${CC} ${OPTS} ToTexture.o -c ${OUTIL}ToTexture.c ${CFLAGS}

plateau_SDL.o: ${INT_SDL}plateau_SDL.c ${INT_SDL}SDL_jeu.h 
	${CC} ${OPTS} plateau_SDL.o -c ${INT_SDL}plateau_SDL.c ${CFLAGS}

menu_SDL.o: ${INT_SDL}menu_SDL.c ${INT_SDL}SDL_jeu.h
	${CC} ${OPTS} menu_SDL.o -c ${INT_SDL}menu_SDL.c ${CFLAGS}

afficher_jeuSDL.o : ${INT_SDL}afficher_jeuSDL.c ${INT_SDL}SDL_jeu.h
	${CC} ${OPTS} afficher_jeuSDL.o -c ${INT_SDL}afficher_jeuSDL.c ${CFLAGS}

gest_matrice.o: ${OUTIL}gest_matrice.c ${OUTIL}gest_matrice.h
	${CC} ${OPTS} gest_matrice.o -c ${OUTIL}gest_matrice.c ${CFLAGS}

objet_SDL.o: ${OUTIL}objet_SDL.c ${OUTIL}objet_SDL.h
	${CC} ${OPTS} objet_SDL.o -c ${OUTIL}objet_SDL.c ${CFLAGS}

eval.o: ${IA}eval.c ${IA}eval.h
	${CC} ${OPTS} eval.o -c ${IA}eval.c ${CFLAGS}

min_max.o: ${IA}min_max.c ${IA}min_max.h
	${CC} ${OPTS} min_max.o -c ${IA}min_max.c ${CFLAGS}

liste.o: ${OUTIL}liste.c ${OUTIL}liste.h
	${CC} ${OPTS} liste.o -c ${OUTIL}liste.c ${CFLAGS}

client.o: ${RES}client.c ${RES}/reseau.h
	${CC} ${OPTS} client.o -c ${RES}client.c ${CFLAGS}

serveur.o: ${RES}serveur.c ${RES}reseau.h
	${CC} ${OPTS} serveur.o -c ${RES}serveur.c ${CFLAGS}

clean:
	rm -f *.o

javel:
	rm -f *.o
	rm -f ${PROG}


