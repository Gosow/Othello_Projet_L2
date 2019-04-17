
SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib

INCLUDES=-I${SDLINC_DIR}

PROG=othello

all: projet

projet: main_terminal.c
	${CC} -o ${PROG} main_terminal.c header/define.h header/include.h fonc_boite_outils/gest_mat.c fonc_boite_outils/gest_matrice.h 
clean:
	rm -f ${PROG}
	rm -f *.o
