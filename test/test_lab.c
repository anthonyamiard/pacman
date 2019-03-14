/*!
 * \file	test_lab.c
 * \author	Anthony Amiard
 * \date	2019
 *
 * Tests sur la génération de labyrinthes
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/labyrinthe.h"

#define N_COORD 6
#define N_CASES 8
#define N_COORD_2 10
#define N_COORD_3 5
#define N_COORD_4 3

int main() {
	srand(time(NULL));

	char labyrinthe[N_LAB][M_LAB];
	int nb_pacgums;

	/* lab_manuel */
	printf("*\n* Labyrinthe manuel\n*\n");
	lab_manuel(labyrinthe, &nb_pacgums);
	aff_lab(labyrinthe);
	printf("nb pacgums = %d\n", nb_pacgums);

	int i, j;
	char demi_lab[N_LAB][M_LAB/2];
	for(i = 0; i < N_LAB; i++)
		for(j = 0; j < M_LAB/2; j++)
			demi_lab[i][j] = labyrinthe[i][j];

	/* cood_alea */
	int coord_x[N_COORD] = {5, 0, 9, 0, -7, M_LAB};
	int coord_y[N_COORD] = {8, 7, 0, 0, -8, 5};
	int x2, y2;

	printf("*\n* Coordonnées aléatoires\n*\n");
	for(i = 0; i < N_COORD; i++) {
		coord_alea(coord_x[i], coord_y[i], &x2, &y2);
		printf("origine = (%2d, %2d), génération 1 = (%2d, %2d), ", coord_x[i],
			   coord_y[i], x2, y2);
		coord_alea(coord_x[i], coord_y[i], &x2, &y2);
		printf("génération 2 = (%2d, %2d), ", x2, y2);
		coord_alea(coord_x[i], coord_y[i], &x2, &y2);
		printf("génération 3 = (%2d, %2d)\n", x2, y2);
	}

	/* est_chemin */
	char cases[N_CASES] = {'c', 'p', 's', 'm', 'b', 'e', 'a', '\0'};
	char attendu_ec[N_CASES] = {1, 1, 1, 0, 0, 0, 0, 0};

	int retour;
	printf("*\n* est_chemin\n*\n");
	for(i = 0; i < N_CASES; i++) {
		retour = est_chemin(cases[i]);
		printf("Case '%1c' (%#4x) : est_chemin = %1d (attendu = %1d)\n", cases[i],
			   cases[i], retour, attendu_ec[i]);
	}

	/* nb_chemins_voisins */
	int coord_x2[N_COORD_2] = {6, 6, 12,  7, 13, 0, 0, 13, -2, 18};
	int coord_y2[N_COORD_2] = {5, 1,  1, 12, 19, 0, 9,  5, -3,  1};
	int attendu_ncv[N_COORD_2] = {4, 3, 2, 1, 0, 0, 1,  2,  0,  2};
	int attendu_ncvd[N_COORD_2] = {4, 3, 2, 1, 0, 0, 1, 2,  0,  0};

	printf("*\n* nb_chemins_voisins et nb_chemins_voisins_demi\n*\n");
	for(i = 0; i < N_COORD_2; i++) {
		retour = nb_chemins_voisins(labyrinthe, coord_x2[i], coord_y2[i]);
		printf("(%2d,%2d) : nb_chemins_voisins = %1d (attendu = %1d), ",
			   coord_x2[i], coord_y2[i], retour, attendu_ncv[i]);
		retour = nb_chemins_voisins_demi(demi_lab, coord_x2[i], coord_y2[i]);
		printf("nb_chemins_voisins_demi = %1d (attendu = %1d)\n", retour,
			   attendu_ncvd[i]);
	}

	/* place_permise */
	int coord_x3[N_COORD_3] = { 7, 5, 2, 3, 13};
	int coord_y3[N_COORD_3] = {17, 5, 2, 6,  6};
	int attendu_pp[N_COORD_3] = {1, 0, 0, 2, 1};

	printf("*\n* place_permise\n*\n");
	for(i = 0; i < N_COORD_3; i++) {
		retour = place_permise(demi_lab, coord_x3[i], coord_y3[i]);
		printf("(%2d, %2d) : place_permise = %1d (attendu = %1d)\n", coord_x3[i],
			   coord_y3[i], retour, attendu_pp[i]);
	}

	/* debouche_cds */

	/* Préparation du labyrinthe */
	demi_lab[2][12] = 'm';
	demi_lab[3][12] = 'm';
	demi_lab[4][12] = 'm';
	demi_lab[9][6] = 'm';
	demi_lab[10][6] = 'm';
	demi_lab[12][6] = 'm';
	demi_lab[13][6] = 'm';
	demi_lab[23][2] = 'm';


	int coord_x4[N_COORD_4] = {12,  6,  1};
	int coord_y4[N_COORD_4] = { 1, 11, 23};

	printf("*\n* debouche_cds\n*\n");
	aff_lab_demi(demi_lab);
	for(i = 0; i < N_COORD_4; i++) {
		printf("(%d, %d)\n", coord_x4[i], coord_y4[i]);
		debouche_cds(demi_lab, coord_x4[i], coord_y4[i]);
		aff_lab_demi(demi_lab);
	}

	/* suppr_cds */

	/* Préparation du labyrinthe */
	for(i = 0; i < N_LAB; i++)
		for(j = 0; j < M_LAB/2; j++)
			demi_lab[i][j] = labyrinthe[i][j];
	demi_lab[2][12] = 'm';
	demi_lab[3][12] = 'm';
	demi_lab[4][12] = 'm';
	demi_lab[9][6] = 'm';
	demi_lab[10][6] = 'm';
	demi_lab[12][6] = 'm';
	demi_lab[13][6] = 'm';
	demi_lab[23][2] = 'm';

	printf("*\n* suppr_cds\n*\n");
	aff_lab_demi(demi_lab);
	for(i = 0; i < N_COORD_4; i++) {
		printf("(%d, %d)\n", coord_x4[i], coord_y4[i]);
		suppr_cds(demi_lab, coord_x4[i], coord_y4[i]);
		aff_lab_demi(demi_lab);
	}

	printf("*\n* Génération aléatoire de labyrinthe\n*\n");
	genere_lab(labyrinthe, &nb_pacgums);
	aff_lab(labyrinthe);
	printf("nb pacgums = %d\n", nb_pacgums);

	return 0;
}
