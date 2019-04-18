
SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib

INCLUDES=-I${SDLINC_DIR}
CC=gcc

PROG=othello_terminal_ed


all: projet

projet: main_terminal.c
	@$(CC) -o ${PROG} main_terminal.c define.h include.h gest_mat.c gest_mat.h 
	mv ${PROG} ../../bin
	@echo "Ended succesfuly "
	@echo "go in bin directory to see executalbe"

	


	

