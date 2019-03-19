/*!
 * \file	test_objets.c
 * \author	Anthony Amiard
 * \date	2019
 * 
 * Tests sur la création et la destruction des objets.
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/objets.h"
#include "../include/IA.h"

/*!
 * \brief		Affiche les attributs d'un objet coord_t
 * \param[in]	coord	Coordonnées à afficher
 */
void aff_coord(const coord_t * coord) {
	if(coord == NULL) {
		printf("NULL");
	} else {
		printf("{ x : %d, y : %d }", coord->x, coord->y);
	}
}

/*!
 * \brief		Affiche les attributs d'un objet fruit_t
 * \param[in]	fruit	Fruit duquel afficher les coordonnées
 */
void aff_fruit(const fruit_t * fruit) {
	if(fruit == NULL) {
		printf("NULL\n");
	} else {
		printf("{\n");
		printf("\tnom    : %s,\n", fruit->nom);
		printf("\tpoints : %d,\n", fruit->points);
		printf("\tcoord  : ");
		aff_coord(fruit->coord);
		printf("\n}\n");
	}
}

/*!
 * \brief		Affiche les attributs d'un objet joueur_t
 * \param[in]	joueur	Fruit duquel afficher les attributs
 */
void aff_joueur(const joueur_t * joueur) {
	if(joueur == NULL) {
		printf("NULL\n");
	} else {
		printf("{\n");
		printf("\tnom   : %s,\n", joueur->nom);
		printf("\tvies  : %d,\n", joueur->vies);
		printf("\tscore : %d,\n", joueur->score);
		printf("\tcoord : ");
		aff_coord(joueur->coord);
		printf("\n}\n");
	}
}

/*!
 * \brief		Affiche les attributs d'un objet fantome_t
 * \param[in]	fantome	Fantôme duquel afficher les attributs
 */
void aff_fantome(const fantome_t * fantome) {
	if(fantome == NULL) {
		printf("NULL\n");
	} else {
		printf("{\n");
		printf("\tnom     : %s,\n", fantome->joueur);
		printf("\tcouleur : %c,\n", fantome->couleur);
		printf("\tchemin  : %p,\n", fantome->chemin);
		printf("\tetat    : %d,\n", fantome->etat);
		printf("\tcoord   : ");
		aff_coord(fantome->coord);
		printf("\n}\n");
	}
}

int main() {
	return 0;
}
