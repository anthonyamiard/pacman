/*
 * Définition des prototypes des fonctions pour l'IA
*/

#ifndef _IA_H_
#define _IA_H_

/* Fonction trouver chemin le plus court pour atteindre le joueur */
void chemin_court(char labyrinthe[N_LAB][M_LAB], coord_t * coord_dep, coord_t * coord_arr);

/* Fonction trouver chemin aleatoire pour atteindre le joueur */
void chemin_aleatoire(char labyrinthe[N_LAB][M_LAB], coord_t * coord_dep, coord_t * coord_arr);

/* Fonction trouver chemin pour anticiper les déplacements du joueur  */
void chemin_anticipe(char labyrinthe[N_LAB][M_LAB], coord_t * coord_dep, coord_t * coord_arr);

/* Fonction trouver chemin pour fuir le joueur*/
void chemin_fuir(char labyrinthe[N_LAB][M_LAB], coord_t * coord_dep, coord_t * coord_arr);


/* Fonction déplacer le fantome */
void fantome(char labyrinthe[N_LAB][M_LAB],fantome_t * fantome,joueur_t * joueur, int vitesse, void (*chemin)(char[N_LAB][M_LAB], coord_t *, coord_t *) );

/* Fonction qui renvoie 0 si tout ce passe bien*/
int ramasse_pacgum(char labyrinthe[N_LAB][M_LAB], joueur_t * joueur);

#endif
