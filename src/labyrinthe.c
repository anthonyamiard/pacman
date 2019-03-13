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
	int xe, ye;

	/* Épaississement des murs ne faisant qu'une case */
	/*
	for(i = 1; i < N_LAB; i++) {
		for(j = 1; j < mid; j++) {
			if(epaisseur_mur(base, j, i, &xe, &ye) == 0) {
				if(xe == 1)
					epaissir_mur_x(base, j, i);
				if(ye == 1)
					epaissir_mur_y(base, j, i);
			}
		}
	}*/
	for(i = 0; i < N_LAB; i++)
		for(j = 0; j < mid; j++)
			debouche_cds(base, j, i);
	/* Suppression des culs-de-sac */
	for(i = 0; i < N_LAB; i++)
		for(j = 0; j < mid; j++)
			suppr_cds(base, j, i);


	/* Recopie du demi-labyrinthe dans labyrinthe avec application de la
	 * symétrie et comptage des pacgums */
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
	if(demi_lab[y][x] == 'm' && place_permise(demi_lab, x, y)) {
		demi_lab[y][x] = 'p';

		/* Cas ou l'on se trouve sur la ligne du milieu. Comme elle sera
		   repliquee juste a cote, on ne peut pas se deplacer verticalement
		   dessus sous peine de creer un chemin verticalde deux cases
		   d'epaisseur. On s'en éloigne donc. */
		if(x == M_LAB / 2 - 1) {
			x--;
		}

		/* x2 et y2 coordonnees de la case voisine a explorer */
		int i = 5, x2, y2;

		i = rand() % 9 + 3;

		/* Genere des coordonnees aleatoires qui ne tombent pas sur un chemin et
		   ou la place est permise */
		do {
			coord_alea(x, y, &x2, &y2);
		} while(i-- && (!est_chemin(demi_lab[y2][x2]) ||
			!place_permise(demi_lab, x2,y2)));

		if(i) { // Si on a trouve des coordonnees valides

			i = rand() % 9 + 3;

			/* Cas ou x2 se trouve sur la ligne du milieu */
			if(x2 == M_LAB / 2 - 1) {
				demi_lab[y2][x2] = 'p';
				x2 -= 2;
			}

			/* Calcule la direction generee par les coordonnees aleatoires */
			int dx = x2 - x;
			int dy = y2 - y;
/*
			if((y2 == 1 && dy < 0) || (y2 == N_LAB - 2 && dy > 0)) {
				dy = 0;
				if(rand() % 2)
					dx = -1;
				else
					dx = 1;
			}
			if((x2 == 1 && dx < 0) || (x2 == M_LAB/2 - 2 && dx > 0)) {
				dx = 0;
				if(rand() % 2)
					dy = -1;
				else
					dy = 1;
			}
*/
			if(!((!(y % 2) && dx) || (!(x % 2) && dy))) {

				do {
				//	if((rand() % 3))
						chemin_alea(demi_lab, x2, y2);
				//	else if(demi_lab[y2][x2] == 'm' &&
				//		place_permise(demi_lab, x2, y2)) {
				//		demi_lab[y2][x2] = 'p';
				//	}
					x2 += dx;
					y2 += dy;
				} while((i-- || nb_chemins_voisins_demi(demi_lab, x2, y2) <= 1) && (est_chemin(demi_lab[y2][x2]) ||
					place_permise(demi_lab, x2, y2)));
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
		return 0;

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

	int ret_rand = 0;
	/* Éviter les murs d'une case d'épaisseur */
	if(est_chemin(demi_lab[y+1][x]) && est_chemin(demi_lab[y][x+2]) && est_chemin(demi_lab[y+1][x+2]))
		return ret_rand;
	if(est_chemin(demi_lab[y-1][x]) && est_chemin(demi_lab[y][x+2]) && est_chemin(demi_lab[y-1][x+2]))
		return ret_rand;
	if(est_chemin(demi_lab[y+1][x]) && est_chemin(demi_lab[y][x-2]) && est_chemin(demi_lab[y+1][x-2]))
		return ret_rand;
	if(est_chemin(demi_lab[y-1][x]) && est_chemin(demi_lab[y][x-2]) && est_chemin(demi_lab[y-1][x-2]))
		return ret_rand;

	if(est_chemin(demi_lab[y][x+1]) && est_chemin(demi_lab[y+2][x]) && est_chemin(demi_lab[y+2][x+1]))
		return ret_rand;
	if(est_chemin(demi_lab[y][x-1]) && est_chemin(demi_lab[y+2][x]) && est_chemin(demi_lab[y+2][x-1]))
		return ret_rand;
	if(est_chemin(demi_lab[y][x+1]) && est_chemin(demi_lab[y-2][x]) && est_chemin(demi_lab[y-2][x+1]))
		return ret_rand;
	if(est_chemin(demi_lab[y][x-1]) && est_chemin(demi_lab[y-2][x]) && est_chemin(demi_lab[y-2][x-1]))
		return ret_rand;

	return 1;
}

void debouche_cds(char demi_lab[N_LAB][M_LAB/2], int x, int y) {
	if(est_chemin(demi_lab[y][x]) && nb_chemins_voisins_demi(demi_lab, x, y) <= 1) {
		if(x > 2 && est_chemin(demi_lab[y][x-2]) && place_permise(demi_lab, x-1, y))
			demi_lab[y][x-1] = 'p';
		if(x < M_LAB/2 - 3 && est_chemin(demi_lab[y][x+2]) && place_permise(demi_lab, x+1, y))
			demi_lab[y][x+1] = 'p';
		if(y > 2 && est_chemin(demi_lab[y-2][x]) && place_permise(demi_lab, x, y-1))
			demi_lab[y-1][x] = 'p';
		if(y < N_LAB - 3 && est_chemin(demi_lab[y+2][x]) && place_permise(demi_lab, x, y+1))
			demi_lab[y+1][x] = 'p';
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

/*
 * Fonctions sur les murs
 */

int epaisseur_mur(const char demi_lab[N_LAB][M_LAB / 2], int x, int y, int * xe,
				  int * ye) {
	*xe = 0;
	*ye = 0;
	if(demi_lab[y][x] == 'm') {
		int i, j;
		for(i = y; i > 0 && demi_lab[i][x] == 'm'; i--);
		if(demi_lab[i][x] != 'm')
			i++;
		for(; i < N_LAB && demi_lab[i][x] == 'm'; i++)
			(*ye)++;
		for(j = x; j > 0 && demi_lab[y][j] == 'm'; j--);
		if(demi_lab[y][j] != 'm')
			j++;
		for(; j < M_LAB / 2 && demi_lab[y][j] == 'm'; j++)
			(*xe)++;
		return 0;
	} else {
		return 1;
	}
}

int epaissir_mur_x(char demi_lab[N_LAB][M_LAB / 2], int x, int y) {
	if(demi_lab[y][x] == 'm') {
		int i, j, hauteur = 0;
		for(i = y; i > 0 && demi_lab[i][x] == 'm'; i--);
		if(demi_lab[i][x] != 'm')
			i++;
		for(; i < N_LAB && demi_lab[i][x] == 'm'; i++)
			hauteur++;
		for(j = x; j < M_LAB / 2 && demi_lab[y][j] == 'm'; j++);
		int dep = i - hauteur;
		for(i = dep; i < dep + hauteur; i++)
			if(demi_lab[i][j] == 'p')
				demi_lab[i][j] = 'm';
		return 0;
	} else {
		return 1;
	}
}

int epaissir_mur_y(char demi_lab[N_LAB][M_LAB / 2], int x, int y) {
	if(demi_lab[y][x] == 'm') {
		int i, j, largeur = 0;
		for(j = x; j > 0 && demi_lab[y][j] == 'm'; j--);
		if(demi_lab[y][j] != 'm')
			j++;
		for(; j < M_LAB / 2 && demi_lab[y][j] == 'm'; j++)
			largeur++;
		for(i = y; i < N_LAB && demi_lab[i][x] == 'm'; i++);
		int dep = j - largeur;
		for(j = dep; j < dep + largeur; j++)
			if(demi_lab[i][j] == 'p')
				demi_lab[i][j] = 'm';
		return 0;
	} else {
		return 1;
	}
}
