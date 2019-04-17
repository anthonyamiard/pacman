/*!
 * \file	objets.c
 * \author	Anthony Amiard
 * \date	2019
 * 
 * Fonctions permettant de créer et détruire les différents objets définis dans
 * \ref objets.h.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/objets.h"
#include "../gui/gui_lab.h"
#include "../gui/dessin.h"

/*
 * Fonctions de création des objets
 */

coord_t * cree_coord(int x, int y) {
    coord_t * coord = malloc(sizeof(coord_t));
    if(coord != NULL) {
        coord->x = x;
        coord->y = y;
    }
    return coord;
}

fruit_t * cree_fruit(int points, int x, int y) {
    fruit_t * fruit = malloc(sizeof(fruit_t));
    if(fruit != NULL) {
        fruit->points = points;
        fruit->coord.x = x;
        fruit->coord.y = y;
    }
    return fruit;
}

joueur_t * cree_joueur(SDL_Renderer * rend, int vies, int score, int x, int y) {
    joueur_t * joueur = malloc(sizeof(joueur_t));
    if(joueur != NULL) {
        joueur->vies = vies;
        joueur->score = score;
        pacdir = 0;
        joueur->f_cons = 0;
        joueur->nextdir = 0;
        joueur->coord.x = x;
        joueur->coord.y = y;
        joueur->position.x = x * TAILLE_CASE;
        joueur->position.y = y * TAILLE_CASE;
        SDL_QueryTexture(sprites.pac, NULL, NULL, &(joueur->position.w),
                        &(joueur->position.h));
        SDL_RenderCopy(rend, sprites.pac, NULL, &(joueur->position));
    }
    return joueur;
}

fantome_t * cree_fantome(SDL_Renderer * rend,
                        char couleur,
                        coord_t (*chemin)(char [N_LAB][M_LAB],
                                        coord_t *,
                                        coord_t *),
                        int x,
                        int y) {
    fantome_t * fantome = malloc(sizeof(fantome_t));
    SDL_Texture * sprite = NULL;
    switch(couleur) {
        case 'b' : sprite = sprites.fant_b; break;
        case 'r' : sprite = sprites.fant_r; break;
        case 'o' : sprite = sprites.fant_o; break;
        case 'p' : sprite = sprites.fant_p; break;
    }
    if(fantome != NULL) {
        fantome->couleur = couleur;
        fantome->chemin = chemin;
        fantome->etat = ATTENTE;
        fantome->dir = 'd';
        fantome->coord.x = x;
        fantome->coord.y = y;
        fantome->coord_dep.x = x;
        fantome->coord_dep.y = y;
        fantome->position.x = x * TAILLE_CASE;
        fantome->position.y = y * TAILLE_CASE;
        fantome->texture = sprite;
        SDL_QueryTexture(sprite, NULL, NULL, &(fantome->position.w),
                        &(fantome->position.h));
        SDL_RenderCopy(rend, sprite, NULL, &(fantome->position));
    }
    return fantome;
}

/*
 * Fonctions de destruction des objets
 */

int detruit_coord(coord_t ** adr) {
    free(*adr);
    *adr = NULL;
    return 0;
}

int detruit_fruit(fruit_t ** adr) {
    free(*adr);
    *adr = NULL;
    return 0;
}

int detruit_joueur(joueur_t ** adr) {
    free(*adr);
    *adr = NULL;
    return 0;
}

int detruit_fantome(fantome_t ** adr) {
    free(*adr);
    *adr = NULL;
    return 0;
}
