/*
 * Fonctions permettant de generer et afficher un labyrinthe
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/labyrinthe.h"

#define N_RAND 2

void aff_lab(const char labyrinthe[N_LAB][M_LAB]) {
	int i, j;
	printf("y\\x");
	for(j = 0; j < M_LAB; j++) {
		printf("%2d", j);
	}
	printf("\n");
	for(i = 0; i < N_LAB; i++) {
		printf("%2d ", i);
		for(j = 0; j < M_LAB; j++) {
			switch(labyrinthe[i][j]) {
				case 'm': printf("██"); break;
				case 'c': printf("  "); break;
				case 'p': printf("• "); break;
				case 's': printf("● "); break;
				case 'b': printf("▓▓"); break;
				case 'e': printf("▔▔"); break;
				default: printf("XX");
			}
		}
		printf("\n");
	}
}

int est_chemin(char case_lab) {
	return case_lab == 'c' || case_lab == 'p' || case_lab == 's';
}

int nb_voisins(char labyrinthe[N_LAB][M_LAB / 2], int x, int y) {
	int nb = 0;
	if(x > 0 && est_chemin(labyrinthe[y][x-1])) {
		nb++;
	}
	if(x < M_LAB / 2 - 1 && est_chemin(labyrinthe[y][x+1])) {
		nb++;
	}
	if(y > 0 && est_chemin(labyrinthe[y-1][x] == 'c')) {
		nb++;
	}
	if(y < M_LAB / 2 - 1 && est_chemin(labyrinthe[y+1][x])) {
		nb++;
	}
	return nb;
}

int nb_voisins_coins(char labyrinthe[N_LAB][M_LAB / 2], int x, int y) {
	int nb = 0;
	if(x > 0 && est_chemin(labyrinthe[y-1][x-1])) {
		nb++;
	}
	if(x < M_LAB / 2 - 1 && est_chemin(labyrinthe[y+1][x-1])) {
		nb++;
	}
	if(y > 0 && est_chemin(labyrinthe[y-1][x+1] == 'c')) {
		nb++;
	}
	if(y < M_LAB / 2 - 1 && est_chemin(labyrinthe[y+1][x+1])) {
		nb++;
	}
	return nb;
}

int place_permise(char l[N_LAB][M_LAB / 2], int x, int y) {
	if(est_chemin(l[y-1][x-1]) && est_chemin(l[y-1][x]) && est_chemin(l[y][x-1])) {
		return 0;
	}
	if(est_chemin(l[y-1][x]) && est_chemin(l[y-1][x+1]) && est_chemin(l[y][x+1])) {
		return 0;
	}
	if(est_chemin(l[y][x-1]) && est_chemin(l[y+1][x-1]) && est_chemin(l[y+1][x])) {
		return 0;
	}
	if(est_chemin(l[y][x+1]) && est_chemin(l[y+1][x+1]) && est_chemin(l[y+1][x])) {
		return 0;
	}
	return 1;
}

void chemin_alea(char labyrinthe[N_LAB][M_LAB / 2], int x, int y) {
	int mid = M_LAB / 2;
	if(labyrinthe[y][x] == 'm') {
		labyrinthe[y][x] = 'p';
		if(x < mid - 1 && nb_voisins(labyrinthe, x, y) < 4) {
			
			if(nb_voisins(labyrinthe, x, y) <= 1) {
				if(x - 1 > 0 && place_permise(labyrinthe, x - 1, y) &&
				   !(rand() % 4))
					chemin_alea(labyrinthe, x - 1, y);
				else if(y - 1 > 0 && place_permise(labyrinthe, x, y - 1) &&
						!(rand() % 3))
					chemin_alea(labyrinthe, x, y - 1);
				else if(y + 1 < N_LAB - 1 && place_permise(labyrinthe, x, y + 1) &&
						rand() % 2)
					chemin_alea(labyrinthe, x, y + 1);
				else
					chemin_alea(labyrinthe, x + 1, y);
			}
			
			if(x - 1 > 0 && place_permise(labyrinthe, x - 1, y)) {
				if(rand() % N_RAND)
					chemin_alea(labyrinthe, x - 1, y);
			}
			if(y - 1 > 0 && place_permise(labyrinthe, x, y - 1)) {
				if(rand() % N_RAND)
					chemin_alea(labyrinthe, x, y - 1);
			}
			if(y + 1 < N_LAB - 1 && place_permise(labyrinthe, x, y + 1)) {
				if(rand() % N_RAND)
					chemin_alea(labyrinthe, x, y + 1);
			}
			if(rand() % N_RAND && place_permise(labyrinthe, x + 1, y))
				chemin_alea(labyrinthe, x + 1, y);
		}
	}
}

void remplace_p_par_m(char labyrinthe[N_LAB][M_LAB / 2], int x, int y) {
	if(x >= 0 && x < M_LAB / 2 && y >= 0 && y < N_LAB &&
	   labyrinthe[y][x] == 'p') {
		labyrinthe[y][x] = 'm';
	}
	if(x + 1 >= 0 && x + 1 < M_LAB / 2 && y >= 0 && y < N_LAB &&
	   labyrinthe[y][x+1] == 'p') {
		labyrinthe[y][x+1] = 'm';
	}
	if(x >= 0 && x < M_LAB / 2 && y + 1 >= 0 && y + 1 < N_LAB &&
	   labyrinthe[y+1][x] == 'p') {
		labyrinthe[y+1][x] = 'm';
	}
	if(x + 1 >= 0 && x + 1 < M_LAB / 2 && y + 1 >= 0 && y + 1 < N_LAB &&
	   labyrinthe[y+1][x+1] == 'p') {
		labyrinthe[y+1][x+1] = 'm';
	}
}

void mur_alea(char labyrinthe[N_LAB][M_LAB / 2], int x, int y) {
	remplace_p_par_m(labyrinthe, x, y);
}

int genere_lab(char labyrinthe[N_LAB][M_LAB], int * nb_pacgums) {
	int mid = M_LAB / 2;
	char base[N_LAB][M_LAB / 2] = {
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'c', 'c', 'c', 'c', 'c'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'c', 'b', 'b', 'b', 'e'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'c', 'b', 'b', 'b', 'b'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'c', 'b', 'b', 'b', 'b'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'c', 'b', 'b', 'b', 'b'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'c', 'b', 'b', 'b', 'b'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'c', 'c', 'c', 'c', 'c'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'c'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'}
	};
	
	*nb_pacgums = 0;
	
	chemin_alea(base, 12, 23);
	
	int i, j;
	for(i = 0; i < N_LAB; i++) {
		for(j = 0; j < mid; j++) {
			labyrinthe[i][j] = base[i][j];
			labyrinthe[i][M_LAB - 1 - j] = base[i][j];
			if(base[i][j] == 'p')
				*nb_pacgums += 2;
		}
	}
	
	return 0;
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
				(*nb_pacgums)++;
			}
		}
	}
	
	return 0;
}
