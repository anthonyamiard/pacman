#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/IA.h"
#include "../include/labyrinthe.h"
#include "../include/objets.h"

#define N_TESTS 1

void aff_res_chemin(coord_t dep, coord_t arr, coord_t res, char * fonction) {
	printf("%s : (%d,%d) -> (%d,%d) : (%d,%d)\n", fonction, dep.x, dep.y, arr.x, arr.y, res.x, res.y);
}

int main() {
	srand(time(NULL));
	
	char lab[N_LAB][M_LAB];
	int nb_pacgums;
	lab_manuel(lab, &nb_pacgums);
	
	coord_t dep;
	coord_t arr;
	coord_t res;
	
	int l_dep_x[N_TESTS] = { 3};
	int l_dep_y[N_TESTS] = { 5};
	int l_arr_x[N_TESTS] = {24};
	int l_arr_y[N_TESTS] = { 5};
	int i;
	
	/* Tests fonctions chemin_* */
	
	for(i = 0; i < N_TESTS; i++) {
	
		dep.x = l_dep_x[i];
		dep.y = l_dep_y[i];
		arr.x = l_arr_x[i];
		arr.y = l_arr_y[i];
		
		res = chemin_court(lab, &coord_dep, &coord_arr);
		aff_res_chemin(dep, arr, res, "chemin_court");
		res = chemin_aleatoire(lab, &coord_dep, &coord_arr);
		aff_res_chemin(dep, arr, res, "chemin_aleatoire");
		res = chemin_anticipe(lab, &coord_dep, &coord_arr);
		aff_res_chemin(dep, arr, res, "chemin_anticipe");
		res = chemin_fuir(lab, &coord_dep, &coord_arr);
		aff_res_chemin(dep, arr, res, "chemin_fuir");
		printf("\n");
	}
	
	
	return 0;
}
