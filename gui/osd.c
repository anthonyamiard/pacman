/*!
 * \file	osd.c
 * \author	Anthony Amiard
 * 
 * Affichage du score et du nombre de vies en bas de la fenêtre, et de messages
 * au milieu du labyrinthe.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "osd.h"
#include "dessin.h"
#include "../include/taille_lab.h"

void score_osd(SDL_Renderer * rend,
			   TTF_Font * police,
			   const joueur_t * joueur,
			   int niveau) {
	SDL_Color noir = {0, 0, 0};
	SDL_Color blanc = {255, 255, 255};
	char str_score[15];
	char str_vies[15];
	char str_niveau[15];
	int w, h;
	sprintf(str_niveau, "Niveau : %03d", niveau);
	SDL_Texture * txt_niveau = cree_texte(police, str_niveau, blanc, noir, 0,
										  rend);
	if(txt_niveau != NULL) {
		SDL_QueryTexture(txt_niveau, NULL, NULL, &w, &h);
		rend_texture(txt_niveau, rend, W_FEN - w, H_FEN - h);
	}
	SDL_DestroyTexture(txt_niveau);
	if(joueur == NULL) {
		fprintf(stderr, "Erreur : joueur nul.\n");
	} else {
		sprintf(str_score, "Score : %04d", joueur->score);
		sprintf(str_vies, "Vies : %02d", joueur->vies);
		SDL_Texture * txt_score = cree_texte(police, str_score, blanc, noir, 0,
											 rend);
		SDL_Texture * txt_vies = cree_texte(police, str_vies, blanc, noir, 0,
											rend);
		if(txt_score != NULL) {
			SDL_QueryTexture(txt_score, NULL, NULL, &w, &h);
			rend_texture(txt_score, rend, 0, H_FEN - h);
		}
		if(txt_vies != NULL) {
			SDL_QueryTexture(txt_vies, NULL, NULL, &w, &h);
			rend_texture(txt_vies, rend, W_FEN / 2 - w / 2, H_FEN - h);
		}
		SDL_DestroyTexture(txt_score);
		SDL_DestroyTexture(txt_vies);
	}
}

void message_osd(SDL_Renderer * rend, TTF_Font * police, const char * message) {
	SDL_Color noir = {0, 0, 0};
	SDL_Color jaune = {255, 255, 0};
	int w;
	SDL_Texture * texture = cree_texte(police, message, jaune, noir, 1, rend);
	if(texture != NULL) {
		SDL_QueryTexture(texture, NULL, NULL, &w, NULL);
		rend_texture(texture, rend, W_FEN / 2 - w / 2,
					 (Y_BOITE + 5) * TAILLE_CASE);
		SDL_DestroyTexture(texture);
	}
}
