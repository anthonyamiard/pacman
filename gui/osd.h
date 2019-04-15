/*!
 * \file	osd.h
 * \author	Anthony Amiard
 * 
 * Affichage du score et du nombre de vies en bas de la fenêtre, et de messages
 * au milieu du labyrinthe.
 * 
 */

#ifndef _OSD_H_
#define _OSD_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../include/objets.h"


/*!
 * \brief		Affiche le score, le nombre de vies et le niveau en bas de
 *				l'écran
 * \param[in]	rend	Renderer
 * \param[in]	police	Police d'écriture
 * \param[in]	joueur	Structure joueur
 * \param[in]	niveau	Numéro du niveau
 */
void score_osd(SDL_Renderer * rend,
			   TTF_Font * police,
			   const joueur_t * joueur,
			   int niveau);


#endif
