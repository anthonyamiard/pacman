/*
 * Fonctions permettant de gerer l'intelligence artificielle
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../include/IA.h"
#include "../include/objets.h"
#include "../include/labyrinthe.h"

#define SCORE_PACGUM 10
#define FAUX 0
#define VRAI 1

coord_t chemin_court(char labyrinthe[N_LAB][M_LAB], coord_t* coord_dep, coord_t* coord_arr) {
  int i,j;
  int trouve = FAUX;
  int nb_courant = 1;
  int lab_numero[N_LAB][M_LAB];
  lab_numero[coord_dep->y][coord_dep->x] = 1;
	   for(i=0;i<30 && !trouve;i++){
		     for(j=0;j<27 && !trouve;j++){
 			       if(est_chemin(labyrinthe[i][j])){
				           lab_numero[i][j] = nb_courant;
                   if (lab_numero[i][j] == nb_courant){
                     if(i-1>=0){
                       if(lab_numero[i-1][j] == 0)
                          lab_numero[i-1][j] = nb_courant + 1;
                     }
                     if(j-1>=0){
                       if(lab_numero[i][j-1] == 0)
                          lab_numero[i][j-1] = nb_courant +1;
                     }
                     if(i+1>=0){
                       if(lab_numero[i+1][j] == 0)
                          lab_numero[i+1][j] = nb_courant +1;
                     }
                     if(j+1>=0){
                       if(lab_numero[i][j+1] == 0)
                          lab_numero[i][j+1] = nb_courant +1;
                     }
                     if(lab_numero[coord_arr->y][coord_arr->x] == nb_courant + 1)
                        trouve = VRAI;
                  nb_courant ++;
                  }
            }
	     }
    }
 nb_courant = lab_numero[coord_arr->y][coord_arr->x];
 while(nb_courant > 1){
   if(i - 1 >= 0 && lab_numero[i-1][j] == nb_courant - 1)
      i = i - 1;
   else if(j - 1 >= 0 && lab_numero[i][j-1] == nb_courant - 1)
      j = j - 1;
   else if(i + 1 >= 0 && lab_numero[i+1][j] == nb_courant - 1)
      i = i - 1;
   else if(j + 1 >= 0 && lab_numero[i][j+1] == nb_courant - 1)
      j = j - 1;
   nb_courant --;
 }
 coord_t retour;
 retour.y=i;
 retour.x=j;
 return retour;
}

coord_t chemin_anticipe(char labyrinthe[N_LAB][M_LAB], coord_t* coord_dep, coord_t* coord_arr) {
  coord_t retour;
  retour.y=0;
  retour.x=0;
  return retour;
}

coord_t chemin_fuir(char labyrinthe[N_LAB][M_LAB], coord_t* coord_dep, coord_t* coord_arr) {
  coord_t retour;
  retour.y=0;
  retour.x=0;
  return retour;
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

int fantome(char labyrinthe[N_LAB][M_LAB], fantome_t* fantome, joueur_t* joueur, int vitesse) {
  coord_t temp;
  temp  = fantome->chemin(labyrinthe,fantome->coord,joueur->coord);
  fantome->coord->x=temp.x;
  fantome->coord->y=temp.y;
  return 0;
}

int ramasse_pacgum(char labyrinthe[N_LAB][M_LAB], joueur_t* joueur) {
  if(labyrinthe[joueur->coord->y][joueur->coord->x] == 'p'){
    labyrinthe[joueur->coord->y][joueur->coord->x] = 'c';
    joueur->score += SCORE_PACGUM;
  }
  return 0;
}
