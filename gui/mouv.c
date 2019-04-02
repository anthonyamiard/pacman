#include <stdio.h>
#include <stdlib.h>
#include "mouv.h"
#include "../include/objets.h"
#include "gui_lab.h"
#include "../include/labyrinthe.h"

int deplace_coord(const coord_t * coord, coord_t * coord_fines, const char labyrinthe[N_LAB][M_LAB], char dir) {
	switch(dir) {
		case 'h':
			if(coord->y > 0 && est_chemin(labyrinthe[coord->y-1][coord->x]))
				coord_fines->y -= 3;
			break;
		case 'b':
			if(coord->y < N_LAB - 1 && est_chemin(labyrinthe[coord->y+1][coord->x]))
				coord_fines->y += 3;
			break;
		case 'd':
			if(coord->x < M_LAB - 1 && est_chemin(labyrinthe[coord->y][coord->x+1]))
				coord_fines->x += 3;
			break;
		case 'g':
			if(coord->x > 0 && est_chemin(labyrinthe[coord->y][coord->x-1]))
				coord_fines->x -= 3;
			break;
	}
	return 0;
}
