/*!
 * \file	objets.h
 * \author	Hugo Bigan, Taliesin Ambroise
 * \date	2019
 *
 * Definition des types et des fonctions permettant de manipuler les differents
 * objets
 *
 */

#ifndef _OBJETS_H_
#define _OBJETS_H_

#include "taille_lab.h"



/*
 * TYPES
 */

/*!
 * \struct	coord_s
 * \brief	Coordonnées
 */
typedef struct coord_s {
	int x;	/*!< Coordonnée horizontale */
	int y;	/*!< Coordonnée verticale */
} coord_t;

/*!
 * \enum	etat_e
 * \brief	État des fantomes
 */
typedef enum etat_e {
	POURSUITE,	/*!< Le fantôme suit son comportement */
	FUITE,		/*!< Le fantôme fuit Pacman (prise de super-pacgum) */
	RETOUR		/*!< Le fantôme, mangé, retourne au point de départ */
} etat_t;

/*!
 * \struct	fruit_s
 * \brief	Fruit bonus
 */
typedef struct fruit_s {
	char * nom;			/*!< Nom du fruit */
	int points;			/*!< Nombre de points qu'il procure */
	coord_t * coord;	/*!< Coordonnées du fruit */
} fruit_t;

/*!
 * \struct	joueur_s
 * \brief	Joueur
 */
typedef struct joueur_s {
	char * nom;			/*!< Nom du joueur */
	int vies;			/*!< Nombre de vies */
	int score;			/*!< Score du joueur */
	coord_t * coord;	/*!< Coordonnée du joueur à l'instant t */
} joueur_t;

/*!
 * \struct	fantome_s
 * \brief	Fantôme
 */
typedef struct fantome_s {
	char * nom;			/*!< Nom du fantôme */
	char couleur; 		/*!< Couleur du fantôme
						 * \li \c 'b' : bleu
						 * \li \c 'r' : rouge
						 * \li \c 'p' : rose
						 * \li \c 'o' : orange
						 */
	coord_t (*chemin)(char [N_LAB][M_LAB], coord_t *, coord_t *); /*!<
		* \brief	Recherche de chemin du fantôme
		*
		* Fonction de recherche de chemin du fantôme en fonction de son
		* comportement.
		*
		*/
	etat_t etat;		/*!< État du fantôme */
	coord_t * coord;	/*!< Coordonnées du fantôme à l'instant t */
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
