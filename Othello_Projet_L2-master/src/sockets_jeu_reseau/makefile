
#CC=gcc
#FLAGS=-Wall -g

#all: client2 serveur2


#%2.o: %2.c define.h gest_matrice.h gest_aff.h
	#$(CC) -o $@ -c $< $(FLAGS)
#

#client2: client2.o
	#$(CC) -o $@ $^ $(LDFLAGS)

#serveur2: serveur.c define.h gest_matrice.h gest_aff.h
	#$(CC) -o serveur2 serveur2.c

#clean:
#	rm -rf *2.o

#mrproper: clean
#	rm -rf $(EXEC)


client2:
	gcc client2.c ../gest_matrice.c ../gest_aff.c ../define.h ../gest_matrice.h ../gest_aff.h


serveur2:
	gcc serveur.c ../gest_matrice.c ../gest_aff.c ../define.h ../gest_matrice.h ../gest_aff.h