/*!
 * \file	dessin.c
 * \author	Anthony Amiard
 * \date	2019
 *
 * Fonctions de base pour afficher des images en SDL.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "dessin.h"

SDL_Texture * charge_img(const char * chemin, SDL_Renderer * rend) {
	SDL_Texture * texture = NULL;
	SDL_Surface * img = SDL_LoadBMP(chemin);
	if(img != NULL) {
		texture = SDL_CreateTextureFromSurface(rend, img);
		SDL_FreeSurface(img);
	}
	return texture;
}
