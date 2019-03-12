/*
 * Definition des types et des fonctions permettant de manipuler les differents
 * objets
 */

#ifndef _OBJETS_H_
#define _OBJETS_H_

#include "taille_lab.h"



/*
 * TYPES
 */

/* Coordonnees */
typedef struct coord_s {
	int x, y;
} coord_t;

/* Etat des fantomes */
typedef enum etat_e {POURSUITE, FUITE, RETOUR} etat_t;

/* Fruit bonus */
typedef struct fruit_s {
	char * nom;
	int points;
	coord_t * coord;
} fruit_t;

/* Joueur */
typedef struct joueur_s {
	char * nom;
	int vies, score;
	coord_t * coord;
} joueur_t;

/* Fantome */
typedef struct fantome_s {
	char * nom;
	char couleur; /* b = bleu, r = rouge, p = rose, o = orange */
	coord_t (*chemin)(char [N_LAB][M_LAB], coord_t *, coord_t *);
	etat_t etat;
	coord_t * coord;
} fantome_t;



/*
 * FONCTIONS DE CREATION DES OBJETS
 * Renvoient un pointeur sur les objets
 */

/* Coordonnees */
coord_t * cree_coord(int x, int y);

/* Fruit bonus */
fruit_t * cree_fruit(const char * nom, int points, int x, int y);

/* Joueur */
joueur_t * cree_joueur(const char * nom, int x, int y);

/* Fantome */
fantome_t * cree_fantome(const char * nom, char couleur, int x, int y);

/*
 * FONCTIONS DE DESTRUCTION DES OBJETS
 * Renvoient un pointeur sur les objets, mis a NULL si tout se passe bien
 */

/* Coordonnees */
coord_t * detruit_coord(coord_t ** coord);

/* Fruit et bonus */
fruit_t * detruit_fruit(fruit_t ** fruit);

/* Joueur */
joueur_t * detruit_joueur(joueur_t ** joueur);

/* Fantome */
fantome_t * detruit_fantome(fantome_t ** fantome);



#endif
