/*!
 * \file	surface.h
 * \author	Anthony Amiard
 *
 * Menu
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "surface.h"
#include "../include/taille_lab.h"

#define PLAY 1
#define PAUSE 0
/**
 * \fn int menu_SDL(void)
 * \brief Fonction qui va nous afficher le menu grâce à la SDL pour jouer et quitter le jeu.
 * \param rien
 * \return entier
 */
int menu_SDL(void){
    int x,y;
    char pac[10] ="PACMAN";
    //Le pointeur vers la fenetre
    SDL_Window* pWindow = NULL;
    //Le pointeur vers la surface incluse dans la fenetre
    SDL_Renderer *renderer=NULL;
    SDL_Rect txtDestRect, txtBvnRect, txtMenuRect[4], imgBtnRect, imgBGRect;

    // Une variable de couleur noire
    SDL_Color couleurNoire = {0, 0, 0, 0};

    /* Création de la fenêtre */
    pWindow = SDL_CreateWindow("Pacman",SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               M_LAB * TAILLE_CASE,
                               N_LAB * TAILLE_CASE,
                               SDL_WINDOW_SHOWN);

    if(!pWindow){
        fprintf(stderr, "Erreur à la création de la fenetre : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL){
        fprintf(stderr, "Erreur à la création du renderer\n");
        exit(EXIT_FAILURE);
    }
    SDL_Texture *texte_tex = tex_text("PoliceTitre.ttf",100,"Pacman",couleurNoire,renderer);
    SDL_Texture *texteMenu_tex[2];
    texteMenu_tex[0] = tex_text("PoliceMenu.ttf",40,"Jouer",couleurNoire,renderer);
    texteMenu_tex[1] = tex_text("PoliceMenu.ttf",40,"Quitter",couleurNoire,renderer);

    //Position ou sera mis le texte dans la fenêtre
    //TITRE
    txtDestRect.x = 300;
    txtDestRect.y = 10;
    SDL_QueryTexture(texte_tex, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));

    //MENU
    for(int j=0;j<4;j++){

        if(j==2 || j==3){
            txtMenuRect[j].x = 480;
        }else{
            txtMenuRect[j].x = 500;
        }
        txtMenuRect[j].y = 165+90*j;
        SDL_QueryTexture(texteMenu_tex[j], NULL, NULL, &(txtMenuRect[j].w), &(txtMenuRect[j].h));
    }


    //Chargement de l'image de fond
    SDL_Texture *image_BG_tex = tex_img_png("./img/Pacman.png",renderer);
    //Chargement de l'image bouton
    SDL_Texture *image_btn_tex = tex_img_png("./img/btn.png",renderer);
    //Chargement de l'image bouton (utilisé quand la souris passe sur l'image)
    SDL_Texture *image_btnHover_tex = tex_img_png("./img/btn.png",renderer);
    //IMAGE PLAY
    SDL_Texture *image_play_tex = tex_img_png("./img/play.png",renderer);
    //IMAGE PAUSE
    SDL_Texture *image_pause_tex = tex_img_png("./img/pause.png",renderer);

    SDL_Texture *temp;
    int i=0;

    if( pWindow )
    {
        int running = 1;
        while(running) {
            SDL_Event e;
            SDL_GetMouseState(&x,&y);
            //if(x<700 && 385<x && y<526 && 130<y) goto affichage;
            //printf("x:%i y:%i\n",x,y);

            while(SDL_PollEvent(&e)) {
                switch(e.type) {
                    case SDL_QUIT: running = 0;break;
                    case SDL_MOUSEBUTTONDOWN:
                    case SDL_WINDOWEVENT:
                    //affichage:
                        /* Le fond de la fenêtre sera blanc */
                        //SDL_SetRenderDrawColor(renderer, 24, 124, 58, 255);
                        SDL_RenderClear(renderer);

                        //BACKGROUND
                        imgBGRect.x = 0;
                        imgBGRect.y = 0;
                        SDL_QueryTexture(image_BG_tex, NULL, NULL, &(imgBGRect.w), &(imgBGRect.h));
                        SDL_RenderCopy(renderer, image_BG_tex, NULL, &imgBGRect);

                        /* Ajout du texte en noir */
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

                        SDL_RenderCopy(renderer, texte_tex, NULL, &txtDestRect);

                        SDL_RenderDrawLine(renderer,0,130,1080,130);

                        //Positionnement du premier bouton
                        imgBtnRect.x = 440;
                        imgBtnRect.y = 150;
                        SDL_QueryTexture(image_btnHover_tex, NULL, NULL, &(imgBtnRect.w), &(imgBtnRect.h));
                        for(i=0;i<4;i++){
                            if(x<620 && 440<x && y<imgBtnRect.y+77 && imgBtnRect.y<y){
                                temp = image_btnHover_tex;
                                if(e.type == SDL_MOUSEBUTTONDOWN){
                                    SDL_DestroyWindow(pWindow);
                                    //lancement_jeu(i);
                                    return 0;
                                }
                            }else{
                                temp = image_btn_tex;
                            }
                            SDL_RenderCopy(renderer, temp, NULL, &imgBtnRect);
                            SDL_RenderCopy(renderer, texteMenu_tex[i], NULL, &(txtMenuRect[i]));
                            imgBtnRect.y += 90;
                        }

                        imgBtnRect.x = 1000;
                        imgBtnRect.y = 570;

                        /* On fait le rendu ! */
                        SDL_RenderPresent(renderer);
                        break;
                }
            }
        }
    } else {
        fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
    }

    //Destruction de la fenetre
    if(pWindow != NULL) SDL_DestroyWindow(pWindow);
    return 0;

}
