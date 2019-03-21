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
#include <time.h>

#include "../include/taille_lab.h"
#include "../gui/gui_lab.h"
#include "../include/labyrinthe.h"

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
	srand(time(NULL));
	if(SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "Échec d'ouverture de la SDL (%s).\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Window * fenetre = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED,
													  SDL_WINDOWPOS_UNDEFINED,
													  M_LAB * TAILLE_CASE,
													  N_LAB * TAILLE_CASE,
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

	SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
	SDL_RenderClear(rend);

	char labyrinthe[N_LAB][M_LAB];
	int nb_pacgums;
	do {
		genere_lab(labyrinthe, &nb_pacgums);
	} while(nb_pacgums < 250 || nb_pacgums > 350);

	if(dessine_lab(labyrinthe, rend)) {
		fprintf(stderr, "Échec de génération du labyrinthe (%s).\n", SDL_GetError());
	}

	SDL_RenderPresent(rend);

	pause();
	SDL_DestroyWindow(fenetre);
	SDL_Quit();
	return 0;
}
