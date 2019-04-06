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



struct sprites_s {
	SDL_Texture * mur;
	SDL_Texture * chemin;
	SDL_Texture * pacgum;
	SDL_Texture * super_pg;
	SDL_Texture * boite;
	SDL_Texture * entree;
	SDL_Texture * autre;
	SDL_Texture * fant_b;
	SDL_Texture * fant_o;
	SDL_Texture * fant_peur;
	SDL_Texture * fant_r;
	SDL_Texture * fant_p;
	SDL_Texture * fant_retour;
	SDL_Texture * pac;
};

int init_sprites();

void detruit_sprites();

SDL_Texture * charge_img(const char * chemin, SDL_Renderer * rend);

void rend_texture(SDL_Texture * tex, SDL_Renderer * rend, int x, int y);

#ifdef _DESSIN_C_
struct sprites_s sprites;
#else
extern struct sprites_s sprites;
#endif

#endif
