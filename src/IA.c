/*
* Fonctions permettant de gerer l'intelligence artificielle
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../include/IA.h"
#include "../include/objets.h"
#include "../include/labyrinthe.h"
#include "../gui/gui_lab.h"

#define SCORE_PACGUM 10
#define FAUX 0
#define VRAI 1

coord_t chemin_court(char labyrinthe[N_LAB][M_LAB], coord_t* coord_dep, coord_t* coord_arr) {
  int i,j;
  int trouve = FAUX;
  int nb_courant = 1;
  int lab_numero[N_LAB][M_LAB] = {0};
  lab_numero[coord_dep->y][coord_dep->x] = 1;
    for(i = 0;i<N_LAB && !trouve;i++){
      for(j = 0;j<M_LAB && !trouve;j++){
                        if (lab_numero[i][j] > 0){
                            if(i-1>=0){
              if(i > 0 && est_chemin(labyrinthe[i-1][j])){
                                  if(lab_numero[i-1][j] == 0)
                                      lab_numero[i-1][j] = lab_numero[i][j] + 1;
              }
                            }
                            if(j-1>=0){
              if(j > 0 && est_chemin(labyrinthe[i][j-1])){
                                  if(lab_numero[i][j-1] == 0)
                                      lab_numero[i][j-1] = lab_numero[i][j] +1;
              }
                            }
                            if(i+1>=0){
              if(i < N_LAB - 1 && est_chemin(labyrinthe[i+1][j])){
                                  if(lab_numero[i+1][j] == 0)
                                      lab_numero[i+1][j] = lab_numero[i][j] +1;
              }
                            }
                            if(j+1>=0){
              if(i < M_LAB - 1 && est_chemin(labyrinthe[i][j+1])){
                                  if(lab_numero[i][j+1] == 0)
                                      lab_numero[i][j+1] = lab_numero[i][j] +1;
              }
                            }
                            if(lab_numero[i][j] > 0 && coord_arr->y == i && coord_arr->x == j)
                                trouve = VRAI;
                        }
      }
    }
    for(i = N_LAB - 1;i>=0 && !trouve;i--){
      for(j = M_LAB - 1;j>=0 && !trouve;j--){
                        if (lab_numero[i][j] > 0){
                            if(i-1>=0){
              if(i > 0 && est_chemin(labyrinthe[i-1][j])){
                                  if(lab_numero[i-1][j] == 0)
                                      lab_numero[i-1][j] = lab_numero[i][j] + 1;
              }
                            }
                            if(j-1>=0){
              if(j > 0 && est_chemin(labyrinthe[i][j-1])){
                                  if(lab_numero[i][j-1] == 0)
                                      lab_numero[i][j-1] = lab_numero[i][j] +1;
              }
                            }
                            if(i+1>=0){
              if(i < N_LAB - 1 && est_chemin(labyrinthe[i+1][j])){
                                  if(lab_numero[i+1][j] == 0)
                                      lab_numero[i+1][j] = lab_numero[i][j] +1;
              }
                            }
                            if(j+1>=0){
              if(i < M_LAB - 1 && est_chemin(labyrinthe[i][j+1])){
                                  if(lab_numero[i][j+1] == 0)
                                      lab_numero[i][j+1] = lab_numero[i][j] +1;
              }
                            }
                            if(lab_numero[i][j] > 0 && coord_arr->y == i && coord_arr->x == j)
                                trouve = VRAI;
                        }
      }
    }
  coord_t retour;
  i = coord_arr->y;
  j = coord_arr->x;
  retour.x = j;
  retour.y = i;

  nb_courant = lab_numero[coord_arr->y][coord_arr->x];
  while(!((j == coord_dep->x && (i >= coord_dep->y-1 && i <= coord_dep->y+1)) || (i == coord_dep->y && (j >= coord_dep->x-1 && j <= coord_dep->x+1)))){
    if(i - 1 >= 0 && lab_numero [i-1][j] > 0){
      retour.y = i - 1;
      retour.x = j;
      nb_courant = lab_numero[i-1][j];
    }else{
      nb_courant = INT_MAX;
    }
    if(i + 1 <= N_LAB - 1 && lab_numero[i+1][j] < nb_courant && lab_numero [i+1][j] > 0){
      retour.y = i + 1;
      retour.x = j;
      nb_courant = lab_numero[i+1][j];
    }
    if(j - 1 >= 0 && lab_numero[i][j-1] < nb_courant && lab_numero [i][j-1] > 0){
      retour.y = i;
      retour.x = j - 1;
      nb_courant = lab_numero[i][j-1];
    }
    if(j + 1 <= M_LAB - 1 && lab_numero[i][j+1] < nb_courant && lab_numero [i][j+1] > 0){
      retour.y = i;
      retour.x = j + 1;
      nb_courant = lab_numero[i][j+1];
    }
    i = retour.y;
    j = retour.x;
  }
  return retour;
}

coord_t chemin_anticipe(char labyrinthe[N_LAB][M_LAB], coord_t* coord_dep, coord_t* coord_arr) {
  coord_t arr = *coord_arr;
  if(pacdir == 'h')
    while(arr.y > 0 && est_chemin(labyrinthe[arr.y+1][arr.x]))
      (arr.y)--;
  else if(pacdir == 'b')
    while(arr.y + 1 < N_LAB && est_chemin(labyrinthe[arr.y-1][arr.x]))
      (arr.y)++;
  else if(pacdir == 'g')
    while(arr.x > 0 && est_chemin(labyrinthe[arr.y][arr.x-1]))
      (arr.x)--;
  else if(pacdir == 'd')
    while(arr.x + 1 < M_LAB && est_chemin(labyrinthe[arr.y][arr.x+1]))
      (arr.x)++;
  return chemin_court(labyrinthe, coord_dep, &arr);
}

coord_t chemin_fuir(char labyrinthe[N_LAB][M_LAB], coord_t* coord_dep, coord_t* coord_arr) {
  coord_t arr = *coord_arr;
  if(pacdir == 'b')
    while(arr.y > 0 && est_chemin(labyrinthe[arr.y+1][arr.x]))
      (arr.y)--;
  else if(pacdir == 'h')
    while(arr.y + 1 < N_LAB && est_chemin(labyrinthe[arr.y-1][arr.x]))
      (arr.y)++;
  else if(pacdir == 'd')
    while(arr.x > 0 && est_chemin(labyrinthe[arr.y][arr.x-1]))
      (arr.x)--;
  else if(pacdir == 'g')
    while(arr.x + 1 < M_LAB && est_chemin(labyrinthe[arr.y][arr.x+1]))
      (arr.x)++;
  return chemin_court(labyrinthe, coord_dep, &arr);
}

coord_t chemin_aleatoire(char labyrinthe[N_LAB][M_LAB], coord_t* coord_dep, coord_t* coord_arr) {

  int x,y;
  coord_t res;

  x = coord_dep->x;
  y = coord_dep->y;

  do{
    coord_alea(x ,y ,&(res.x) ,&(res.y));
  }while(!est_chemin(labyrinthe[res.y][res.x]));

  return res;
}

void conv_coord_fantome(fantome_t * fantome) {
	if(fantome != NULL) {
		fantome->coord->x = fantome->coord_fines->x / TAILLE_CASE;
		fantome->coord->y = fantome->coord_fines->y / TAILLE_CASE;
	}
}

void conv_coord_joueur(joueur_t * joueur) {
	if(joueur != NULL) {
		joueur->coord->x = joueur->coord_fines->x / TAILLE_CASE;
		joueur->coord->y = joueur->coord_fines->y / TAILLE_CASE;
	}
}

int fantome(char labyrinthe[N_LAB][M_LAB], fantome_t* fantome, joueur_t* joueur, int vitesse) {
  coord_t temp;
  temp  = fantome->chemin(labyrinthe,fantome->coord,joueur->coord);
  int dx = temp.x - fantome->coord->x;
  int dy = temp.y - fantome->coord->y;
  fantome->coord_fines->x += dx * vitesse;
  fantome->coord_fines->y += dy * vitesse;
  conv_coord_fantome(fantome);
  
  return 0;
}

int ramasse_pacgum(char labyrinthe[N_LAB][M_LAB], joueur_t* joueur) {
  if(labyrinthe[joueur->coord->y][joueur->coord->x] == 'p'){
    labyrinthe[joueur->coord->y][joueur->coord->x] = 'c';
    joueur->score += SCORE_PACGUM;
  }
  return 0;
}
