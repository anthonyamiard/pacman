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
					SDL_Renderer * rend,
					fantome_t * f1,
					fantome_t * f2,
					fantome_t * f3,
					fantome_t * f4) {
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
	} else if(labyrinthe[joueur->coord.y][joueur->coord.x] == 's') {
		labyrinthe[joueur->coord.y][joueur->coord.x] = 'c';
		if(f1->etat == POURSUITE)
			f1->etat = FUITE;
		if(f2->etat == POURSUITE)
			f2->etat = FUITE;
		if(f3->etat == POURSUITE)
			f3->etat = FUITE;
		if(f4->etat == POURSUITE)
			f4->etat = FUITE;
	}
	SDL_RenderCopy(rend, sprites.pac, NULL, &(joueur->position));
}

void deplace_fantome(fantome_t * fantome, char labyrinthe[N_LAB][M_LAB], SDL_Renderer * rend, joueur_t * joueur) {
	coord_t dest;
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
		if(fantome->etat == RETOUR && fantome->coord.x == X_BOITE && fantome->coord.y == Y_BOITE - 1) {
			fantome->coord.y = Y_BOITE;
			fantome->dir = 'b';
		} else if(fantome->etat) {
			if((!est_dans_boite(fantome->coord.x, fantome->coord.y)) && (
				nb_chemins_voisins(labyrinthe, fantome->coord.x,
				fantome->coord.y) > 2 || ((fantome->dir == 'g' &&
				!est_chemin(labyrinthe[fantome->coord.y][fantome->coord.x-1]))
				|| (fantome->dir == 'd' &&
				!est_chemin(labyrinthe[fantome->coord.y][fantome->coord.x+1]))
				|| (fantome->dir == 'h' &&
				!est_chemin(labyrinthe[fantome->coord.y-1][fantome->coord.x]))
				|| (fantome->dir == 'b' &&
				!est_chemin(labyrinthe[fantome->coord.y+1][fantome->coord.x])
				)))) {
				dest = chemin(labyrinthe, &(fantome->coord), &cible);
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
	SDL_Texture * texture;
	if(fantome->etat == FUITE)
		texture = sprites.fant_peur;
	else if(fantome->etat == RETOUR)
		texture = sprites.fant_retour;
	else
		texture = fantome->texture;
	deplace_coord(&(fantome->coord), &(fantome->position), labyrinthe,
				  fantome->dir, 3);
	SDL_RenderCopy(rend, texture, NULL, &(fantome->position));
}

int collision(const joueur_t * joueur, const fantome_t * fantome) {
	return joueur->position.x > fantome->position.x - TAILLE_CASE &&
		joueur->position.x < fantome->position.x + TAILLE_CASE &&
		joueur->position.y > fantome->position.y - TAILLE_CASE &&
		joueur->position.y < fantome->position.y + TAILLE_CASE;
}

void gere_collisions(joueur_t * joueur,
					 fantome_t * fant_b,
					 fantome_t * fant_r,
					 fantome_t * fant_o,
					 fantome_t * fant_p) {
	int col_b = collision(joueur, fant_b);
	int col_r = collision(joueur, fant_r);
	int col_o = collision(joueur, fant_o);
	int col_p = collision(joueur, fant_p);
	if((col_b && fant_b->etat == POURSUITE) ||
		(col_r && fant_r->etat == POURSUITE) ||
		(col_o && fant_o->etat == POURSUITE) ||
		(col_p && fant_p->etat == POURSUITE)) {
		joueur->vies -= 1;
		joueur->nextdir = 0;
		pacdir = 0;
		joueur->position.x = X_DEP * TAILLE_CASE;
		joueur->position.y = Y_DEP * TAILLE_CASE;
		joueur->coord.x = X_DEP;
		joueur->coord.y = Y_DEP;
		fant_b->position.x = X_BLEU * TAILLE_CASE;
		fant_b->position.y = Y_BLEU * TAILLE_CASE;
		fant_b->coord.x = X_BLEU;
		fant_b->coord.y = Y_BLEU;
		fant_b->etat = ATTENTE;
		fant_r->position.x = X_ROUGE * TAILLE_CASE;
		fant_r->position.y = Y_ROUGE * TAILLE_CASE;
		fant_r->coord.x = X_ROUGE;
		fant_r->coord.y = Y_ROUGE;
		fant_r->etat = ATTENTE;
		fant_o->position.x = X_ORANGE * TAILLE_CASE;
		fant_o->position.y = Y_ORANGE * TAILLE_CASE;
		fant_o->coord.x = X_ORANGE;
		fant_o->coord.y = Y_ORANGE;
		fant_o->etat = ATTENTE;
		fant_p->position.x = X_ROSE * TAILLE_CASE;
		fant_p->position.y = Y_ROSE * TAILLE_CASE;
		fant_p->coord.x = X_ROSE;
		fant_p->coord.y = Y_ROSE;
		fant_p->etat = ATTENTE;
	} else if(col_b && fant_b->etat == FUITE) {
		joueur->score += 100;
		fant_b->etat = RETOUR;
	} else if(col_r && fant_r->etat == FUITE) {
		joueur->score += 100;
		fant_r->etat = RETOUR;
	} else if(col_o && fant_o->etat == FUITE) {
		joueur->score += 100;
		fant_o->etat = RETOUR;
	} else if(col_p && fant_p->etat == FUITE) {
		joueur->score += 100;
		fant_p->etat = RETOUR;
	}
}
