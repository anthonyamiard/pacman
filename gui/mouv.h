/*!
 * \file	mouv.h
 * \author	Anthony Amiard
 * 
 * Gestion des déplacements
 * 
 */

#ifndef _MOUV_H_
#define _MOUV_H_

#include <SDL2/SDL.h>
#include "../include/taille_lab.h"
#include "../include/objets.h"



int deplace_coord(const coord_t * coord, coord_t * coord_fines, const char labyrinthe[N_LAB][M_LAB], char dir);

int deplace_joueur(joueur_t * joueur, const char labyrinthe[N_LAB][M_LAB], SDL_Rect * position);



#endif
