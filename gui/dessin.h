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


SDL_Texture * charge_img(const char * chemin, SDL_Renderer * rend);

void rend_texture(SDL_Texture * tex, SDL_Renderer * rend, int x, int y);

#endif
