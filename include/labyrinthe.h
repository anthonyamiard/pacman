/*
 * Definition des constantes et des fonctions permettant de generer un
 * labyrinthe
 */

#ifndef _LABYRINTHE_H_
#define _LABYRINTHE_H_



/*
 * CONSTANTES
 */


#include "taille_lab.h"



/*
 * FONCTIONS
 */
 
/* Genere un labyrinthe aleatoire dans la matrice labyrinthe
 * 'm' = mur
 * 'c' = chemin vide
 * 'p' = chemin avec pacgum
 * 's' = chemin avec super pacgum
 * 'b' = boite des fantomes
 * 'e' = entree de la boite
 * Ecrit le nombre de pacgums presents dans le labyrinthe dans nb_pacgums
 * Renvoie 0 si tout se passe bien
 */
int genere_lab(char labyrinthe[N_LAB][M_LAB], int * nb_pacgums);

/* Ecrit un labyrinthe genere manuellement dans la matrice labyrinthe */
int lab_manuel(char labyrinthe[N_LAB][M_LAB], int * nb_pacgums);

/* Affiche le labyrinthe sur la sortie standard */
void aff_lab(const char labyrinthe[N_LAB][M_LAB]);

/* Renvoie vrai si le caractere case_lab correspond a un chemin (avec ou sans 
   item), faux sinon */
int est_chemin(char case_lab);


#endif
