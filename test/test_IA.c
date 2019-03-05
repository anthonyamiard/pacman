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
	coord_dep.x = 13;
	coord_arr.x = 14;
	
	
	return 0;
}
