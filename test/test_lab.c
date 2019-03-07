#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/labyrinthe.h"

int main() {
	srand(time(NULL));
	
	char labyrinthe[N_LAB][M_LAB];
	int nb_pacgums;
	lab_manuel(labyrinthe, &nb_pacgums);
	aff_lab(labyrinthe);
	printf("nb pacgums = %d\n", nb_pacgums);
	
	printf("\n");
		genere_lab(labyrinthe, &nb_pacgums);
		aff_lab(labyrinthe);
		printf("nb pacgums = %d\n", nb_pacgums);
	
	return 0;
}
