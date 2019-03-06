/*
 * Fonctions permettant de gerer l'intelligence artificielle
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/IA.h"
#include "../include/objets.h"
#include "../include/labyrinthe.h"

#define N 6
#define M 1

int total = 0;

int joueur(int total) {
	if(N - total <= M) {
		return 1;
	} else {
		int i, max = INT_MIN, tmp;
		for(i = 1; i <= M; i++) {
			tmp = adversaire(total + i);
			if(tmp > max)
				max = tmp;
		}
		return max;
	}
}

int adversaire(int total) {
	if(N - total <= M) {
		return -1;
	} else {
		int i, min = INT_MAX, tmp;
		for(i = 1; i <= M; i++) {
			tmp = joueur(total + i);
			if(tmp < min)
				min = tmp;
		}
		return min;
	}
}

/* Simule un coup optimal */
int coup_opti(int total) {
	if(N - total <= M)
		return N - total;
	int i;
	for(i = 1; i <= M; i++) {
		if(adversaire(total + i) == 1) {
			return i;
		}
	}
	return rand() % (M - 1) + 1;
}

coord_t chemin_court(char labyrinthe[N_LAB][M_LAB], coord_t* coord_dep, coord_t* coord_arr) {
    int x,y;
    coord_t res;
    x = coord_dep->x;
	y = coord_dep->y;
	i = coord_arr->x;
	j = coord_arr->y;

	do{
        if(les cases sont + N)
            chemin_aleatoire(labyrinthe(res.x)(rex.y),coord_dep,coord_arr);
        else
            coup_opti(total);


	}while(!est_chemin(labyrinthe[res.y][res.x]) && x != i && y != j);
}

coord_t chemin_anticipe(char labyrinthe[N_LAB][M_LAB], coord_t* coord_dep, coord_t* coord_arr) {

}

coord_t chemin_fuir(char labyrinthe[N_LAB][M_LAB], coord_t* coord_dep, coord_t* coord_arr) {
    inverse de chemin court?
}

coord_t chemin_aleatoire(char labyrinthe[N_LAB][M_LAB], coord_t* coord_dep, coord_t* coord_arr) {

	int x,y;
	coord_t res;

	x = coord_dep->x;
	y = coord_dep->y;

	do{
		if(rand() %2)
			res.x=x+1;
		else
			res.x=x-1;
		if(rand() %2)
			res.y=y+1;
		else
			res.y=y-1;
	}while(!est_chemin(labyrinthe[res.y][res.x]));

	return res;
}

int fantome(char labyrinthe[N_LAB][M_LAB], fantome_t* fantome, joueur_t* joueur, int vitesse) {

}

int ramasse_pacgum(char labyrinthe[N_LAB][M_LAB], joueur_t* joueur) {

}
