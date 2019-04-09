/*!
 * \file	dessin.h
 * \author	Anthony Amiard
 * \date	2019
 *
 * Fonctions de base pour afficher des images en SDL.
 *
 */

#ifndef _DESSIN_H_
#define _DESSIN_H_

#include <SDL2/SDL.h>



/*
 * TYPES
 */



/*!
 * \brief	Ensemble des sprites utilisés
 * 
 * Ensemble des sprites utilisés dans le jeu.
 * 
 */
struct sprites_s {
	SDL_Texture * mur;			/*!< Mur */
	SDL_Texture * chemin;		/*!< Chemin vide */
	SDL_Texture * pacgum;		/*!< Pacgum */
	SDL_Texture * super_pg;		/*!< Super pacgum */
	SDL_Texture * boite;		/*!< Boîte des fantômes */
	SDL_Texture * entree;		/*!< Entrée de la boîte */
	SDL_Texture * autre;		/*!< Élément inconnu (points d'interrogation) */
	SDL_Texture * fant_b;		/*!< Fantôme bleu */
	SDL_Texture * fant_o;		/*!< Fantôme orange */
	SDL_Texture * fant_peur;	/*!< Fantôme apeuré */
	SDL_Texture * fant_r;		/*!< Fantôme rouge */
	SDL_Texture * fant_p;		/*!< Fantôme rose */
	SDL_Texture * fant_retour;	/*!< Yeux du fantôme seuls */
	SDL_Texture * pac;			/*!< Pacman */
};



/*
 * FONCTIONS
 */


/*!
 * \brief	Initialisation de la liste des sprites
 * \retval	0	Initialisation de tous les sprites
 * \retval	1	Certains sprites n'ont pas pu être chargés
 */
int init_sprites();

/*!
 * \brief	Destruction de la liste des sprites
 */
void detruit_sprites();

SDL_Texture * charge_img(const char * chemin, SDL_Renderer * rend);

void rend_texture(SDL_Texture * tex, SDL_Renderer * rend, int x, int y);

#ifdef _DESSIN_C_
struct sprites_s sprites;
#else
extern struct sprites_s sprites;
#endif

#endif
