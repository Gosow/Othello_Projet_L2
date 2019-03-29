
CC=gcc
FLAGS=-Wall -g
OBJS=gest_matrice.o gest_socket.o

all: client serveur
gcc client.c socket.h ../gest_matrice.c ../gest_matrice.h ../define.h gest_socket.c gest_socket.h
%.o: %.c socket.h
	$(CC) -c $< $(FLAGS) -o $@


client: client.o $(OBJS)
	$(CC)  -o client.c client.o $(OBJS)

serveur: serveur.o $(OBJS)
	$(CC)  -o serveur.c serveur.o $(OBJS)

serveur.o: serveur.c socket.h
	$(CC)  serveur.c -o serveur.o

client.o: client.c socket.h
	$(CC)  client.c -o client.o

gest_matrice.o: ../gest_matrice.c ../gest_matrice.h
		$(CC)  ../gest_matrice.c -o gest_matrice.o

gest_socket.o: gest_socket.c gest_socket.h
		$(CC)  gest_socket.c -o gest_socket.o

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
