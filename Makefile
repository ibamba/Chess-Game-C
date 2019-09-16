CC = gcc

CFLAGS = -g -Wall -pedantic 

FICHIERS = piece.o coup.o sdl.o liste_cj.o liste_pc.o partie.o main.o

PROG = chess

all : $(FICHIERS)
	$(CC) $(CFLAGS) $(FICHIERS) -o $(PROG)

piece.o : piece.c
	$(CC) -c $(CFLAGS) piece.c

coup.o : coup.c
	$(CC) -c $(CFLAGS) coup.c

sdl.o : sdl.c
	$(CC) -c $(CFLAGS) sdl.c

liste_cj.o : liste_cj.c
	$(CC) -c $(CFLAGS) liste_cj.c

liste_pc.o : liste_pc.c
	$(CC) -c $(CFLAGS) liste_pc.c

partie.o : partie.c
	$(CC) -c $(CFLAGS) partie.c

main.o : main.c
	$(CC) -c $(CFLAGS) main.c


clean : 
	rm  -rf *.o
	rm  -rf *~
