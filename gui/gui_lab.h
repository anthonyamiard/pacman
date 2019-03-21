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

#include <SDL/SDL2.h>
#include "../include/taille_lab.h"

#define TAILLE_CASE 24

SDL_Texture * case_texture(char case_lab, SDL_Renderer * renderer);

#endif
