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

#include "dessin.h"
#include "gui_lab.h"

int case_img(char case_lab, SDL_Renderer * renderer, int x, int y) {
	SDL_Texture * img = NULL;
	switch(case_lab) {
		case 'm': img = sprites.mur; break;
		case 'c': img = sprites.chemin; break;
		case 'p': img = sprites.pacgum; break;
		case 's': img = sprites.super_pg; break;
		case 'b': img = sprites.boite; break;
		case 'e': img = sprites.entree; break;
		default: img = sprites.autre; break;
	}
	if(img == NULL) {
		return EXIT_FAILURE;
	}
	rend_texture(img, renderer, x, y);
	return 0;
}

int dessine_lab(const char labyrinthe[N_LAB][M_LAB], SDL_Renderer * rend) {
	int i, j;
	for(i = 0; i < N_LAB; i++) {
		for(j = 0; j < M_LAB; j++) {
			if(case_img(labyrinthe[i][j], rend, j * TAILLE_CASE,
						i * TAILLE_CASE)) {
				return EXIT_FAILURE;
			}
		}
	}
	return EXIT_SUCCESS;
}

void detruit_lab(SDL_Renderer * rend) {
	SDL_DestroyRenderer(rend);
}
