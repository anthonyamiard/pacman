/*!
 * \file	main.c
 * \author	Anthony Amiard
 * \date	2019
 *
 * Fichier contenant la fonction main.
 *
 */

#define _MAIN_C_

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

#include "../include/taille_lab.h"
#include "../gui/gui_lab.h"
#include "../include/labyrinthe.h"
#include "../include/objets.h"

#define TAILLE_CASE 24

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

	SDL_Rect position;

	SDL_Surface * image = SDL_LoadBMP("../img/autre.bmp");
	if(!image) {
		fprintf(stderr, "Erreur de chargement de l'image : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Renderer * rend = SDL_CreateRenderer(fenetre, -1,
											 SDL_RENDERER_ACCELERATED);
	if(rend == NULL) {
		fprintf(stderr, "Échec de création du renderer (%s).\n",
				SDL_GetError());
		SDL_DestroyWindow(fenetre);
		return EXIT_FAILURE;
	}

	SDL_Texture * image_tex = SDL_CreateTextureFromSurface(rend, image);
	SDL_FreeSurface(image);

	SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
	SDL_RenderClear(rend);

	char labyrinthe[N_LAB][M_LAB];
	int nb_pacgums;
	do {
		genere_lab(labyrinthe, &nb_pacgums);
	} while(nb_pacgums < 280 || nb_pacgums > 350);

	if(dessine_lab(labyrinthe, rend)) {
		fprintf(stderr, "Échec de génération du labyrinthe (%s).\n",
				SDL_GetError());
	}

	printf("Nombre pacgums : %d\n", nb_pacgums);

	SDL_RenderPresent(rend);

	if(fenetre) {
		int continuer = 1;
		while(continuer) {
			SDL_Event e;
			while(SDL_PollEvent(&e)) {
				switch(e.type) {
					case SDL_QUIT: continuer = 0; break;
					case SDL_WINDOWEVENT:
						switch(e.window.event) {
							case SDL_WINDOWEVENT_EXPOSED:
							case SDL_WINDOWEVENT_SIZE_CHANGED:
							case SDL_WINDOWEVENT_RESIZED:
							case SDL_WINDOWEVENT_SHOWN:
								position.x = X_DEP * TAILLE_CASE;
								position.y = Y_DEP * TAILLE_CASE;
								SDL_QueryTexture(image_tex, NULL, NULL, &(position.w), &(position.h));
								SDL_RenderCopy(rend, image_tex, NULL, &position);
								SDL_RenderPresent(rend);
								break;
						}

						break;
					case SDL_KEYDOWN:
						switch(e.key.keysym.sym) {
							case SDLK_UP:
								position.y -= TAILLE_CASE;
								break;
							case SDLK_DOWN:
								position.y += TAILLE_CASE;
								break;
							case SDLK_RIGHT:
								position.x += TAILLE_CASE;
								break;
							case SDLK_LEFT:
								position.x -= TAILLE_CASE;
								break;
						}
						
						SDL_RenderClear(rend);
						if(dessine_lab(labyrinthe, rend)) {
							fprintf(stderr, "Échec d'affichage du labyrinthe (%s).\n",
									SDL_GetError());
						}
						SDL_RenderCopy(rend, image_tex, NULL, &position);
						SDL_RenderPresent(rend);
						break;
				}
			}
		}
	}

	SDL_DestroyWindow(fenetre);
	SDL_Quit();
	return 0;
}
