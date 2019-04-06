/*!
 * \file	mouv.h
 * \author	Anthony Amiard
 * 
 * Gestion des déplacements et collisions
 * 
 */

#ifndef _MOUV_H_
#define _MOUV_H_

#include <SDL2/SDL.h>
#include "../include/taille_lab.h"
#include "../include/objets.h"


/*!
 * \brief	Déplace la position dans le labyrinthe
 * 
 * Déplace la position d'un objet dans le labyrinthe dans une direction donnée
 * et d'une vitesse donnée, si la destination est un chemin.
 * 
 * \param[in]		coord		Coordonnées de la position en numéro de case du
 * 								labyrinthe
 * \param[in,out]	position	Position à déplacer, en pixels
 * \param[in]		labyrinthe	Labyrinthe dans lequel se déplacer
 * \param[in]		dir			Direction dans laquelle se déplacer
 * 								- \c 'g' à gauche
 * 								- \c 'd' à droite
 * 								- \c 'h' en haut
 * 								- \c 'b' en bas
 * \param[in]		vitesse		Nombre de pixels sur lequel se déplacer
 * \retval			0			Aucune erreur
 */
int deplace_coord(const coord_t * coord, SDL_Rect * position,
				  const char labyrinthe[N_LAB][M_LAB], char dir, int vitesse);

/*!
 * \brief	Déplace le joueur dans le labyrinthe
 * 
 * Déplace le joueur dans le labyrinthe d'après la variable globale \c pacdir.
 * 
 * \param[in,out]	joueur			Joueur à déplacer
 * \param[in]		labyrinthe		Labyrinthe dans lequel déplacer le joueur
 * \param[in,out]	rend			Renderer à mettre à jour
 * \param[in,out]	f1, f2, f3, f4	Fantômes
 */
void deplace_joueur(joueur_t * joueur,
					char labyrinthe[N_LAB][M_LAB],
					SDL_Renderer * rend,
					fantome_t * f1,
					fantome_t * f2,
					fantome_t * f3,
					fantome_t * f4);

/*!
 * \brief	Déplace le fantôme dans le labyrinthe
 * 
 * Déplace le fantôme dans le labyrinthe d'après son attribut \c dir.
 * 
 * \param[in,out]	fantome		Fantôme à déplacer
 * \param[in]		labyrinthe	Labyrinthe dans lequel déplacer le joueur
 * \param[in,out]	rend		Renderer à mettre à jour
 * \param[in]		joueur		Joueur à pourchasser
 */
void deplace_fantome(fantome_t * fantome, char labyrinthe[N_LAB][M_LAB], SDL_Renderer * rend, joueur_t * joueur);

/*!
 * \brief	Teste s'il y a collision entre le joueur et un fantôme
 * \param[in]	joueur	Joueur
 * \param[in]	fantome	Fantome à tester
 * \retval		1		Il y a collision entre le joueur et le fantôme
 * \retval		0		Il n'y a pas collision entre le joueur et le fantôme
 */
int collision(const joueur_t * joueur, const fantome_t * fantome);

/*!
 * \brief	Teste s'il y a collision entre le joueur et un fantôme et effectue
 * 			les opérations nécessaires
 * \param[in,out]	joueur							Joueur
 * \param[in,out]	fant_b, fant_r, fant_o, fant_p	Fantômes bleu, rouge, orange
 * 													et rose
 */
void gere_collisions(joueur_t * joueur,
					 fantome_t * fant_b,
					 fantome_t * fant_r,
					 fantome_t * fant_o,
					 fantome_t * fant_p);



#endif
