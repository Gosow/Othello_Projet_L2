
CC=gcc
FLAGS=-Wall -g
OBJS=gest_matrice.o 

all: client serveur 

%.o: %.c socket.h 
	$(CC) -c $< $(FLAGS) -o $@


client: client.o $(OBJS)
	$(CC)  $^  (LDFLAGS) -o $@

serveur: serveur.o $(OBJS)
	$(CC)  serveur.c  -o serveur 

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)

