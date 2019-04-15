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
#include "../gui/dessin.h"
#include "../gui/gui_lab.h"
#include "../include/labyrinthe.h"
#include "../include/objets.h"
#include "../include/IA.h"
#include "../gui/mouv.h"
#include "../gui/surface.h"
#include "../gui/osd.h"



int main() {
	srand(time(NULL));

	if(SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "Échec d'ouverture de la SDL (%s).\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	
	if(TTF_Init()) {
		fprintf(stderr, "Échec d'ouverture de TTF (%s).\n", TTF_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}
	
	TTF_Font * police_menu = TTF_OpenFont("../gui/PoliceMenu.ttf", 32);
	if(police_menu == NULL)
		fprintf(stderr, "Échec d'ouverture de la police (%s).\n",
				TTF_GetError());

//	menu_SDL();

	SDL_Window * fenetre = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED,
													  SDL_WINDOWPOS_UNDEFINED,
													  W_FEN,
													  H_FEN,
													  SDL_WINDOW_SHOWN);
	if(fenetre == NULL) {
		fprintf(stderr, "Échec de création de la fenêtre (%s).\n",
				SDL_GetError());
		TTF_CloseFont(police_menu);
		TTF_Quit();
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_Renderer * rend = SDL_CreateRenderer(fenetre, -1,
											 SDL_RENDERER_ACCELERATED);
	if(rend == NULL) {
		fprintf(stderr, "Échec de création du renderer (%s).\n",
				SDL_GetError());
		SDL_DestroyWindow(fenetre);
		TTF_CloseFont(police_menu);
		TTF_Quit();
		SDL_Quit();
		return EXIT_FAILURE;
	}

	init_sprites(rend);

	char labyrinthe[N_LAB][M_LAB];
	int nb_pacgums;
	int niveau = 1;
	do {
		genere_lab(labyrinthe, &nb_pacgums);
	} while(nb_pacgums < 280 || nb_pacgums > 350);

	if(dessine_lab(labyrinthe, rend)) {
		fprintf(stderr, "Échec de l'affichage du labyrinthe (%s).\n",
				SDL_GetError());
	}

	joueur_t * pacman = cree_joueur(rend, 3, 0, X_DEP, Y_DEP);

	fantome_t * fant_b = cree_fantome(rend, 'b', chemin_fuir, X_BLEU, Y_BLEU);
	fantome_t * fant_o = cree_fantome(rend, 'o', chemin_aleatoire, X_ORANGE,
									  Y_ORANGE);
	fantome_t * fant_r = cree_fantome(rend, 'r', chemin_court, X_ROUGE, Y_ROUGE);
	fantome_t * fant_p = cree_fantome(rend, 'p', chemin_anticipe, X_ROSE,
										Y_ROSE);

	SDL_RenderPresent(rend);

	uint32_t start_time = 0;
	uint32_t end_time = 0;
	uint32_t delta = 0;
	short fps = 30;
	short mspf = 1000/fps;

	if(fenetre) {
		int continuer = 1;
		while(continuer) {
			if(!start_time)
				start_time = SDL_GetTicks();
			else
				delta = end_time - start_time;
			SDL_Event e;
			while(SDL_PollEvent(&e)) {
				switch(e.type) {
					case SDL_QUIT: continuer = 0; break;
					case SDL_WINDOWEVENT:/*
						switch(e.window.event) {
							case SDL_WINDOWEVENT_EXPOSED:
							case SDL_WINDOWEVENT_SIZE_CHANGED:
							case SDL_WINDOWEVENT_RESIZED:
							case SDL_WINDOWEVENT_SHOWN:
								SDL_RenderPresent(rend);
								break;
						}
*/
						break;
					case SDL_KEYDOWN:
						if(fant_b->etat == ATTENTE)
							fant_b->etat = POURSUITE;
						if(fant_r->etat == ATTENTE)
							fant_r->etat = POURSUITE;
						if(fant_o->etat == ATTENTE)
							fant_o->etat = POURSUITE;
						if(fant_p->etat == ATTENTE)
							fant_p->etat = POURSUITE;
						switch(e.key.keysym.sym) {
							case SDLK_UP:
								pacman->nextdir = 'h';
								break;
							case SDLK_DOWN:
								pacman->nextdir = 'b';
								break;
							case SDLK_RIGHT:
								pacman->nextdir = 'd';
								break;
							case SDLK_LEFT:
								pacman->nextdir = 'g';
								break;
						}
						break;
				}
			}

			SDL_RenderClear(rend);

			dessine_lab(labyrinthe, rend);

			deplace_fantome(fant_b, labyrinthe, rend, pacman, fps);
			deplace_fantome(fant_r, labyrinthe, rend, pacman, fps);
			deplace_fantome(fant_o, labyrinthe, rend, pacman, fps);
			deplace_fantome(fant_p, labyrinthe, rend, pacman, fps);
			deplace_joueur(pacman, labyrinthe, &nb_pacgums, rend, fant_b,
						   fant_r, fant_o, fant_p, fps);
			
			gere_collisions(pacman, fant_b, fant_r, fant_o, fant_p);
			
			if(pacman->vies == 0) {
				do {
					genere_lab(labyrinthe, &nb_pacgums);
				} while(nb_pacgums < 280 || nb_pacgums > 350);
				pacman->vies = 3,
				pacman->score = 0;
				niveau = 1;
				init_place(pacman, fant_b, fant_r, fant_o, fant_p);
			}
			
			if(nb_pacgums == 0) {
				do {
					genere_lab(labyrinthe, &nb_pacgums);
				} while(nb_pacgums < 280 || nb_pacgums > 350);
				niveau++;
				init_place(pacman, fant_b, fant_r, fant_o, fant_p);
			}
			
			score_osd(rend, police_menu, pacman, niveau);

			SDL_RenderPresent(rend);
			if(delta < mspf)
				SDL_Delay(mspf - delta);
			start_time = end_time;
			end_time = SDL_GetTicks();


		}
	}

	detruit_sprites();
	detruit_joueur(&pacman);
	detruit_fantome(&fant_b);
	detruit_fantome(&fant_r);
	detruit_fantome(&fant_o);
	detruit_fantome(&fant_p);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(fenetre);
	TTF_CloseFont(police_menu);
	TTF_Quit();
	SDL_Quit();
	return 0;
}
