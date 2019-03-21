/*!
 * \file	gui_lab.c
 * \author	Anthony Amiard
 * \date	2019
 *
 * Fonctions qui permettent d'afficher le labyrinthe en SDL.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "gui_lab.h"

SDL_Texture * case_texture(char case_lab, SDL_Renderer * renderer) {
	SDL_Texture * texture = NULL;
	SDL_Surface * img = NULL;
	switch(case_lab) {
		case 'm': img = SDL_LoadBMP("../img/mur.bmp");
		case 'c': img = SDL_LoadBMP("../img/chemin.bmp");
		case 'p': img = SDL_LoadBMP("../img/pacgum.bmp");
		case 's': img = SDL_LoadBMP("../img/super_pg.bmp");
		case 'b': img = SDL_LoadBMP("../img/boite.bmp");
		case 'e': img = SDL_LoadBMP("../img/entree.bmp");
		default: img = SDL_LoadBMP("../img/autre.bmp");
	}
	if(img != NULL) {
		texture = SDL_CreateTextureFromSurface(renderer, img);
		SDL_FreeSurface(img);
	}
	return texture;
}

#include "gui_lab.h"
