/*
 * Fonctions permettant de gerer l'intelligence artificielle
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../include/IA.h"
#include "../include/objets.h"
#include "../include/labyrinthe.h"

coord_t chemin_court(char labyrinthe[N_LAB][M_LAB], coord_t* coord_dep, coord_t* coord_arr) {
  	int i,j;
	int lab_numero[N_LAB][M_LAB];
	coord_t * temp = coord_arr;

	for(i=0;i<30;i++){
		for(j=0;j<27;j++){
 			if(labyrinthe[i][j] == 'm')
				lab_numero[i][j] = -1;
			else
				lab_numero[i][j] == 0;
		}
	}
	lab_numero[coord_arr->y][coord_arr->x] = 0;
	lab_numero[coord_dep->y][coord_dep->x] = -2;

	do {
		if(!lab_numero[i][j] == -1){
			lab_numero[temp->y][temp->x+1];
			if(!lab_numero[i][j] == -1)
				lab_numero[temp->y][temp->x+1] +=1;
		}
		if(!lab_numero[i][j] == -1){
			lab_numero[temp->y][temp->x-1];
			if(!lab_numero[i][j] == -1)
				lab_numero[temp->y][temp->x+1] +=1;
		}
		if(!lab_numero[i][j] == -1){
			lab_numero[temp->y+1][temp->x];
			if(!lab_numero[i][j] == -1)
				lab_numero[temp->y-1][temp->x] +=1;
		}
		if(!lab_numero[i][j] == -1){
			lab_numero[temp->y-1][temp->x];
			if(!lab_numero[i][j] == -1)
				lab_numero[temp->y+1][temp->x] +=1;
		}


	} while(lab_numero[coord_dep->y][coord_dep->x] == -2);
	do{
		if(!lab_numero[coord_dep->y][coord_dep->x] == -2);
		
	} while(1 /*Pour rendre le fichier compilable*/);

}

coord_t chemin_anticipe(char labyrinthe[N_LAB][M_LAB], coord_t* coord_dep, coord_t* coord_arr) {

}

coord_t chemin_fuir(char labyrinthe[N_LAB][M_LAB], coord_t* coord_dep, coord_t* coord_arr) {
    /*inverse de chemin court?*/
}

coord_t chemin_aleatoire(char labyrinthe[N_LAB][M_LAB], coord_t* coord_dep, coord_t* coord_arr) {

	int x,y;
	coord_t res;

	x = coord_dep->x;
	y = coord_dep->y;

	do{
		coord_alea(x ,y ,&(res.x) ,&(res.y));
	}while(!est_chemin(labyrinthe[res.y][res.x]));

	return res;
}

int fantome(char labyrinthe[N_LAB][M_LAB], fantome_t* fantome, joueur_t* joueur, int vitesse) {

}

int ramasse_pacgum(char labyrinthe[N_LAB][M_LAB], joueur_t* joueur) {

}
