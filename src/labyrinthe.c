/*
 * Fonctions permettant de generer et afficher un labyrinthe
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/labyrinthe.h"

void aff_lab(const char labyrinthe[N_LAB][M_LAB]) {
	int i, j;
	for(i = 0; i < N_LAB; i++) {
		for(j = 0; j < M_LAB; j++) {
			switch(labyrinthe[i][j]) {
				case 'm': printf("██"); break;
				case 'c': printf("  "); break;
				case 'p': printf("• "); break;
				case 's': printf("● "); break;
				case 'b': printf("▓▓"); break;
				case 'e': printf("▔▔"); break;
				default: printf("  ");
			}
		}
		printf("\n");
	}
}

int lab_manuel(char labyrinthe[N_LAB][M_LAB], int * nb_pacgums) {
	char lab_def[N_LAB][M_LAB] = {
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'm', 'm', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'm'},
		{'m', 'p', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'p', 'm'},
		{'m', 's', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 's', 'm'},
		{'m', 'p', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'p', 'm'},
		{'m', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'm'},
		{'m', 'p', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'p', 'm'},
		{'m', 'p', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'p', 'm'},
		{'m', 'p', 'p', 'p', 'p', 'p', 'p', 'm', 'm', 'p', 'p', 'p', 'p', 'm', 'm', 'p', 'p', 'p', 'p', 'm', 'm', 'p', 'p', 'p', 'p', 'p', 'p', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'm', 'c', 'm', 'm', 'c', 'm', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'c', 'c', 'c', 'c', 'c', 'm', 'p', 'm', 'm', 'm', 'm', 'm', 'c', 'm', 'm', 'c', 'm', 'm', 'm', 'm', 'm', 'p', 'm', 'c', 'c', 'c', 'c', 'c'},
		{'c', 'c', 'c', 'c', 'c', 'm', 'p', 'm', 'm', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'm', 'm', 'p', 'm', 'c', 'c', 'c', 'c', 'c'},
		{'c', 'c', 'c', 'c', 'c', 'm', 'p', 'm', 'm', 'c', 'b', 'b', 'b', 'e', 'e', 'b', 'b', 'b', 'c', 'm', 'm', 'p', 'm', 'c', 'c', 'c', 'c', 'c'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'c', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'c', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'c', 'c', 'c', 'c', 'c', 'c', 'p', 'c', 'c', 'c', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'c', 'c', 'c', 'p', 'c', 'c', 'c', 'c', 'c', 'c'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'c', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'c', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'c', 'c', 'c', 'c', 'c', 'm', 'p', 'm', 'm', 'c', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'c', 'm', 'm', 'p', 'm', 'c', 'c', 'c', 'c', 'c'},
		{'c', 'c', 'c', 'c', 'c', 'm', 'p', 'm', 'm', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'm', 'm', 'p', 'm', 'c', 'c', 'c', 'c', 'c'},
		{'c', 'c', 'c', 'c', 'c', 'm', 'p', 'm', 'm', 'c', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'c', 'm', 'm', 'p', 'm', 'c', 'c', 'c', 'c', 'c'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'c', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'c', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'm', 'm', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'm'},
		{'m', 'p', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'p', 'm'},
		{'m', 'p', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'p', 'm'},
		{'m', 's', 'p', 'p', 'm', 'm', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'c', 'c', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'm', 'm', 'p', 'p', 's', 'm'},
		{'m', 'm', 'm', 'p', 'm', 'm', 'p', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'p', 'm', 'm', 'p', 'm', 'm', 'm'},
		{'m', 'm', 'm', 'p', 'm', 'm', 'p', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'p', 'm', 'm', 'p', 'm', 'm', 'm'},
		{'m', 'p', 'p', 'p', 'p', 'p', 'p', 'm', 'm', 'p', 'p', 'p', 'p', 'm', 'm', 'p', 'p', 'p', 'p', 'm', 'm', 'p', 'p', 'p', 'p', 'p', 'p', 'm'},
		{'m', 'p', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'p', 'm'},
		{'m', 'p', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'p', 'm'},
		{'m', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'}
	};
	int i, j;
	*nb_pacgums = 0;
	for(i = 0; i < N_LAB; i++) {
		for(j = 0; j < M_LAB; j++) {
			labyrinthe[i][j] = lab_def[i][j];
			if(lab_def[i][j] == 'p') {
				*nb_pacgums++;
			}
		}
	}
	
	return 0;
}
