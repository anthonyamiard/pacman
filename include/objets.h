/*!
 * \file	objets.h
 * \author	Hugo Bigan
 * \author	Taliesin Ambroise
 * \author	Anthony Amiard
 * \date	2019
 *
 * Definition des types et des fonctions permettant de manipuler les differents
 * objets
 *
 */

#ifndef _OBJETS_H_
#define _OBJETS_H_

#include <SDL2/SDL.h>
#include "taille_lab.h"

/*! Taille maximale des chaînes de caractères noms */
#define TAILLE_NOM 20



/*
 * TYPES
 */

/*!
 * \brief	Couple de coordonnées \c x et \c y
 */
typedef struct coord_s {
	int x;	/*!< Coordonnée horizontale */
	int y;	/*!< Coordonnée verticale */
} coord_t;

/*!
 * \brief	État des fantomes
 */
typedef enum etat_e {
	ATTENTE,	/*!< Le fantôme attent dans la boîte */
	POURSUITE,	/*!< Le fantôme suit son comportement */
	FUITE,		/*!< Le fantôme fuit Pacman (prise de super-pacgum) */
	RETOUR		/*!< Le fantôme, mangé, retourne au point de départ */
} etat_t;

/*!
 * \brief	Fruit bonus
 */
typedef struct fruit_s {
	int points;				/*!< Nombre de points qu'il procure */
	coord_t coord;		/*!< Coordonnées du fruit */
} fruit_t;

/*!
 * \brief	Joueur
 */
typedef struct joueur_s {
	int vies;				/*!< Nombre de vies */
	int score;				/*!< Score du joueur */
	coord_t coord;		/*!< Coordonnée du joueur à l'instant t */
	SDL_Rect position;
	char nextdir;
} joueur_t;

/*!
 * \brief	Fantôme
 */
typedef struct fantome_s {
	/*! Couleur du fantôme 
	 * \li \c 'b' : bleu
	 * \li \c 'r' : rouge
	 * \li \c 'p' : rose
	 * \li \c 'o' : orange
	 */
	char couleur;
	SDL_Texture * texture;
	/*! Recherche de chemin du fantôme */
	coord_t (*chemin)(char [N_LAB][M_LAB], coord_t *, coord_t *);
	etat_t etat;		/*!< État du fantôme */
	coord_t coord;		/*!< Coordonnées du fantôme à l'instant présent */
	coord_t coord_dep;
	SDL_Rect position;
	char dir;
	int duree;
} fantome_t;



/*!
 * \name	Fonctions de création des objets
 * @{
 * \returns		Pointeur sur l'objet créé
 * \retval		NULL	L'objet n'a pas pu être créé
 */

/*!
 * \brief		Création de coordonnées
 * \param[in]	x, y	Coordonnées à écrire dans l'objet
 */
coord_t * cree_coord(int x, int y);

/*!
 * \brief		Création de fruit bonus 
 * \param[in]	nom		Nom du fruit, ne doit pas dépasser \c TAILLE_NOM
 * \param[in]	points	Nombre de points procurés par le bonus
 * \param[in]	x, y	Coordonnées d'apparition du bonus
 */
fruit_t * cree_fruit(int points, int x, int y);

/*!
 * \brief		Création du joueur
 * \param[in]	nom		Nom du joueur, ne doit pas dépasser \c TAILLE_NOM
 * \param[in]	vies	Nombre de vies de départ
 * \param[in]	score	Score de départ
 * \param[in]	x, y	Coordonnées de départ du joueur
 */
joueur_t * cree_joueur(SDL_Renderer * rend, int vies, int score, int x, int y);

/*!
 * \brief		Création de fantôme
 * \param[in]	nom		Nom du fantôme
 * \param[in]	couleur	Couleur du fantôme. Voir \ref fantome_s::couleur
 * \param[in]	chemin	Fonction de recherche de chemin adaptée au comportement
 * 						du fantôme
 * \param[in]	x, y	Coordonnées d’apparition du fantôme
 */
fantome_t * cree_fantome(SDL_Renderer * rend, 
						 char couleur,
						 coord_t (*chemin)(char [N_LAB][M_LAB],
										   coord_t *,
										   coord_t *),
						 int x,
						 int y);

/*!
 * @}
 * \name	Fonctions de destruction des objets
 * @{
 * \brief			Supprime les objets et met leur adresse à \c NULL.
 * \param[in,out]	adr		Adresse du pointeur de l'objet
 * \retval			0		L'objet a été détruit
 */

/* Coordonnees */
int detruit_coord(coord_t ** adr);

/* Fruit et bonus */
int detruit_fruit(fruit_t ** adr);

/* Joueur */
int detruit_joueur(joueur_t ** adr);

/* Fantome */
int detruit_fantome(fantome_t ** adr);

/*!
 * @}
 */

/*
 * VARIABLES GLOBALES
 */

#ifdef _MAIN_C_
char pacdir;
#else
extern char pacdir;
#endif



#endif
