#ifndef _TO_SURFACE_H_
#define _TO_SURFACE_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

SDL_Texture* tex_img_png(char * s, SDL_Renderer* renderer);

SDL_Texture *tex_text(char* font,int size, char* s, SDL_Color color, SDL_Renderer* renderer);

#endif
