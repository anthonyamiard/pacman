#include <stdio.h>
#include <stdlib.h>
#include "mouv.h"
#include "../include/objets.h"
#include "gui_lab.h"
#include "../include/labyrinthe.h"

int deplace_coord(coord_t * coord, const char labyrinthe[N_LAB][M_LAB], char dir) {
	int x = coord->x / TAILLE_CASE;
	int y = coord->y / TAILLE_CASE;
	switch(dir) {
		case 'h':
			if(y > 0 && est_chemin(labyrinthe[y-1][x]))
				coord->y -= 3;
			break;
		case 'b':
			if(y < N_LAB - 1 && est_chemin(labyrinthe[y+1][x]))
				coord->y += 3;
			break;
		case 'd':
			if(x < M_LAB - 1 && est_chemin(labyrinthe[y][x+1]))
				coord->x += 3;
			break;
		case 'g':
			if(x > 0 && est_chemin(labyrinthe[y][x-1]))
				coord->x -= 3;
			break;
	}
	return 0;
}
