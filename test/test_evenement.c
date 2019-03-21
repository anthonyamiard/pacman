#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

int main(int argc, char** argv) {
	SDL_Window* window = NULL;

	if(SDL_Init(SDL_INIT_VIDEO) == -1) {
		fprintf(stdout, "Echec de l'initialisation de la SDL (%s)\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	window = SDL_CreateWindow("Test SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
	if(!window) {
		fprintf(stderr, "Erreur a la creation de la fenetre : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if(window) {
		int running = 1;
		while(running) {
			SDL_Event e;
			while(SDL_PollEvent(&e)) {
				switch(e.type) {
					case SDL_QUIT: running = 0; break;
					case SDL_KEYDOWN:
						switch(e.key.keysym.sym) {
							case SDLK_q:
								running = 0;
								break;
						}

					break;
				}
			}
		}
	} else {
		fprintf(stderr, "Erreur de creation de la fenetre : %s\n", SDL_GetError());
	}

	SDL_Quit();

	return 0;
}
