#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

int main(int argc, char** argv) {
	SDL_Window* window = NULL;
	SDL_Rect position;

	if(SDL_Init(SDL_INIT_VIDEO) == -1) {
		fprintf(stdout, "Echec de l'initialisation de la SDL (%s)\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	window = SDL_CreateWindow("Test SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
	if(!window) {
		fprintf(stderr, "Erreur a la creation de la fenetre : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Surface* image = SDL_LoadBMP("../img/pacgum.bmp");
	if(!image) {
		fprintf(stderr, "Erreur de chargement de l'image : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(!renderer) {
		fprintf(stderr, "Erreur de chargement du renderer : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Texture* image_tex = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);

	if(window) {
		int running = 1;
		while(running) {
			SDL_Event e;
			while(SDL_PollEvent(&e)) {
				switch(e.type) {
					case SDL_QUIT: running = 0; break;
					case SDL_WINDOWEVENT:
						switch(e.window.event) {
							case SDL_WINDOWEVENT_EXPOSED:
							case SDL_WINDOWEVENT_SIZE_CHANGED:
							case SDL_WINDOWEVENT_RESIZED:
							case SDL_WINDOWEVENT_SHOWN:
								position.x = 640 / 2 - image->w / 2;
								position.y = 480 / 2 - image->h / 2;
								SDL_QueryTexture(image_tex, NULL, NULL, &(position.w), &(position.h));
								SDL_RenderCopy(renderer, image_tex, NULL, &position);
								SDL_RenderPresent(renderer);
								break;
						}
						break;
					case SDL_KEYDOWN:
						switch(e.key.keysym.sym) {
							case SDLK_UP:
								position.y--;
								break;
							case SDLK_DOWN:
								position.y++;
								break;
							case SDLK_RIGHT:
								position.x++;
								break;
							case SDLK_LEFT:
								position.x--;
								break;
							case SDLK_q: running = 0;	break;
						}

					SDL_RenderClear(renderer);
					SDL_RenderCopy(renderer, image_tex, NULL, &position);
					SDL_RenderPresent(renderer);
					break;
				}
			}
		}
	} else {
		fprintf(stderr, "Erreur de creation de la fenetre : %s\n", SDL_GetError());
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}
