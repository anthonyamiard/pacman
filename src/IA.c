/*
 * Fonctions permettant de gerer l'intelligence artificielle
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/IA.h"
#include "../include/objets.h"
#include "../include/labyrinthe.h"


/*Pathfinding pour M cases */


coord_t chemin_court(char labyrinthe[N_LAB][M_LAB], coord_t* coord_dep, coord_t* coord_arr) {
	fantome_t * f_bleu;
}

coord_t chemin_anticipe(char labyrinthe[N_LAB][M_LAB], coord_t* coord_dep, coord_t* coord_arr) {
	fantome_t * f_rose;
}

coord_t chemin_fuir(char labyrinthe[N_LAB][M_LAB], coord_t* coord_dep, coord_t* coord_arr) {
	fantome_t * f_orange;
}

coord_t chemin_aleatoire(char labyrinthe[N_LAB][M_LAB], coord_t* coord_dep, coord_t* coord_arr) {
	fantome_t * f_rouge;
	
}

int fantome(char labyrinthe[N_LAB][M_LAB], fantome_t* fantome, joueur_t* joueur, int vitesse) {

}

int ramasse_pacgum(char labyrinthe[N_LAB][M_LAB], joueur_t* joueur) {

}
