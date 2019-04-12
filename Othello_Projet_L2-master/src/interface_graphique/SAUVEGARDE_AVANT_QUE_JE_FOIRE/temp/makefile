
CC=gcc

SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=/usr/local/opt/
SDLINC_DIR=${SDL_DIR}/include

LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I${SDLINC_DIR} 

PROG=menu_SDL

all: sdl_text

sdl_text: menu_SDL.c
	${CC} -o ${PROG} menu_SDL.c ${LIBS} ${INCLUDES}

clean: 
	rm -f ${PROG}
	rm -f *.o


