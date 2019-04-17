/*!
 * \file		score.h
 * \author		Anthony Amiard
 * 
 * Définition du nombre de points gagné à différents moments du jeu.
 * 
 */

#ifndef _SCORE_H_
#define _SCORE_H_

#include "objets.h"

/*
 * CONSTANTES
 */

/*! Nombre de points procurés par une pacgum */
#define PTS_PACGUM		10
/*! Nombre de points procurés par une super pacgum */
#define PTS_SPG			50

/*! Nombre de points procurés lors de la consommation du premier fantôme */
#define PTS_FANTOME_1	200
/*! Nombre de points procurés lors de la consommation du deuxième fantôme */
#define PTS_FANTOME_2	400
/*! Nombre de points procurés lors de la consommation du troisième fantôme */
#define PTS_FANTOME_3	800
/*! Nombre de points procurés lors de la consommation du quatrième fantôme */
#define PTS_FANTOME_4	1600

/*! Palier de points qui rapporte une vie */
#define PTS_GAIN_VIE	10000


/*
 * FONCTIONS
 */

/*!
 * \brief           Ajoute des points au joueur
 * 
 * Ajoute \c nb_points au joueur \c joueur et gère le gain de vie au palier
 * \c PTS_GAIN_VIE.
 * 
 * \param[in,out]   joueur      Joueur
 * \param[in]       nb_points   Nombre de points à ajouter
 */
void ajout_points(joueur_t * joueur, int nb_points);


#endif
