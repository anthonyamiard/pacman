/**
 * \file ToTexture.c
 * \brief Fichier qui contient les fonctions qui transforme les images et texte en texture pour la  SDL
 * \author Taliesin AMBROISE
 * \date 2 mars 2019
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "surface.h"

/**
 * \fn SDL_Texture* tex_img_png(char * s, SDL_Renderer* renderer)
 * \brief Transforme une image PNG en format texture pour pouvoir l'afficher dans la fenêtre SDL
 * \param s : chemin d'accès vers l'image PNG
 * \param renderer : le renderer de la fenêtre.
 * \return Pointeur sur SDL_Texture
 */
SDL_Texture* tex_img_png(char * s, SDL_Renderer* renderer){

    SDL_RWops *rwop=SDL_RWFromFile(s, "rb");
	SDL_Surface *image=IMG_LoadPNG_RW(rwop);
	if(!image) {
	     printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
	}
	SDL_Texture *image_btn_tex = SDL_CreateTextureFromSurface(renderer, image);
	if(!image_btn_tex){
		fprintf(stderr, "Erreur à la création du rendu de l'image : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_FreeSurface(image); /* on a la texture, plus besoin de l'image */
    return image_btn_tex;
}

/**
 * \fn SDL_Texture* tex_img_png(char * s, SDL_Renderer* renderer)
 * \brief Transforme du texte en format texture pour pouvoir l'afficher dans la fenêtre SDL
 * \param font : chemin d'accès vers la police d'écriture.
 * \param size : taille de la police
 * \param s : texte
 * \param color : couleur pour le texte
 * \param renderer : le renderer de la fenêtre.
 * \return Pointeur sur SDL_Texture
 */
SDL_Texture *tex_text(char* font,int size, char* s, SDL_Color color, SDL_Renderer* renderer){
    TTF_Font *policeTitre = NULL;
	if( (policeTitre = TTF_OpenFont(font, size)) == NULL){
        fprintf(stderr, "erreur chargement font\n");
        exit(EXIT_FAILURE);
    }
    SDL_Surface *texte = TTF_RenderUTF8_Blended(policeTitre, s, color);
    if(!texte){
        fprintf(stderr, "Erreur à la création du texte : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Texture *texte_tex = SDL_CreateTextureFromSurface(renderer, texte);
    if(!texte_tex){
        fprintf(stderr, "Erreur à la création du rendu du texte : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_FreeSurface(texte); /* on a la texture, plus besoin du texte */
    TTF_CloseFont(policeTitre); /* Doit être avant TTF_Quit() */
    return texte_tex;
}
