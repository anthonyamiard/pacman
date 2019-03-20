/*!
 * \file	main.c
 * \author	Anthony Amiard
 * \date	2019
 *
 * Fichier contenant la fonction main.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../include/taille_lab.h"

#define TAILLE_CASE 24

void pause() {
	int continuer = 1;
	SDL_Event event;

	while(continuer) {
		SDL_WaitEvent(&event);
		switch(event.type) {
			case SDL_QUIT: continuer = 0; break;
		}
	}
}

int main() {
	if(SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "Échec d'ouverture de la SDL (%s).\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Window * fenetre = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED,
													  SDL_WINDOWPOS_UNDEFINED,
													  N_LAB * TAILLE_CASE,
													  M_LAB * TAILLE_CASE,
													  SDL_WINDOW_SHOWN);
	if(fenetre == NULL) {
		fprintf(stderr, "Échec de création de la fenêtre (%s).\n",
				SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Renderer * rend = SDL_CreateRenderer(fenetre, -1,
											 SDL_RENDERER_ACCELERATED);
	if(rend == NULL) {
		fprintf(stderr, "Échec de création du renderer (%s).\n",
				SDL_GetError());
		SDL_DestroyWindow(fenetre);
		return EXIT_FAILURE;
	}

	SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
	SDL_RenderClear(rend);

	SDL_RenderPresent(rend);

	pause();
	SDL_DestroyWindow(fenetre);
	SDL_Quit();
	return 0;
}
