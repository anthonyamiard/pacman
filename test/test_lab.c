#include <stdio.h>
#include <stdlib.h>

#include "../include/labyrinthe.h"

int main() {
	char labyrinthe[N_LAB][M_LAB];
	int nb_pacgums;
	lab_manuel(labyrinthe, &nb_pacgums);
	
	aff_lab(labyrinthe);
	
	return 0;
}
