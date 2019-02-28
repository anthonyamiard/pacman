main: labyrinthe.o main.o
	gcc main.o labyrinthe.o -o main
main.o: main.c
	gcc -c main.c
labyrinthe.o: labyrinthe.c labyrinthe.h taille_lab.h
	gcc -c labyrinthe.c
IA.o: IA.c IA.h taille.h
	gcc -c IA.c
