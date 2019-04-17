/*!
 * \file	taille_lab.h
 * \author	Anthony Amiard
 * \date	2019
 * 
 * Constantes de la taille du labyrinthe et des coordonnées des différents
 * 
 */

#ifndef _TAILLE_LAB_H_
#define _TAILLE_LAB_H_

#define M_LAB       28  /*!< Nombre de colonnes du labyrinthe */
#define N_LAB       31  /*!< Nombre de lignes du labyrinthe */

#define X_DEP       13  /*!< Coordonnée X du point de départ */
#define Y_DEP       23  /*!< Coordonnée Y du point de départ */

#define X_BOITE     13  /*!< Coordonnée X de l'entrée de la boîte */
#define Y_BOITE     12  /*!< Coordonnée Y de l'entrée de la boîte */

#define X_BLEU      12  /*!< Coordonnée X de départ du fantôme bleu */
#define Y_BLEU      14  /*!< Coordonnée Y de départ du fantôme bleu */

#define X_ROUGE     13  /*!< Coordonnée X de départ du fantôme rouge */
#define Y_ROUGE     14  /*!< Coordonnée Y de départ du fantôme rouge */

#define X_ROSE      14  /*!< Coordonnée X de départ du fantôme rose */
#define Y_ROSE      14  /*!< Coordonnée Y de départ du fantôme rose */

#define X_ORANGE    15  /*!< Coordonnée X de départ du fantôme orange */
#define Y_ORANGE    14  /*!< Coordonnée Y de départ du fantôme orange */

#define TAILLE_CASE 24  /*!< Taille d'une case du labyrinthe en pixels */

/*! Largeur en pixels de la fenêtre */
#define W_FEN       (M_LAB * TAILLE_CASE)
/*! Hauteur en pixels de la fenêtre */
#define H_FEN       (N_LAB * TAILLE_CASE + 48)

#endif
