/*!
 * \file	mouv.h
 * \author	Anthony Amiard
 * 
 * Gestion des déplacements
 * 
 */

#ifndef _MOUV_H_
#define _MOUV_H_

#include "../include/taille_lab.h"
#include "../include/objets.h"



int deplace_coord(coord_t * coord, const char labyrinthe[N_LAB][M_LAB], char dir);



#endif
