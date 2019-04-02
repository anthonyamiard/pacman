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



int deplace_coord(const coord_t * coord, SDL_Rect * coord_fines, const char labyrinthe[N_LAB][M_LAB], char dir, int vitesse);

void deplace_joueur(joueur_t * joueur, char labyrinthe[N_LAB][M_LAB], SDL_Renderer * rend);

void deplace_fantome(fantome_t * fantome, char labyrinthe[N_LAB][M_LAB], SDL_Renderer * rend, joueur_t * joueur);



#endif
