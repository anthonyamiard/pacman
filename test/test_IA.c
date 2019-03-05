#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/IA.h"
#include "../include/labyrinthe.h"
#include "../include/objets.h"

int main() {
	srand(time(NULL));
	
	char lab[N_LAB][M_LAB];
	int nb_pacgums;
	lab_manuel(lab, &nb_pacgums);
	
	coord_t coord_dep;
	coord_t coord_arr;
	
	/* Tests fonction chemin_court */
	
	/* depart = (3,5), arrivee = (24,5) */
	coord_dep.x = 3;
	coord_arr.x = 5;
	
	
	
	
	return 0;
}
