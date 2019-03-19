/*!
 * \file	objets.c
 * \author	Anthony Amiard
 * \date	2019
 * 
 * Fonctions permettant de créer et détruire les différents objets définis dans
 * \ref objets.h.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/objets.h"

/*
 * Fonctions de création des objets
 */

coord_t * cree_coord(int x, int y) {
	coord_t * coord = malloc(sizeof(coord_t));
	if(coord != NULL) {
		coord->x = x;
		coord->y = y;
	}
	return coord;
}

fruit_t * cree_fruit(const char * nom, int points, int x, int y) {
	fruit_t * fruit = malloc(sizeof(fruit_t));
	if(fruit != NULL) {
		strncpy(fruit->nom, nom, TAILLE_NOM);
		fruit->points = points;
		fruit->coord = cree_coord(x, y);
		if(fruit->coord == NULL) {
			free(fruit);
			fruit = NULL;
		}
	}
	return fruit;
}

joueur_t * cree_joueur(const char * nom, int vies, int score, int x, int y) {
	joueur_t * joueur = malloc(sizeof(joueur_t));
	if(joueur != NULL) {
		strncpy(joueur->nom, nom, TAILLE_NOM);
		joueur->vies = vies;
		joueur->score = score;
		joueur->coord = cree_coord(x, y);
		if(joueur->coord == NULL) {
			free(joueur);
			joueur = NULL;
		}
	}
	return joueur;
}

fantome_t * cree_fantome(const char * nom,
						 char couleur,
						 coord_t (*chemin)(char [N_LAB][M_LAB],
										   coord_t *,
										   coord_t *),
						 int x,
						 int y) {
	fantome_t * fantome = malloc(sizeof(fantome_t));
	if(fantome != NULL) {
		strncpy(fantome->nom, nom, TAILLE_NOM);
		fantome->couleur = couleur;
		fantome->chemin = chemin;
		fantome->etat = POURSUITE;
		fantome->coord = cree_coord(x, y);
		if(fantome->coord == NULL) {
			free(fantome);
			fantome = NULL;
		}
	}
	return fantome;
}

/*
 * Fonctions de destruction des objets
 */

int detruit_coord(coord_t ** adr) {
	free(*adr);
	*adr = NULL;
	return 0;
}

int detruit_fruit(fruit_t ** adr) {
	if(*adr != NULL)
		detruit_coord(&((*adr)->coord));
	free(*adr);
	*adr = NULL;
	return 0;
}

int detruit_joueur(joueur_t ** adr) {
	if(*adr != NULL)
		detruit_coord(&((*adr)->coord));
	free(*adr);
	*adr = NULL;
	return 0;
}

int detruit_fantome(fantome_t ** adr) {
	if(*adr != NULL)
		detruit_coord(&((*adr)->coord));
	free(*adr);
	*adr = NULL;
	return 0;
}
