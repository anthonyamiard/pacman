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
		printf("\tnom     : %s,\n", fantome->nom);
		printf("\tcouleur : %c,\n", fantome->couleur);
		printf("\tchemin  : %p,\n", fantome->chemin);
		printf("\tetat    : %d,\n", fantome->etat);
		printf("\tcoord   : ");
		aff_coord(fantome->coord);
		printf("\n}\n");
	}
}

int main() {
	
	printf("\n** Création de coordonnées **\n\n");
	coord_t * coord = cree_coord(18, 36);
	aff_coord(coord);
	printf("\n");
	
	printf("\n** Création d'un fruit **\n\n");
	fruit_t * fruit = cree_fruit("Cerise", 50, 12, 15);
	aff_fruit(fruit);
	
	printf("\n** Création du joueur **\n\n");
	joueur_t * joueur = cree_joueur("Pacman", 3, 0, 25, 35);
	aff_joueur(joueur);
	
	printf("\n** Création des fantômes **\n\n");
	fantome_t * f1 = cree_fantome("Fantome 1", 'b', chemin_court, 21, 8);
	printf("f1 : ");
	aff_fantome(f1);
	fantome_t * f2 = cree_fantome("Fantome 2", 'r', chemin_aleatoire, 5, 9);
	printf("f2 : ");
	aff_fantome(f2);
	fantome_t * f3 = cree_fantome("Fantome 3", 'o', chemin_anticipe, 7, 15);
	printf("f3 : ");
	aff_fantome(f3);
	fantome_t * f4 = cree_fantome("Fantome 4", 'p', chemin_fuir, 6, 4);
	printf("f4 : ");
	aff_fantome(f4);
	
	printf("\n** Suppression des objets **\n\n");
	detruit_coord(&coord);
	printf("Coordonnées : ");
	aff_coord(coord);
	printf("\n");
	detruit_fruit(&fruit);
	printf("Fruit : ");
	aff_fruit(fruit);
	detruit_joueur(&joueur);
	printf("Joueur : ");
	aff_joueur(joueur);
	detruit_fantome(&f1);
	printf("f1 : ");
	aff_fantome(f1);
	detruit_fantome(&f2);
	printf("f2 : ");
	aff_fantome(f2);
	detruit_fantome(&f3);
	printf("f3 : ");
	aff_fantome(f3);
	detruit_fantome(&f4);
	printf("f4 : ");
	aff_fantome(f4);
	printf("\n");
	
	return 0;
}
