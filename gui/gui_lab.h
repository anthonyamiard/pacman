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

int case_img(char case_lab, SDL_Renderer * renderer, int x, int y);

int dessine_lab(const char labyrinthe[N_LAB][M_LAB], SDL_Renderer * rend);

#endif
