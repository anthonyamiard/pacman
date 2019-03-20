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

int main() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Quit();
	return 0;
}
