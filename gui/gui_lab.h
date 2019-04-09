/*!
 * \file	gui_lab.h
 * \auhor	Anthony Amiard
 * \date	2019
 *
 * Définitions des fonctions qui permettent d'afficher le labyrinthe en SDL.
 *
 */

#ifndef _GUI_LAB_H_
#define _GUI_LAB_H_

#include <SDL2/SDL.h>
#include "../include/taille_lab.h"

#define TAILLE_CASE 24

/*!
 * \brief			Affiche une case du labyrinthe sur le renderer aux
 * 					coodonnées doonnées
 * \param[in]		case_lab		Case du labyrinthe à afficher
 * \param[in,out]	renderer		Renderer
 * \param[in]		x, y			Coordonnée de la case à afficher
 * \retval			EXIT_SUCCESS	Aucune erreur
 * \retval			EXIT_FAILURE	L'image n'a pas pu être chargée
 */
int case_img(char case_lab, SDL_Renderer * renderer, int x, int y);

/*!
 * \brief			Affiche le labyrinthe sur le renderer
 * \param[in]		labyrinthe		Labyrinthe à afficher
 * \param[in,out]	rend			Renderer sur lequel afficher le labyrinthe
 * \retval			EXIT_SUCCESS	Aucune erreur
 * \retval			EXIT_SUCCESS	Une image n'a pas pu être chargée
 */
int dessine_lab(const char labyrinthe[N_LAB][M_LAB], SDL_Renderer * rend);

/*!
 * \brief			Détruit l'affichage du labyrinthe
 * \param[in,out]	rend	Renderer sur lequel est affiché le labyrinthe
 */
void detruit_lab(SDL_Renderer * rend);

#endif
