/*!
 * \file	pacman.c
 * \author	Anthony Amiard
 * \date	2019
 *
 * Fichier contenant la fonction main.
 *
 */

#define _MAIN_C_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

#include "../include/labyrinthe.h"
#include "../include/objets.h"
#include "../include/IA.h"
#include "../gui/dessin.h"
#include "../gui/gui_lab.h"
#include "../gui/mouv.h"
#include "../gui/surface.h"
#include "../gui/osd.h"



int main() {
    
    /*
     * Initialisations
     */
    
    srand(time(NULL));

    if(SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Échec d'ouverture de la SDL (%s).\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    
    if(TTF_Init()) {
        fprintf(stderr, "Échec d'ouverture de TTF (%s).\n", TTF_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    
    TTF_Font * police_menu = TTF_OpenFont("../fonts/PoliceMenu.ttf", 32);
    TTF_Font * police_message = TTF_OpenFont("../fonts/PoliceMenu.ttf", 24);
    if(police_message == NULL || police_menu == NULL)
        fprintf(stderr, "Échec d'ouverture de la police (%s).\n",
                TTF_GetError());

//	menu_SDL();

    SDL_Window * fenetre = SDL_CreateWindow("Pacman",
                                            SDL_WINDOWPOS_UNDEFINED,
                                            SDL_WINDOWPOS_UNDEFINED,
                                            W_FEN,
                                            H_FEN,
                                            SDL_WINDOW_SHOWN);
    if(fenetre == NULL) {
        fprintf(stderr, "Échec de création de la fenêtre (%s).\n",
                SDL_GetError());
        TTF_CloseFont(police_menu);
        TTF_CloseFont(police_message);
        TTF_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Renderer * rend = SDL_CreateRenderer(fenetre, -1,
                                             SDL_RENDERER_ACCELERATED);
    if(rend == NULL) {
        fprintf(stderr, "Échec de création du renderer (%s).\n",
                SDL_GetError());
        SDL_DestroyWindow(fenetre);
        TTF_CloseFont(police_menu);
        TTF_CloseFont(police_message);
        TTF_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    init_sprites(rend);

    char labyrinthe[N_LAB][M_LAB];
    int nb_pacgums;             /* Nombre de pacgums dans le labyrinthe */
    int niveau = 1;             /* Numéro du niveau actuel */
    char message[20];           /* Message affiché au milieu du labyrinthe */
    do {
        genere_lab(labyrinthe, &nb_pacgums);
    } while(nb_pacgums < 280 || nb_pacgums > 350);
    

    joueur_t * pacman = cree_joueur(rend, 3, 0, X_DEP, Y_DEP);

    fantome_t * fant_b = cree_fantome(rend, 'b', chemin_fuir, X_BLEU, Y_BLEU);
    fantome_t * fant_o = cree_fantome(rend, 'o', chemin_aleatoire, X_ORANGE,
                                    Y_ORANGE);
    fantome_t * fant_r = cree_fantome(rend, 'r', chemin_court, X_ROUGE, Y_ROUGE);
    fantome_t * fant_p = cree_fantome(rend, 'p', chemin_anticipe, X_ROSE,
                                        Y_ROSE);
    
    /* Timer pour contrôler la durée d'une image */
    uint32_t start_time = 0;
    uint32_t end_time = 0;
    uint32_t delta = 0;
    short fps = 30;
    short mspf = 1000/fps;
    
    strcpy(message, "Niveau 1");
    
    int continuer = 1;      /* Mettre à 0 pour sortir de la boucle */
    long timer = -1;        /* Timer pour compter le temps de pause lors de 
                             * collisions. Quand le timer est négatif l'action
                             * continue. */
    while(continuer) {
        if(!start_time)
            start_time = SDL_GetTicks();
        else
            delta = end_time - start_time;
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_QUIT: continuer = 0; break;
                case SDL_WINDOWEVENT:/*
                    switch(e.window.event) {
                        case SDL_WINDOWEVENT_EXPOSED:
                        case SDL_WINDOWEVENT_SIZE_CHANGED:
                        case SDL_WINDOWEVENT_RESIZED:
                        case SDL_WINDOWEVENT_SHOWN:
                            SDL_RenderPresent(rend);
                            break;
                    }
*/
                    break;
                case SDL_KEYDOWN:
                    if(fant_b->etat == ATTENTE)
                        fant_b->etat = POURSUITE;
                    if(fant_r->etat == ATTENTE)
                        fant_r->etat = POURSUITE;
                    if(fant_o->etat == ATTENTE)
                        fant_o->etat = POURSUITE;
                    if(fant_p->etat == ATTENTE)
                        fant_p->etat = POURSUITE;
                    message[0] = 0;
                    if(timer < 0) {
                        switch(e.key.keysym.sym) {
                            case SDLK_UP:
                                pacman->nextdir = 'h';
                                break;
                            case SDLK_DOWN:
                                pacman->nextdir = 'b';
                                break;
                            case SDLK_RIGHT:
                                pacman->nextdir = 'd';
                                break;
                            case SDLK_LEFT:
                                pacman->nextdir = 'g';
                                break;
                        }
                    }
                    break;
            }
        }
        
        SDL_RenderClear(rend);
        dessine_lab(labyrinthe, rend);
        deplace_fantome(fant_b, labyrinthe, rend, pacman, fps, timer >= 0);
        deplace_fantome(fant_r, labyrinthe, rend, pacman, fps, timer >= 0);
        deplace_fantome(fant_o, labyrinthe, rend, pacman, fps, timer >= 0);
        deplace_fantome(fant_p, labyrinthe, rend, pacman, fps, timer >= 0);
        deplace_joueur(pacman, labyrinthe, &nb_pacgums, rend, fant_b,
                    fant_r, fant_o, fant_p, fps, timer >= 0);
        
        gere_collisions(pacman, fant_b, fant_r, fant_o, fant_p, &timer, fps);
        
        /* Cas où Pacman n'a plus de vie */
        if(pacman->vies == 0) {
            strcpy(message, "Perdu !");
            if(timer < 0) {
                do {
                    genere_lab(labyrinthe, &nb_pacgums);
                } while(nb_pacgums < 280 || nb_pacgums > 350);
                pacman->vies = 3,
                pacman->score = 0;
                niveau = 1;
                init_place(pacman, fant_b, fant_r, fant_o, fant_p);
                sprintf(message, "Niveau %d", niveau);
            }
        }
        
        /* Cas où toutes les pacgums du labyrinthe ont été mangées */
        if(nb_pacgums == 0) {
            do {
                genere_lab(labyrinthe, &nb_pacgums);
            } while(nb_pacgums < 280 || nb_pacgums > 350);
            niveau++;
            init_place(pacman, fant_b, fant_r, fant_o, fant_p);
            sprintf(message, "Niveau %d", niveau);
        }
        
        score_osd(rend, police_menu, pacman, niveau);
        
        if(message[0])
            message_osd(rend, police_message, message);

        SDL_RenderPresent(rend);
        
        timer--;
        if(delta < mspf)
            SDL_Delay(mspf - delta);
        start_time = end_time;
        end_time = SDL_GetTicks();


    }

    detruit_sprites();
    detruit_joueur(&pacman);
    detruit_fantome(&fant_b);
    detruit_fantome(&fant_r);
    detruit_fantome(&fant_o);
    detruit_fantome(&fant_p);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(fenetre);
    TTF_CloseFont(police_menu);
    TTF_CloseFont(police_message);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
