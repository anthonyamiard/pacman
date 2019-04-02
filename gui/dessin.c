/*!
 * \file	dessin.c
 * \author	Anthony Amiard
 * \date	2019
 *
 * Fonctions de base pour afficher des images en SDL.
 *
 */

#define _DESSIN_C_

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "dessin.h"

int init_sprites(SDL_Renderer * rend) {
	int err = 0;
	if((sprites.mur = charge_img("../img/mur.bmp", rend)) == NULL)
		err = 1;
	if((sprites.chemin = charge_img("../img/chemin.bmp", rend)) == NULL)
		err = 1;
	if((sprites.pacgum = charge_img("../img/pacgum.bmp", rend)) == NULL)
		err = 1;
	if((sprites.super_pg = charge_img("../img/super_pg.bmp", rend)) == NULL)
		err = 1;
	if((sprites.boite = charge_img("../img/boite.bmp", rend)) == NULL)
		err = 1;
	if((sprites.entree = charge_img("../img/entree.bmp", rend)) == NULL)
		err = 1;
	if((sprites.autre = charge_img("../img/autre.bmp", rend)) == NULL)
		err = 1;
	if((sprites.fant_b = charge_img("../img/fant_b.bmp", rend)) == NULL)
		err = 1;
	if((sprites.fant_o = charge_img("../img/fant_o.bmp", rend)) == NULL)
		err = 1;
	if((sprites.fant_peur = charge_img("../img/fant_peur.bmp", rend)) == NULL)
		err = 1;
	if((sprites.fant_r = charge_img("../img/fant_r.bmp", rend)) == NULL)
		err = 1;
	if((sprites.fant_p = charge_img("../img/fant_rose.bmp", rend)) == NULL)
		err = 1;
	if((sprites.pac = charge_img("../img/pac.bmp", rend)) == NULL)
		err = 1;
	return err;
}

void detruit_sprites() {
	SDL_DestroyTexture(sprites.mur);
	SDL_DestroyTexture(sprites.chemin);
	SDL_DestroyTexture(sprites.pacgum);
	SDL_DestroyTexture(sprites.super_pg);
	SDL_DestroyTexture(sprites.boite);
	SDL_DestroyTexture(sprites.entree);
	SDL_DestroyTexture(sprites.autre);
	SDL_DestroyTexture(sprites.fant_b);
	SDL_DestroyTexture(sprites.fant_o);
	SDL_DestroyTexture(sprites.fant_peur);
	SDL_DestroyTexture(sprites.fant_r);
	SDL_DestroyTexture(sprites.fant_p);
	SDL_DestroyTexture(sprites.pac);
}


SDL_Texture * charge_img(const char * chemin, SDL_Renderer * rend) {
	SDL_Texture * texture = NULL;
	SDL_Surface * img = SDL_LoadBMP(chemin);
	if(img != NULL) {
		texture = SDL_CreateTextureFromSurface(rend, img);
		SDL_FreeSurface(img);
	}
	return texture;
}

void rend_texture(SDL_Texture * tex, SDL_Renderer * rend, int x, int y) {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &(dest.w), &(dest.h));
	SDL_RenderCopy(rend, tex, NULL, &dest);
}
