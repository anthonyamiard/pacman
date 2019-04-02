#include <stdio.h>
#include <stdlib.h>
#include "../include/objets.h"
#include "../include/labyrinthe.h"
#include "gui_lab.h"
#include "mouv.h"
#include "dessin.h"

int deplace_coord(const coord_t * coord, SDL_Rect * position, const char labyrinthe[N_LAB][M_LAB], char dir) {
	switch(dir) {
		case 'h':
			if(coord->y > 0 && est_chemin(labyrinthe[coord->y-1][coord->x]))
				position->y -= 3;
			break;
		case 'b':
			if(coord->y < N_LAB - 1 && est_chemin(labyrinthe[coord->y+1][coord->x]))
				position->y += 3;
			break;
		case 'd':
			if(coord->x < M_LAB - 1 && est_chemin(labyrinthe[coord->y][coord->x+1]))
				position->x += 3;
			break;
		case 'g':
			if(coord->x > 0 && est_chemin(labyrinthe[coord->y][coord->x-1]))
				position->x -= 3;
			break;
	}
	return 0;
}

void deplace_joueur(joueur_t * joueur, char labyrinthe[N_LAB][M_LAB], SDL_Renderer * rend) {
	if(joueur->position.x % TAILLE_CASE == 0 && joueur->position.y % TAILLE_CASE == 0) {
		joueur->coord.x = joueur->position.x / TAILLE_CASE;
		joueur->coord.y = joueur->position.y / TAILLE_CASE;
		pacdir = joueur->nextdir;
	}
	deplace_coord(&(joueur->coord), &(joueur->position), labyrinthe, pacdir);
	if(labyrinthe[joueur->coord.y][joueur->coord.x] == 'p') {
		joueur->score += 1;
		labyrinthe[joueur->coord.y][joueur->coord.x] = 'c';
	}
	SDL_RenderCopy(rend, sprites.pac, NULL, &(joueur->position));
}

void deplace_fantome(fantome_t * fantome, const char labyrinthe[N_LAB][M_LAB], SDL_Renderer * rend) {
	if(fantome->position.x % TAILLE_CASE == 0 && fantome->position.y % TAILLE_CASE == 0) {
		fantome->coord.x = fantome->position.x / TAILLE_CASE;
		fantome->coord.y = fantome->position.y / TAILLE_CASE;
		fantome->dir = fantome->nextdir;
	}
	deplace_coord(&(fantome->coord), &(fantome->position), labyrinthe, fantome->dir);
	SDL_RenderCopy(rend, fantome->texture, NULL, &(fantome->position));
}
