
SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib

INCLUDES=-I${SDLINC_DIR}

PROG=othello

all: projet

projet: main.c
	${CC} -o ${PROG} main.c gest_matrice.c gest_matrice.h define.h

clean:
	rm -f ${PROG}
	rm -f *.o
