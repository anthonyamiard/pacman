#include <stdio.h>
#include <stdlib.h>
#include "../include/objets.h"
#include "../include/labyrinthe.h"
#include "gui_lab.h"
#include "mouv.h"
#include "dessin.h"

int deplace_coord(const coord_t * coord, SDL_Rect * position,
				  const char labyrinthe[N_LAB][M_LAB], char dir, int vitesse) {
	switch(dir) {
		case 'h':
			if((coord->y > 0 && est_chemin(labyrinthe[coord->y-1][coord->x])) ||
				est_dans_boite(coord->x, coord->y))
				position->y -= vitesse;
			break;
		case 'b':
			if((coord->y < N_LAB - 1 &&
				est_chemin(labyrinthe[coord->y+1][coord->x])) ||
				est_dans_boite(coord->x, coord->y))
				position->y += vitesse;
			break;
		case 'd':
			if((coord->x < M_LAB - 1 &&
				est_chemin(labyrinthe[coord->y][coord->x+1])) ||
				est_dans_boite(coord->x, coord->y))
				position->x += vitesse;
			break;
		case 'g':
			if((coord->x > 0 &&
				est_chemin(labyrinthe[coord->y][coord->x-1])) ||
				est_dans_boite(coord->x, coord->y))
				position->x -= vitesse;
			break;
	}
	return 0;
}

void deplace_joueur(joueur_t * joueur, char labyrinthe[N_LAB][M_LAB], SDL_Renderer * rend) {
	if(joueur->position.x % TAILLE_CASE == 0 &&
		joueur->position.y % TAILLE_CASE == 0) {
		joueur->coord.x = joueur->position.x / TAILLE_CASE;
		joueur->coord.y = joueur->position.y / TAILLE_CASE;
		pacdir = joueur->nextdir;
	}
	deplace_coord(&(joueur->coord), &(joueur->position), labyrinthe, pacdir, 3);
	if(labyrinthe[joueur->coord.y][joueur->coord.x] == 'p') {
		joueur->score += 1;
		labyrinthe[joueur->coord.y][joueur->coord.x] = 'c';
	}
	SDL_RenderCopy(rend, sprites.pac, NULL, &(joueur->position));
}

void deplace_fantome(fantome_t * fantome, char labyrinthe[N_LAB][M_LAB], SDL_Renderer * rend, joueur_t * joueur) {
	coord_t dest;
	if(fantome->position.x % TAILLE_CASE == 0 &&
		fantome->position.y % TAILLE_CASE == 0) {
		fantome->coord.x = fantome->position.x / TAILLE_CASE;
		fantome->coord.y = fantome->position.y / TAILLE_CASE;
		if((!est_dans_boite(fantome->coord.x, fantome->coord.y)) && (
			nb_chemins_voisins(labyrinthe, fantome->coord.x, fantome->coord.y)
			> 2 || (
			(fantome->dir == 'g' &&
			!est_chemin(labyrinthe[fantome->coord.y][fantome->coord.x-1])) ||
			(fantome->dir == 'd' &&
			!est_chemin(labyrinthe[fantome->coord.y][fantome->coord.x+1])) ||
			(fantome->dir == 'h' &&
			!est_chemin(labyrinthe[fantome->coord.y-1][fantome->coord.x])) ||
			(fantome->dir == 'b' &&
			!est_chemin(labyrinthe[fantome->coord.y+1][fantome->coord.x]))))) {
			dest = fantome->chemin(labyrinthe, &(fantome->coord),
								   &(joueur->coord));
			if(dest.x - fantome->coord.x < 0)
				fantome->dir = 'g';
			else if(dest.x - fantome->coord.x > 0)
				fantome->dir = 'd';
			else if(dest.y - fantome->coord.y < 0)
				fantome->dir = 'h';
			else
				fantome->dir = 'b';
		} else if(est_dans_boite(fantome->coord.x, fantome->coord.y)) {
			if(fantome->coord.x < X_BOITE)
				fantome->dir = 'd';
			else if(fantome->coord.x > X_BOITE + 1)
				fantome->dir = 'g';
			else
				fantome->dir = 'h';
		}
	}
	deplace_coord(&(fantome->coord), &(fantome->position), labyrinthe,
				  fantome->dir, 3);
	SDL_RenderCopy(rend, fantome->texture, NULL, &(fantome->position));
}

int collision(const joueur_t * joueur, const fantome_t * fantome) {
	return joueur->position.x > fantome->position.x - TAILLE_CASE &&
		joueur->position.x < fantome->position.x + TAILLE_CASE &&
		joueur->position.y > fantome->position.y - TAILLE_CASE &&
		joueur->position.y < fantome->position.y + TAILLE_CASE;
}
