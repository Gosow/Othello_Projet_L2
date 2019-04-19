SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib

INCLUDES=-I${SDLINC_DIR}
CC=gcc
OPTS=-g -o
CFLAGS=-W -Wall
PROG=othello_terminal_ed
FICHIER_O=gest_mat.o main_terminal.o 
OUTIL=./src/fonc_boite_outils/


all: javel prog



prog:$(FICHIER_O)
	${CC} ${OPTS} ${PROG} $(FICHIER_O)   ${CFLAGS}
	mv ${PROG} ../../bin
	mv *.o ../../obj
	@echo "\033[31m Ended succesfuly "
	@echo "\033[31m go in bin directory to see executalbe"
	@echo "\033[31m go in obj directory to see .o files"

gest_mat.o: gest_mat.c gest_mat.h
	${CC} ${OPTS} gest_mat.o -c gest_mat.c ${CFLAGS}

main_terminal.o : main_terminal.c
	${CC} ${OPTS} main_terminal.o -c main_terminal.c ${CFLAGS}

javel :
	rm -f ${PROG}
	rm -f ../../bin/${PROG}
	rm -f gest_mat.o main_terminal.o 
	rm -f ../../bin/gest_mat.o ../../bin/main_terminal.o 
	@echo "\033[31m Javeling ended succesfully "
	

clean :
	rm -f gest_mat.o main_terminal.o 
	rm -f ../../bin/gest_mat.o ../../bin/main_terminal.o 
	@echo "\033[31m Cleaning ended succesfully "

	

