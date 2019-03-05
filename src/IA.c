/*
 * Fonctions permettant de gerer l'intelligence artificielle
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/IA.h"
#include "../include/objets.h"
#include "../include/labyrinthe.h"



coord_t chemin_court(char labyrinthe[N_LAB][M_LAB], coord_t* coord_dep, coord_t* coord_arr) {

}

coord_t chemin_anticipe(char labyrinthe[N_LAB][M_LAB], coord_t* coord_dep, coord_t* coord_arr) {

}

coord_t chemin_fuir(char labyrinthe[N_LAB][M_LAB], coord_t* coord_dep, coord_t* coord_arr) {

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
