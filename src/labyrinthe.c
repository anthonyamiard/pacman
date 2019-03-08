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

/* Renvoie le nombre de chemins voisins d'une case */
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

/* Pareil pour un demin-labyrinthe */
int nb_chemins_voisins_demi(char labyrinthe[N_LAB][M_LAB / 2], int x, int y) {
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

/* Renvoie vrai si on peut generer une case chemin aux coordonnees (x,y), faux
   sinon */
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
				printf("%2d", nb_chemins_voisins_demi(labyrinthe, j, i));
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

/* Renvoie des coordonnees voisines aleatoires pour x, y dans x2 et y2 */
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

/* Se deplace sur le demi-labyrinthe de cases en cases de maniere aleatoire et
   recursive et transforme les murs en chemins avec pacgum */
void chemin_alea(char lab[N_LAB][M_LAB / 2], int x, int y) {
	if(lab[y][x] == 'm' && place_permise(lab, x, y)) {
		lab[y][x] = 'p';
		
		/* Cas ou l'on se trouve sur la ligne du milieu. Comme elle sera
		   repliquee juste a cote, on ne peut pas se deplacer verticalement
		   dessus sous peine de creer un chemin verticalde deux cases
		   d'epaisseur */
		if(x == M_LAB / 2 - 1) {
			x--;
		}
		
		/* x2 et y2 coordonnees de la case voisine a explorer */ 
		int i = 5, x2, y2;
		
		/* Genere des coordonnees aleatoires qui ne tombent pas sur un chemin et
		   ou la place est permise */
		do {
			coord_alea(x, y, &x2, &y2);
		} while(i-- && (!est_chemin(lab[y2][x2]) || !place_permise(lab, x2, y2)));
		
		if(i) { // Si on a trouve des coordonnees valides
			
			/* Cas ou x2 se trouve sur la ligne du milieu */
			if(x2 == M_LAB / 2 - 1) {
				lab[y2][x2] = 'p';
				x2--;
			}
			
			i = rand() % 9 + 3;
			
			/* Calcule la direction generee par les coordonnees aleatoires */
			int dx = x2 - x;
			int dy = y2 - y;
			
			if(!((!(y % 2) && dx) || (!(x % 2) && dy))) {
			
				do {
					if((rand() % 3))
						chemin_alea(lab, x2, y2);
					else if(lab[y2][x2] == 'm' && place_permise(lab, x2, y2)) {
						lab[y2][x2] = 'p';
					}
					x2 += dx;
					y2 += dy;
				} while(i-- && (est_chemin(lab[y2][x2]) || place_permise(lab, x2, y2)));
			}
		}
	}
}

void suppr_cds(char lab[N_LAB][M_LAB / 2], int x, int y) {
	if(est_chemin(lab[y][x]) && nb_chemins_voisins_demi(lab, x, y) <= 1) {
		lab[y][x] = 'm';
		int x2 = x, y2 = y;
		if(est_chemin(lab[y][x - 1]))
			x2 = x - 1;
		else if(est_chemin(lab[y][x + 1]))
			x2 = x + 2;
		else if(est_chemin(lab[y - 1][x]))
			y2 = y - 1;
		else if(est_chemin(lab[y + 1][x]))
			y2 = y + 1;
		if(x2 != x || y2 != y)
			suppr_cds(lab, x2, y2);
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
		
	
	int i, j;
	int xe, ye;
	
	for(i = 1; i < N_LAB; i++) {
		for(j = 1; j < mid; j++) {
			if(epaisseur_mur(base, j, i, &xe, &ye) == 0) {
				if(xe == 1)
					epaissir_mur_x(base, j, i);
				if(ye == 1)
					epaissir_mur_y(base, j, i);
			}
		}
	}
	
	for(i = 0; i < N_LAB; i++)
		for(j = 0; j < mid; j++)
			suppr_cds(base, j, i);
	
	for(i = 0; i < N_LAB; i++) {
		for(j = 0; j < mid; j++) {
			labyrinthe[i][j] = base[i][j];
			labyrinthe[i][M_LAB - 1 - j] = base[i][j];
			if(base[i][j] == 'p')
				*nb_pacgums += 2;
		}
	}
	
	if(*nb_pacgums < 270 || *nb_pacgums > 350)
		genere_lab(labyrinthe, nb_pacgums);
	
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

/* Ecrit l'epaisseur xe et ye d'un mur en x, y
   Renvoie 0 s'il n'y a pas d'erreur, 1 si la case selectionnee de correspond
   pas a un mur */
int epaisseur_mur(const char l[N_LAB][M_LAB / 2], int x, int y, int * xe, int * ye) {
	*xe = 0;
	*ye = 0;
	if(l[y][x] == 'm') {
		int i, j;
		for(i = y; i > 0 && l[i][x] == 'm'; i--);
		if(l[i][x] != 'm')
			i++;
		for(; i < N_LAB && l[i][x] == 'm'; i++)
			(*ye)++;
		for(j = x; j > 0 && l[y][j] == 'm'; j--);
		if(l[y][j] != 'm')
			j++;
		for(; j < M_LAB / 2 && l[y][j] == 'm'; j++)
			(*xe)++;
		return 0;
	} else {
		return 1;
	}
}

/* Epaissit le mur en x, y d'une case de largeur
   Renvoie 0 s'il n'y a pas d'erreur, 1 si la case selectionnee ne correspond
   pas a un mur */
int epaissir_mur_x(char l[N_LAB][M_LAB / 2], int x, int y) {
	if(l[y][x] == 'm') {
		int i, j, hauteur = 0;
		for(i = y; i > 0 && l[i][x] == 'm'; i--);
		if(l[i][x] != 'm')
			i++;
		for(; i < N_LAB && l[i][x] == 'm'; i++)
			hauteur++;
		for(j = x; j < M_LAB / 2 && l[y][j] == 'm'; j++);
		int dep = i - hauteur;
		for(i = dep; i < dep + hauteur; i++)
			if(l[i][j] == 'p')
				l[i][j] = 'm';
		return 0;
	} else {
		return 1;
	}
}

/* Epaissit le mur en x, y d'une case de hauteur
   Renvoie 0 s'il n'y a pas d'erreur, 1 si la case selectionnee ne correspond
   pas a un mur */
int epaissir_mur_y(char l[N_LAB][M_LAB / 2], int x, int y) {
	if(l[y][x] == 'm') {
		int i, j, largeur = 0;
		for(j = x; j > 0 && l[y][j] == 'm'; j--);
		if(l[y][j] != 'm')
			j++;
		for(; j < M_LAB / 2 && l[y][j] == 'm'; j++)
			largeur++;
		for(i = y; i < N_LAB && l[i][x] == 'm'; i++);
		int dep = j - largeur;
		for(j = dep; j < dep + largeur; j++)
			if(l[i][j] == 'p')
				l[i][j] = 'm';
		return 0;
	} else {
		return 1;
	}
}
