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

void aff_lab_coord(const char labyrinthe[N_LAB][M_LAB / 2], int x, int y) {
	int i, j;
	printf("y\\x");
	for(j = 0; j < M_LAB / 2; j++) {
		printf("%2d", j);
	}
	printf("\n");
	for(i = 0; i < N_LAB; i++) {
		printf("%2d ", i);
		for(j = 0; j < M_LAB / 2; j++) {
			if(j == x && i == y) {
				printf("XX");
			} else {
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
		}
		printf("\n");
	}
}

int est_chemin(char case_lab) {
	return case_lab == 'c' || case_lab == 'p' || case_lab == 's';
}

int nb_chemins_voisins(char labyrinthe[N_LAB][M_LAB], int x, int y) {
	int nb = 0;
	if(x > 0 && est_chemin(labyrinthe[y][x-1])) {
		nb++;
	}
	if(x < (M_LAB - 1) && est_chemin(labyrinthe[y][x+1])) {
		nb++;
	}
	if(y > 0 && est_chemin(labyrinthe[y-1][x])) {
		nb++;
	}
	if(y < (N_LAB - 1) && est_chemin(labyrinthe[y+1][x])) {
		nb++;
	}
	return nb;
}

int nb_voisins(char labyrinthe[N_LAB][M_LAB / 2], int x, int y) {
	int nb = 0;
	if(x > 0 && est_chemin(labyrinthe[y][x-1])) {
		nb++;
	}
	if(x < (M_LAB / 2 - 1) && est_chemin(labyrinthe[y][x+1])) {
		nb++;
	}
	if(y > 0 && est_chemin(labyrinthe[y-1][x])) {
		nb++;
	}
	if(y < (N_LAB - 1) && est_chemin(labyrinthe[y+1][x])) {
		nb++;
	}
	if(x == M_LAB / 2 - 1)
		nb++;
	return nb;
}

int place_permise(const char l[N_LAB][M_LAB / 2], int x, int y) {
	if((x < 1) || (x > (M_LAB / 2 - 1)) || (y < 1) || (y > N_LAB - 2)) {
		return 0;
	}
	if(est_chemin(l[y][x]))
		return 0;
	
	if(est_chemin(l[y-1][x-1]) && est_chemin(l[y-1][x]) && est_chemin(l[y][x-1])) {
		return 0;
	}
	if(est_chemin(l[y-1][x+1]) && est_chemin(l[y-1][x]) && est_chemin(l[y][x+1])) {
		return 0;
	}
	if(est_chemin(l[y+1][x-1]) && est_chemin(l[y][x-1]) && est_chemin(l[y+1][x])) {
		return 0;
	}
	if(est_chemin(l[y+1][x+1]) && est_chemin(l[y][x+1]) && est_chemin(l[y+1][x])) {
		return 0;
	}
	/*
	if(est_chemin(l[y-1][x-1]) && !est_chemin(l[y-1][x]) && !est_chemin(l[y][x-1])) {
		return 0;
	}
	if(est_chemin(l[y-1][x+1]) && !est_chemin(l[y-1][x]) && !est_chemin(l[y][x+1])) {
		return 0;
	}
	if(est_chemin(l[y+1][x-1]) && !est_chemin(l[y][x-1]) && !est_chemin(l[y+1][x])) {
		return 0;
	}
	if(est_chemin(l[y+1][x+1]) && !est_chemin(l[y][x+1]) && !est_chemin(l[y+1][x])) {
		return 0;
	}
	*/
	return 1;
}

void aff_lab_permis(const char labyrinthe[N_LAB][M_LAB / 2]) {
	int i, j;
	printf("y\\x");
	for(j = 0; j < M_LAB / 2; j++) {
		printf("%2d", j);
	}
	printf("\n");
	for(i = 0; i < N_LAB; i++) {
		printf("%2d ", i);
		for(j = 0; j < M_LAB / 2; j++) {
			if(place_permise(labyrinthe, j, i)) {
				printf(" O");
			} else {
				printf(" N");
			}
		}
		printf("\n");
	}
}

void aff_lab_voisins(const char labyrinthe[N_LAB][M_LAB / 2]) {
	int i, j;
	printf("y\\x");
	for(j = 0; j < M_LAB / 2; j++) {
		printf("%2d", j);
	}
	printf("\n");
	for(i = 0; i < N_LAB; i++) {
		printf("%2d ", i);
		for(j = 0; j < M_LAB / 2; j++) {
			if(est_chemin(labyrinthe[i][j])) {
				printf("%2d", nb_voisins(labyrinthe, j, i));
			} else {
				
				switch(labyrinthe[i][j]) {
					case 'm': printf("██"); break;
					case 'b': printf("▓▓"); break;
					case 'e': printf("▔▔"); break;
					default: printf("XX");
				}
			}
		}
		printf("\n");
	}
}

void coord_alea(int x, int y, int * x2, int * y2) {
	*x2 = x;
	*y2 = y;
	
	if(!(rand() % 4))
		*x2 = x - 1;
	else if(!(rand() % 3))
		*x2 = x + 1;
	else if(rand() % 2)
		*y2 = y - 1;
	else
		*y2 = y + 1;
}

void chemin_alea(char lab[N_LAB][M_LAB / 2], int x, int y) {
	if(lab[y][x] == 'm' && place_permise(lab, x, y)) {
		lab[y][x] = 'p';
		if(x == M_LAB / 2 - 1) {
			x--;
		}
		
		aff_lab_coord(lab, x, y);
		
		int i = 50, x2, y2;
		
		do {
			coord_alea(x, y, &x2, &y2);
		} while(i-- && (!est_chemin(lab[y2][x2]) || !place_permise(lab, x2, y2)));
		
		if(i) {
			
			if(x2 == M_LAB / 2 - 1) {
				lab[y2][x2] = 'p';
				x2--;
			}
		
			i = rand() % 12;
			
			int dx = x2 - x;
			int dy = y2 - y;
			
			if((!(y % 2) && dx) || (!(x % 2) && dy)) {
			
			} else {
			
				do {
					chemin_alea(lab, x2, y2);
					x2 += dx;
					y2 += dy;
				} while(i-- && (est_chemin(lab[y2][x2]) || place_permise(lab, x2, y2)));
			}
		} else {
			aff_lab_coord(lab, x, y);
			printf("%d, %d pas de chemin trouvé\n", x, y);
		}
	} else {
		aff_lab_coord(lab, x, y);
		printf("%d, %d place interdite\n", x, y);
	}
}

void suppr_cds(char lab[N_LAB][M_LAB / 2]) {
	int i, j;
	for(i = 0; i < N_LAB; i++) {
		for(j = 0; j < M_LAB / 2 - 1; j++) {
			if(est_chemin(lab[i][j]) && nb_voisins(lab, j, i) <= 1) {
				lab[i][j] = 'm';
			}
		}
	}
}

int genere_lab(char labyrinthe[N_LAB][M_LAB], int * nb_pacgums) {
	int mid = M_LAB / 2;
	char base[N_LAB][M_LAB / 2] = {
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'p', 'p', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'p', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
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
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'p', 'c'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'p', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'p', 'p', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'}
	};
	
	*nb_pacgums = 0;
	
	chemin_alea(base, 11, 23);
	chemin_alea(base, 1, 3);
	chemin_alea(base, 3, 1);
	chemin_alea(base, 1, 27);
	chemin_alea(base, 3, 29);
	
	aff_lab_voisins(base);
	aff_lab_coord(base, 0, 0);
	
	int i, j;
	
	for(i = 0; i < N_LAB; i++)
		for(j = 0; j < mid; j++)
			suppr_cds(base);
	
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
		{'m', 'p', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'm', 'c', 'm', 'm', 'c', 'm', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'p', 'm'},
		{'m', 'p', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'm', 'c', 'm', 'm', 'c', 'm', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'p', 'm'},
		{'m', 'p', 'p', 'p', 'p', 'p', 'p', 'm', 'm', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'm', 'm', 'p', 'p', 'p', 'p', 'p', 'p', 'm'},
		{'m', 'p', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'c', 'b', 'b', 'b', 'e', 'e', 'b', 'b', 'b', 'c', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'p', 'm'},
		{'m', 'p', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'c', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'c', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'p', 'm'},
		{'m', 'p', 'p', 'p', 'p', 'p', 'p', 'c', 'c', 'c', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'c', 'c', 'c', 'p', 'p', 'p', 'p', 'p', 'p', 'm'},
		{'m', 'p', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'c', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'c', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'p', 'm'},
		{'m', 'p', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'c', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'c', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'p', 'm'},
		{'m', 'p', 'p', 'p', 'p', 'p', 'p', 'm', 'm', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'm', 'm', 'p', 'p', 'p', 'p', 'p', 'p', 'm'},
		{'m', 'p', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'c', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'c', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'p', 'm'},
		{'m', 'p', 'm', 'm', 'm', 'm', 'p', 'm', 'm', 'c', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'c', 'm', 'm', 'p', 'm', 'm', 'm', 'm', 'p', 'm'},
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
