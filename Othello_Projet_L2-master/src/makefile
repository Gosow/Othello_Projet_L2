
SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include

LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I${SDLINC_DIR} 

PROG=othello

all: projet

projet: main.c
	${CC} -o ${PROG} main.c gest_matrice.c gest_aff.c gest_aff.h gest_matrice.h define.h ${LIBS} ${INCLUDES}

clean: 
	rm -f ${PROG}
	rm -f *.o


