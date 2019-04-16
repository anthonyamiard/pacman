#include <stdio.h>
#include <stdlib.h>
#include "../include/objets.h"
#include "../include/labyrinthe.h"
#include "../include/IA.h"
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

void deplace_joueur(joueur_t * joueur,
					char labyrinthe[N_LAB][M_LAB],
					int * nb_pacgums,
					SDL_Renderer * rend,
					fantome_t * f1,
					fantome_t * f2,
					fantome_t * f3,
					fantome_t * f4,
					int fps,
					int pause) {
	fantome_t * f[] = {f1, f2, f3, f4};
	int i;
	if(!pause) {
		if(joueur->position.x % TAILLE_CASE == 0 &&
			joueur->position.y % TAILLE_CASE == 0) {
			joueur->coord.x = joueur->position.x / TAILLE_CASE;
			joueur->coord.y = joueur->position.y / TAILLE_CASE;
			pacdir = joueur->nextdir;
		}
		deplace_coord(&(joueur->coord), &(joueur->position), labyrinthe, pacdir,
					  3);
		if(labyrinthe[joueur->coord.y][joueur->coord.x] == 'p') {
			joueur->score += 1;
			*nb_pacgums -= 1;
			labyrinthe[joueur->coord.y][joueur->coord.x] = 'c';
		} else if(labyrinthe[joueur->coord.y][joueur->coord.x] == 's') {
			labyrinthe[joueur->coord.y][joueur->coord.x] = 'c';
			for(i = 0; i < 4; i++) {
				if(f[i]->etat == POURSUITE || f[i]->etat == FUITE) {
					f[i]->etat = FUITE;
					f[i]->duree = 30 * fps;
				}
			}
		}
	}
	double angle;
	switch(pacdir) {
		case 'g': angle = 180; break;
		case 'd': angle = 0; break;
		case 'h': angle = 270; break;
		case 'b': angle = 90; break;
		default: angle = 0;
	}
	SDL_RenderCopyEx(rend, sprites.pac, NULL, &(joueur->position), angle, NULL, SDL_FLIP_NONE);
}

void deplace_fantome(fantome_t * fantome,
					 char labyrinthe[N_LAB][M_LAB],
					 SDL_Renderer * rend,
					 joueur_t * joueur,
					 int fps,
					 int pause) {
	coord_t dest;
	if(!pause) {
		fantome->duree -= 1;
		if(fantome->etat == FUITE && fantome->duree == 0)
			fantome->etat = POURSUITE;
		if(fantome->position.x % TAILLE_CASE == 0 &&
			fantome->position.y % TAILLE_CASE == 0) {
			fantome->coord.x = fantome->position.x / TAILLE_CASE;
			fantome->coord.y = fantome->position.y / TAILLE_CASE;
			coord_t (*chemin)(char [N_LAB][M_LAB], coord_t *, coord_t *);
			if(fantome->etat == FUITE)
				chemin = chemin_fuir;
			else if(fantome->etat == RETOUR)
				chemin = chemin_court;
			else
				chemin = fantome->chemin;
			coord_t cible;
			if(fantome->etat == RETOUR) {
				cible.x = X_BOITE;
				cible.y = Y_BOITE - 1;	
			} else {
				cible.x = joueur->coord.x;
				cible.y = joueur->coord.y;
			}
			if(fantome->etat == RETOUR && fantome->coord.x == X_BOITE &&
				fantome->coord.y == Y_BOITE - 1) {
				fantome->coord.y = Y_BOITE;
				fantome->dir = 'b';
			} else if(fantome->etat) {
				if((!est_dans_boite(fantome->coord.x, fantome->coord.y)) && (
					nb_chemins_voisins(labyrinthe, fantome->coord.x,
					fantome->coord.y) > 2 || (
						(
							fantome->dir == 'g' &&
							!est_chemin(
								labyrinthe[fantome->coord.y][fantome->coord.x-1]
							)
						) || (
							fantome->dir == 'd' &&
							!est_chemin(
								labyrinthe[fantome->coord.y][fantome->coord.x+1]
							)
						) || (
							fantome->dir == 'h' &&
							!est_chemin(
								labyrinthe[fantome->coord.y-1][fantome->coord.x]
							)
						) || (
							fantome->dir == 'b' &&
							!est_chemin(
								labyrinthe[fantome->coord.y+1][fantome->coord.x]
							)
						)
					))) {
					dest = chemin(labyrinthe, &(fantome->coord), &cible);
					if(dest.x == fantome->coord.x && dest.y == fantome->coord.y)
						dest = chemin_aleatoire(labyrinthe, &(fantome->coord),
												&cible);
					if(dest.x - fantome->coord.x < 0)
						fantome->dir = 'g';
					else if(dest.x - fantome->coord.x > 0)
						fantome->dir = 'd';
					else if(dest.y - fantome->coord.y < 0)
						fantome->dir = 'h';
					else
						fantome->dir = 'b';
				} else if(est_dans_boite(fantome->coord.x, fantome->coord.y)) {
					if(fantome->etat == POURSUITE) {
						if(fantome->coord.x < X_BOITE)
							fantome->dir = 'd';
						else if(fantome->coord.x > X_BOITE + 1)
							fantome->dir = 'g';
						else
							fantome->dir = 'h';
					} else if(fantome->etat == RETOUR) {
						if(fantome->coord.y < fantome->coord_dep.y)
							fantome->dir = 'b';
						else if(fantome->coord.x < fantome->coord_dep.x)
							fantome->dir = 'd';
						else if(fantome->coord.x > fantome->coord_dep.x)
							fantome->dir = 'g';
						else {
							fantome->dir = 0;
							fantome->etat = POURSUITE;
						}
					}
				}
			} else if(fantome->etat == ATTENTE) {
				if(fantome->coord.y == Y_BLEU - 1)
					fantome->dir = 'b';
				else if(fantome->coord.y == Y_BLEU + 1)
					fantome->dir = 'h';
				if(fantome->dir != 'h' && fantome->dir != 'b') {
					if(fantome->coord_dep.x % 2)
						fantome->dir = 'b';
					else
						fantome->dir = 'h';
				}
			}
		}
	}
	SDL_Texture * texture;
	if(fantome->etat == FUITE &&
		(fantome->duree > 10 * fps || (fantome->duree / (fps / 2)) % 2))
		texture = sprites.fant_peur;
	else if(fantome->etat == RETOUR)
		texture = sprites.fant_retour;
	else
		texture = fantome->texture;
	if(!pause)
		deplace_coord(&(fantome->coord), &(fantome->position), labyrinthe,
					fantome->dir, 3);
	SDL_RenderCopy(rend, texture, NULL, &(fantome->position));
}

void init_place(joueur_t * joueur,
				fantome_t * f1,
				fantome_t * f2,
				fantome_t * f3,
				fantome_t * f4) {
	fantome_t * f[] = {f1, f2, f3, f4};
	int i;
	joueur->nextdir = 0;
	pacdir = 0;
	joueur->position.x = X_DEP * TAILLE_CASE;
	joueur->position.y = Y_DEP * TAILLE_CASE;
	joueur->coord.x = X_DEP;
	joueur->coord.y = Y_DEP;
	for(i = 0; i < 4; i++) {
		f[i]->position.x = f[i]->coord_dep.x * TAILLE_CASE;
		f[i]->position.y = f[i]->coord_dep.y * TAILLE_CASE;
		f[i]->coord.x = f[i]->coord_dep.x;
		f[i]->coord.y = f[i]->coord_dep.y;
		f[i]->etat = ATTENTE;
		f[i]->dir = 0;
	}
}

int collision(const joueur_t * joueur, const fantome_t * fantome) {
	return joueur->position.x > fantome->position.x - TAILLE_CASE / 2 &&
		joueur->position.x < fantome->position.x + TAILLE_CASE / 2 &&
		joueur->position.y > fantome->position.y - TAILLE_CASE / 2 &&
		joueur->position.y < fantome->position.y + TAILLE_CASE / 2;
}

void gere_collisions(joueur_t * joueur,
					 fantome_t * f1,
					 fantome_t * f2,
					 fantome_t * f3,
					 fantome_t * f4,
					 long * timer,
					 int fps) {
	fantome_t * f[] = {f1, f2, f3, f4};
	int i, arret = 0;
	for(i = 0; i < 4 && !arret; i++) {
		if(collision(joueur, f[i])) {
			if(f[i]->etat == POURSUITE) {
				arret = 1;
				if(*timer < 0) {
					joueur->vies -= 1;
					*timer = 2 * fps;
				} else if(*timer == 0) {
					init_place(joueur, f1, f2, f3, f4);
				}
			} else if(f[i]->etat == FUITE) {
				joueur->score += 100;
				f[i]->etat = RETOUR;
			}
		}
	}
}
