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
#include <SDL2/SDL_ttf.h>



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

/*!
 * \brief		Crée une texture à partir d'une image
 * \param[in]	chemin	Chemin de l'image sur le disque
 * \param[in]	rend	Renderer
 * \returns		Texture de l'image
 * \retval		NULL	L'image n'a pas pu être chargée
 */
SDL_Texture * charge_img(const char * chemin, SDL_Renderer * rend);

/*!
 * \brief			Dessine une texture sur le renderer
 * 
 * Dessine la texture \c tex sur le renderer \c rend aux coordonnées \c x et
 * \c y.
 * 
 * \param[in]		tex		Texture à dessiner
 * \param[in,out]	rend	Renderer sur lequel dessiner la texture
 * \param[in]		x, y	Coordonnées
 */
void rend_texture(SDL_Texture * tex, SDL_Renderer * rend, int x, int y);

/*!
 * \brief		Crée une texture à partir de texte
 * \param[in]	police			Police d'écriture
 * \param[in]	texte			Texte à écrire
 * \param[in]	couleur			Couleur du texte
 * \param[in]	fond			Couleur de fond
 * \param[in]	transparence	Vrai si le fond est transparent, faux s'il est
 * 								de la couleur indiquée
 * \param[in]	rend			Renderer
 * \returns		Texture du texte
 * \retval		NULL			Erreur à la création du texte
 */
SDL_Texture * cree_texte(TTF_Font * police,
						 const char * texte,
						 SDL_Color couleur,
						 SDL_Color fond,
						 int transparence,
						 SDL_Renderer * rend);

#ifdef _DESSIN_C_
struct sprites_s sprites;
#else
extern struct sprites_s sprites;
#endif

#endif
