#define _MAIN_C_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/IA.h"
#include "../include/objets.h"
#include "../include/labyrinthe.h"

#define N_TESTS 9
#define VITESSE 1

/* Affichage du resultat des fonctions chemin_* */
void aff_res_chemin(coord_t dep, coord_t arr, coord_t res, char * fonction) {
	printf("%s : (%d,%d) -> (%d,%d) (pacdir = \'%c\') : (%d,%d)\n", fonction, dep.x, dep.y, arr.x, arr.y, pacdir, res.x, res.y);
}

int main() {
	srand(time(NULL));

	char lab[N_LAB][M_LAB];
	int nb_pacgums;
	lab_manuel(lab, &nb_pacgums);

	coord_t dep;
	coord_t arr;
	coord_t res;

	int l_dep_x[N_TESTS] = { 3, 24,  6,  6, 12, 15, 10, 10, 6};
	int l_dep_y[N_TESTS] = { 5,  5,  2,  8,  4,  4,  5,  8, 5};
	int l_arr_x[N_TESTS] = {24, 24,  6,  6, 15, 12, 10, 10, 2};
	int l_arr_y[N_TESTS] = { 5,  5,  8,  2,  4,  4,  8,  5, 1};
	char l_pacdir[N_TESTS] = {'d', 'g', 'b', 'h', 'b', 'h', 'd', 'g', 'g'};
	int i;

	/* Tests fonctions chemin_* */

	printf("*\n*Tests des fonctions chemin_*\n*\n");

	for(i = 0; i < N_TESTS; i++) {

		dep.x = l_dep_x[i];
		dep.y = l_dep_y[i];
		arr.x = l_arr_x[i];
		arr.y = l_arr_y[i];
		pacdir = l_pacdir[i];

		res = chemin_court(lab, &dep, &arr);
		aff_res_chemin(dep, arr, res, "chemin_court");
		res = chemin_aleatoire(lab, &dep, &arr);
		aff_res_chemin(dep, arr, res, "chemin_aleatoire");
		res = chemin_anticipe(lab, &dep, &arr);
		aff_res_chemin(dep, arr, res, "chemin_anticipe");
		res = chemin_fuir(lab, &dep, &arr);
		aff_res_chemin(dep, arr, res, "chemin_fuir");
		printf("\n");
	}


	return 0;
}
