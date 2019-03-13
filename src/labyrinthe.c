/*!
 * \file		labyrinthe.c
 * \author		Anthony Amiard
 * \brief		Fonctions permettant de générer un labyrinthe
 * \date		2019
 *
 * Fonctions permettant de générer et afficher un labyrinthe
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/labyrinthe.h"

#define X_DEP 11 /*!< Coordonnée X du point de départ sur un demi-labyrinthe */
#define Y_DEP 23 /*!< Coordonnée Y du point de départ */


/*
 * Fonctions sur le labyrinthe
 */

int genere_lab(char labyrinthe[N_LAB][M_LAB], int * nb_pacgums) {
	int mid = M_LAB / 2;
	/*
	 * Demi-labyrinthe de base avec la boîte, le point de départ et quelques
	 * chemins déjà placés
	 */
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

	/* Génération de chemin aléatoire à partir du point de départ et des deux
	 * coins (deux points de départs par coin) */
	chemin_alea(base, X_DEP, Y_DEP);
	chemin_alea(base, 1, 3);
	chemin_alea(base, 3, 1);
	chemin_alea(base, 1, 27);
	chemin_alea(base, 3, 29);


	int i, j;
	
	/* Débouchage des culs-de-sac */
	for(i = 0; i < N_LAB; i++)
		for(j = 0; j < mid; j++)
			debouche_cds(base, j, i);
	/* Suppression des culs-de-sac */
	for(i = 0; i < N_LAB; i++)
		for(j = 0; j < mid; j++)
			suppr_cds(base, j, i);

	int nb_spg = 0; /* Nombre de super-pacgums */
		
	/* Recopie du demi-labyrinthe dans labyrinthe avec application de la
	 * symétrie, placement des super-pacgums et comptage des pacgums */
	for(i = 0; i < N_LAB; i++) {
		for(j = 0; j < mid; j++) {
			if(base[i][j] == 'p') {
				if(j < 8 && (
						(nb_spg < 4 && !(rand() % 75)) ||
						(!nb_spg && *nb_pacgums > 150) ||
						(nb_spg < 4 && *nb_pacgums > 230)
					)) {
					base[i][j] = 's';
					nb_spg += 2;
				} else {
					*nb_pacgums += 2;
				}
			}
			labyrinthe[i][j] = base[i][j];
			labyrinthe[i][M_LAB - 1 - j] = base[i][j];
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
	
	/* Recopie avec comptage des pacgums */
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

/*
 * Fonctions sur les chemins
 */

int est_chemin(char case_lab) {
	return case_lab == 'c' || case_lab == 'p' || case_lab == 's';
}

void chemin_alea(char demi_lab[N_LAB][M_LAB / 2], int x, int y) {
	if(demi_lab[y][x] == 'm' && place_permise(demi_lab, x, y) == 1) {
		demi_lab[y][x] = 'p';

		/* Cas ou l'on se trouve sur la ligne du milieu. Comme elle sera
		 * répliquée juste a cote, on ne peut pas se déplacer verticalement
		 * dessus sous peine de créer un chemin verticale de deux cases
		 * d’épaisseur. On s'en éloigne donc. */
		if(x == M_LAB / 2 - 1) {
			x--;
		}

		/* x2 et y2 coordonnées de la case voisine à explorer */
		int i = 5, x2, y2;

		/* Génère des coordonnées aléatoires qui ne tombent pas sur un chemin et
		 * ou la place est permise */
		do {
			coord_alea(x, y, &x2, &y2);
		} while(i-- && (!est_chemin(demi_lab[y2][x2]) ||
			place_permise(demi_lab, x2,y2) != 1));

		if(i) { // Si on a trouvé des coordonnées valides

			i = rand() % 9 + 3;

			/* Cas où x2 se trouve sur la ligne du milieu */
			if(x2 == M_LAB / 2 - 1) {
				demi_lab[y2][x2] = 'p';
				x2 -= 2;
			}

			/* Calcule la direction générée par les coordonnées aléatoires */
			int dx = x2 - x;
			int dy = y2 - y;
			
			if(!((!(y % 2) && dx) || (!(x % 2) && dy))) {

				/* Génération d'une ligne droite avec ramifications */
				do {
					if((rand() % 4))
						chemin_alea(demi_lab, x2, y2);
					else if(demi_lab[y2][x2] == 'm' &&
						place_permise(demi_lab, x2, y2)) {
						demi_lab[y2][x2] = 'p';
					}
					x2 += dx;
					y2 += dy;
				} while((i-- || nb_chemins_voisins_demi(demi_lab, x2, y2) <= 1) && (est_chemin(demi_lab[y2][x2]) ||
					place_permise(demi_lab, x2, y2) == 1));
			}
		}
	}
}

int nb_chemins_voisins(const char labyrinthe[N_LAB][M_LAB], int x, int y) {
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

int nb_chemins_voisins_demi(const char demi_lab[N_LAB][M_LAB / 2], int x, int y) {
	int nb = 0;
	if(x > 0 && est_chemin(demi_lab[y][x-1])) {
		nb++;
	}
	if(x < (M_LAB / 2 - 1) && est_chemin(demi_lab[y][x+1])) {
		nb++;
	}
	if(y > 0 && est_chemin(demi_lab[y-1][x])) {
		nb++;
	}
	if(y < (N_LAB - 1) && est_chemin(demi_lab[y+1][x])) {
		nb++;
	}
	if(x == M_LAB / 2 - 1 && est_chemin(demi_lab[y][x]))
		nb++;
	return nb;
}

int place_permise(const char demi_lab[N_LAB][M_LAB / 2], int x, int y) {

	/* Chemin en dehors du labyrinthe */
	if((x < 1) || (x > (M_LAB / 2 - 1)) || (y < 1) || (y > N_LAB - 2))
		return 0;

	/* La case n'est pas déjà un chemin */
	if(est_chemin(demi_lab[y][x]))
		return 0;

	/* La case doit avoir au moins un voisin */
	if(!nb_chemins_voisins_demi(demi_lab, x, y))
		return 2;

	/* Empêcher de créer des blocs de chemins de plusieurs cases d'épaisseur */
	if(est_chemin(demi_lab[y-1][x-1]) && est_chemin(demi_lab[y-1][x]) &&
		est_chemin(demi_lab[y][x-1]))
		return 0;
	if(est_chemin(demi_lab[y-1][x+1]) && est_chemin(demi_lab[y-1][x]) &&
		est_chemin(demi_lab[y][x+1]))
		return 0;
	if(est_chemin(demi_lab[y+1][x-1]) && est_chemin(demi_lab[y][x-1]) &&
		est_chemin(demi_lab[y+1][x]))
		return 0;
	if(est_chemin(demi_lab[y+1][x+1]) && est_chemin(demi_lab[y][x+1]) &&
		est_chemin(demi_lab[y+1][x]))
		return 0;

	/* Éviter les murs d'une case d'épaisseur */
	if(est_chemin(demi_lab[y+1][x]) && !est_chemin(demi_lab[y][x+1]) &&
		!est_chemin(demi_lab[y+1][x+1]) && est_chemin(demi_lab[y][x+2]) &&
		est_chemin(demi_lab[y+1][x+2]))
		return 2;
	if(est_chemin(demi_lab[y-1][x]) && !est_chemin(demi_lab[y][x+1]) &&
		!est_chemin(demi_lab[y-1][x+1]) && est_chemin(demi_lab[y][x+2]) &&
		est_chemin(demi_lab[y-1][x+2]))
		return 2;
	if(est_chemin(demi_lab[y+1][x]) && !est_chemin(demi_lab[y][x-1]) &&
		!est_chemin(demi_lab[y+1][x-1]) && est_chemin(demi_lab[y][x-2]) &&
		est_chemin(demi_lab[y+1][x-2]))
		return 2;
	if(est_chemin(demi_lab[y-1][x]) && !est_chemin(demi_lab[y][x-1]) &&
		!est_chemin(demi_lab[y-1][x-1]) && est_chemin(demi_lab[y][x-2]) &&
		est_chemin(demi_lab[y-1][x-2]))
		return 2;

	if(est_chemin(demi_lab[y][x+1]) && !est_chemin(demi_lab[y+1][x]) &&
		!est_chemin(demi_lab[y+1][x+1]) && est_chemin(demi_lab[y+2][x]) &&
		est_chemin(demi_lab[y+2][x+1]))
		return 2;
	if(est_chemin(demi_lab[y][x-1]) && !est_chemin(demi_lab[y+1][x]) &&
		!est_chemin(demi_lab[y+1][x-1]) && est_chemin(demi_lab[y+2][x]) &&
		est_chemin(demi_lab[y+2][x-1]))
		return 2;
	if(est_chemin(demi_lab[y][x+1]) && !est_chemin(demi_lab[y-1][x]) &&
		!est_chemin(demi_lab[y-1][x+1]) && est_chemin(demi_lab[y-2][x]) &&
		est_chemin(demi_lab[y-2][x+1]))
		return 2;
	if(est_chemin(demi_lab[y][x-1]) && !est_chemin(demi_lab[y-1][x]) &&
		!est_chemin(demi_lab[y-1][x-1]) && est_chemin(demi_lab[y-2][x]) &&
		est_chemin(demi_lab[y-2][x-1]))
		return 2;

	return 1;
}

void debouche_cds(char demi_lab[N_LAB][M_LAB/2], int x, int y) {
	if(est_chemin(demi_lab[y][x]) &&
		nb_chemins_voisins_demi(demi_lab, x, y) <= 1) {

		int i = y, j = x;
		
		for(j = x + 1; j < M_LAB/2 && !est_chemin(demi_lab[y][j]) &&
			place_permise(demi_lab, j, y); j++);
		if(j == M_LAB/2 || (j < M_LAB/2 && est_chemin(demi_lab[y][j])))
			for(j = x + 1; j < M_LAB/2 && !est_chemin(demi_lab[y][j]) &&
				place_permise(demi_lab, j, y); j++)
				demi_lab[y][j] = 'p';
		
		for(j = x - 1; j > 0 && !est_chemin(demi_lab[y][j]) &&
			place_permise(demi_lab, j, y); j--);
		if(j > 0 && est_chemin(demi_lab[y][j]))
			for(j = x - 1; j > 0 && !est_chemin(demi_lab[y][j]) &&
				place_permise(demi_lab, j, y); j--)
				demi_lab[y][j] = 'p';
		
		for(i = y + 1; i < N_LAB && !est_chemin(demi_lab[i][x]) &&
			place_permise(demi_lab, x, i); i++);
		if(i < N_LAB && est_chemin(demi_lab[i][x]))
			for(i = y + 1; i < N_LAB && !est_chemin(demi_lab[i][x]) &&
				place_permise(demi_lab, x, i); i++)
				demi_lab[i][x] = 'p';
		
		for(i = y - 1; i > 0 && !est_chemin(demi_lab[i][x]) &&
			place_permise(demi_lab, x, i); i--);
		if(i > 0 && est_chemin(demi_lab[i][x]))
			for(i = y - 1; i > 0 && !est_chemin(demi_lab[i][x]) &&
				place_permise(demi_lab, x, i); i--)
				demi_lab[i][x] = 'p';
		
	}
}

void suppr_cds(char demi_lab[N_LAB][M_LAB / 2], int x, int y) {
	if((x != X_DEP || y != Y_DEP) && est_chemin(demi_lab[y][x]) &&
		nb_chemins_voisins_demi(demi_lab, x, y) <= 1) {
		demi_lab[y][x] = 'm';
		int x2 = x, y2 = y;
		if(x > 0 && est_chemin(demi_lab[y][x - 1]))
			x2 = x - 1;
		else if(x < M_LAB / 2 - 1 && est_chemin(demi_lab[y][x + 1]))
			x2 = x + 1;
		else if(y > 0 && est_chemin(demi_lab[y - 1][x]))
			y2 = y - 1;
		else if(y < N_LAB - 1 && est_chemin(demi_lab[y + 1][x]))
			y2 = y + 1;
		if(x2 != x || y2 != y)
			suppr_cds(demi_lab, x2, y2);
	}
}
