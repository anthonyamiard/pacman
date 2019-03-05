#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/IA.h"
#include "../include/labyrinthe.h"
#include "../include/objets.h"

#define N_TESTS 9
#define VITESSE 1

/* Affichage du resultat des fonctions chemin_* */
void aff_res_chemin(coord_t dep, coord_t arr, coord_t res, char * fonction) {
	printf("%s : (%d,%d) -> (%d,%d) : (%d,%d)\n", fonction, dep.x, dep.y, arr.x, arr.y, res.x, res.y);
}

/* Affichage du resultat de la fonction fantome */
void aff_res_fantome(fantome_t * f, int retour) {
	print("Fantome %c : (%d,%d), retour = %d\n", f->couleur, f->coord->x, f->coord->y, retour);
}

int main() {
	srand(time(NULL));
	
	char lab[N_LAB][M_LAB];
	int nb_pacgums;
	lab_manuel(lab, &nb_pacgums);
	
	coord_t dep;
	coord_t arr;
	coord_t res;
	
	int l_dep_x[N_TESTS] = { 3, 24,  6,  6, 12, 15, 10, 10, 6};
	int l_dep_y[N_TESTS] = { 5,  5,  2,  8,  4,  4,  5,  8, 5};
	int l_arr_x[N_TESTS] = {24, 24,  6,  6, 15, 12, 10, 10, 2};
	int l_arr_y[N_TESTS] = { 5,  5,  8,  2,  4,  4,  8,  5, 1};
	int i;
	
	/* Tests fonctions chemin_* */
	
	printf("*\n*Tests des fonctions chemin_*\n*\n");
	
	for(i = 0; i < N_TESTS; i++) {
	
		dep.x = l_dep_x[i];
		dep.y = l_dep_y[i];
		arr.x = l_arr_x[i];
		arr.y = l_arr_y[i];
		
		res = chemin_court(lab, &coord_dep, &coord_arr);
		aff_res_chemin(dep, arr, res, "chemin_court");
		res = chemin_aleatoire(lab, &coord_dep, &coord_arr);
		aff_res_chemin(dep, arr, res, "chemin_aleatoire");
		res = chemin_anticipe(lab, &coord_dep, &coord_arr);
		aff_res_chemin(dep, arr, res, "chemin_anticipe");
		res = chemin_fuir(lab, &coord_dep, &coord_arr);
		aff_res_chemin(dep, arr, res, "chemin_fuir");
		printf("\n");
	}
	
	/* Tests fonctions fantome */
	
	printf("*\n*Tests de la fonction fantome*\n*\n");
	
	fantome_t * f_bleu = malloc(sizeof(fantome_t));
	f_bleu->nom = NULL;
	f_bleu->couleur = 'b';
	f_bleu->chemin = chemin_court;
	f_bleu->etat = POURSUITE;
	f_bleu->coord = malloc(sizeof(coord_t));
	
	fantome_t * f_rouge = malloc(sizeof(fantome_t));
	f_bleu->nom = NULL;
	f_bleu->couleur = 'r';
	f_bleu->chemin = chemin_aleatoire;
	f_bleu->etat = POURSUITE;
	f_bleu->coord = malloc(sizeof(coord_t));
	
	fantome_t * f_rose = malloc(sizeof(fantome_t));
	f_bleu->nom = NULL;
	f_bleu->couleur = 'r';
	f_bleu->chemin = chemin_anticipe;
	f_bleu->etat = POURSUITE;
	f_bleu->coord = malloc(sizeof(coord_t));
	
	fantome_t * f_orange = malloc(sizeof(fantome_t));
	f_bleu->nom = NULL;
	f_bleu->couleur = 'o';
	f_bleu->chemin = chemin_fuir;
	f_bleu->etat = POURSUITE;
	f_bleu->coord = malloc(sizeof(coord_t));
	
	joueur_t * j = malloc(sizeof(joueur_t));
	j->nom = NULL;
	j->vies = 1;
	j->score = 0;
	j->coord = malloc(sizeof(coord_t));
	
	int retour;
	
	for(i = 0; i < N_TESTS; i++) {
		dep.x = l_dep_x[i];
		dep.y = l_dep_y[i];
		arr.x = l_arr_x[i];
		arr.y = l_arr_y[i];
		
		f_bleu->coord->x = dep.x;
		f_bleu->coord->y = dep.y;
		f_rouge->coord->x = dep.x;
		f_rouge->coord->y = dep.y;
		f_orange->coord->x = dep.x;
		f_orange->coord->y = dep.y;
		f_rose->coord->x = dep.x;
		f_rose->coord->y = dep.y;
		j->coord->x = arr.x;
		j->coord->y = arr.y;
		
		printf("Joueur = (%d,%d)\n", j->coord->x, j->coord->y);
		
		retour = fantome(lab, f_bleu, j, VITESSE);
		aff_res_fantome(f_bleu, retour);
		retour = fantome(lab, f_rouge, j, VITESSE);
		aff_res_fantome(f_rouge, retour);
		retour = fantome(lab, f_orange, j, VITESSE);
		aff_res_fantome(f_orange, retour);
		retour = fantome(lab, f_rose, j, VITESSE);
		aff_res_fantome(f_rose, retour);
	
	}
	
	/* Test de la fonction ramasse_pacgum */
	
	printf("*\n*Tests de la fonction ramasse_pacgum\n*\n");
	
	for(i = 0; i < N_TESTS; i++) {
	
		j->coord->x = l_dep_x[i];
		j->coord->y = l_dep_y[i];
		
		ramasse_pacgum(lab, j);
		aff_lab(lab);
		printf("Coordonnees du joueur : (%d,%d), score : %d\n", j->coord->x, j->coord->y, j->score);
		
	}
	
	
	
	free(f_bleu->coord);
	free(f_bleu);
	free(f_rouge->coord);
	free(f_rouge);
	free(f_orange->coord);
	free(f_orange);
	free(f_rose->coord);
	free(f_rose);
	free(j->coord);
	free(j);
	
	
	return 0;
}
