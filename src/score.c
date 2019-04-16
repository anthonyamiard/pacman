/*!
 * \file		score.c
 * \author		Anthony Amiard
 * 
 * Fonctions de gestion du score du joueur.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/score.h"

void ajout_points(joueur_t * joueur, int nb_points) {
	if(joueur != NULL) {
		joueur->score += nb_points;
		if((joueur->score - nb_points) % PTS_GAIN_VIE >
			joueur->score % PTS_GAIN_VIE)
			joueur->vies += 1;
	}
}
