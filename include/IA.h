/*!
 * \file IA.h
 * \author Taliesin AMBROISE
 * \brief Fonctions permettant de coder l'intelligence artificiel
 * \date 2019
 *
 * Définition des fonctions permettant de coder l'intelligence artificiel
 */

#ifndef _IA_H_
#define _IA_H_
#include "taille_lab.h"
#include "objets.h"

/*!
 * \fn coord_t chemin_court(char labyrinthe[N_LAB][M_LAB], coord_t * coord_dep, coord_t * coord_arr)
 * \brief Code le comportement chemin court
 *
 * L'ennemi avec ce comportement cherchera le chemin le plus court entre lui
 * et pacman
 *
 * \param[in] labyrinthe Labyrinthe de \c N_LAB lignes et \c M_LAB colonnes
 * \param[in] coord_dep Coordonnées de départ où se trouve l'ennemi
 * \param[in] coord_arr Coordonnées d'arrivée où se trouve pacman
 * \retval coord_t La coordonnée suivante à l'instant t+1
 */
coord_t chemin_court(char labyrinthe[N_LAB][M_LAB], coord_t * coord_dep, coord_t * coord_arr);

/*!
 * \fn coord_t chemin_aleatoire(char labyrinthe[N_LAB][M_LAB], coord_t * coord_dep, coord_t * coord_arr)
 * \brief Code le comportement chemin aleatoire
 *
 * L'ennemi avec ce comportement prendra un chemin aléatoire sans se soucier de
 * l'emplacement de pacman
 *
 * \param[in] labyrinthe Labyrinthe de \c N_LAB lignes et \c M_LAB colonnes
 * \param[in] coord_dep Coordonnées de départ où se trouve l'ennemi
 * \param[in] coord_arr Coordonnées d'arrivée où se trouve pacman
 * \retval coord_t La coordonnée suivante à l'instant t+1
 */
coord_t chemin_aleatoire(char labyrinthe[N_LAB][M_LAB], coord_t * coord_dep, coord_t * coord_arr);

/*!
 * \fn coord_t chemin_anticipe(char labyrinthe[N_LAB][M_LAB], coord_t * coord_dep, coord_t * coord_arr)
 * \brief Code le comportement chemin anticipe
 *
 * L'ennemi avec ce comportement anticipera les déplacements de pacman et le
 * prendra en embuscade
 *
 * \param[in] labyrinthe Labyrinthe de \c N_LAB lignes et \c M_LAB colonnes
 * \param[in] coord_dep Coordonnées de départ où se trouve l'ennemi
 * \param[in] coord_arr Coordonnées d'arrivée où se trouve pacman
 * \retval coord_t La coordonnée suivante à l'instant t+1
 */
coord_t chemin_anticipe(char labyrinthe[N_LAB][M_LAB], coord_t * coord_dep, coord_t * coord_arr);

/*!
 * \fn coord_t chemin_fuir(char labyrinthe[N_LAB][M_LAB], coord_t * coord_dep, coord_t * coord_arr)
 * \brief Code le comportement chemin fuir
 *
 * L'ennemi avec ce comportement cherchera à fuir pacman dès que c'est possible
 *
 * \param[in] labyrinthe Labyrinthe de \c N_LAB lignes et \c M_LAB colonnes
 * \param[in] coord_dep Coordonnées de départ où se trouve l'ennemi
 * \param[in] coord_arr Coordonnées d'arrivée où se trouve pacman
 * \retval coord_t La coordonnée suivante à l'instant t+1
 */
coord_t chemin_fuir(char labyrinthe[N_LAB][M_LAB], coord_t * coord_dep, coord_t * coord_arr);

#endif
