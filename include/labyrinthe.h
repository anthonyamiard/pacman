/*!
 * \file		labyrinthe.h
 * \author		Anthony Amiard
 * \brief		Constantes et fonctions permettant de générer un labyrinthe
 * \date		2019
 *
 * Définition des constantes et des fonctions permettant de générer un
 * labyrinthe
 *
 */

#ifndef _LABYRINTHE_H_
#define _LABYRINTHE_H_



/*
 * CONSTANTES
 */



#include "taille_lab.h"



/*
 * FONCTIONS
 */

/*!
 * \name	Fonctions sur le labyrinthe
 * @{
 */

/*!
 * \fn		int genere_lab(char labyrinthe[N_LAB][M_LAB], int * nb_pacgums)
 * \brief	Génère un labyrinthe aléatoirement
 *
 * Génère un labyrinthe aléatoire dans la matrice \c labyrinthe et écrit le
 * nombre de pacgums présents dans le labyrinthe dans \c nb_pacgums.
 *
 * \param[out]	labyrinthe	Matrice de \c N_LAB lignes et \c M_LAB colonnes de
 *							caractères représentant le labyrinthe. Les valeurs
 *							des caractères peuvent être :
 *								\li \c 'm' : mur
 *								\li \c 'c' : chemin vide
 *								\li \c 'p' : chemin avec pacgum
 *								\li \c 's' : chemin avec super pacgum
 *								\li \c 'b' : boite des fantômes
 *								\li \c 'e' : entrée de la boite
 * \param[out]	nb_pacgums	Nombre de pacgums présents dans le labyrinthe généré
 * \retval		0	 aucune erreur
 */
int genere_lab(char labyrinthe[N_LAB][M_LAB], int * nb_pacgums);

/*!
 * \fn		int lab_manuel(char labyrinthe[N_LAB][M_LAB], int * nb_pacgums)
 * \brief	Labyrinthe généré manuellement
 *
 * Écrit un labyrinthe généré manuellement sur le même modèle que
 * \link genere_lab \c genere_lab \endlink.
 */
int lab_manuel(char labyrinthe[N_LAB][M_LAB], int * nb_pacgums);

/*!
 * \fn		void aff_lab(const char labyrinthe[N_LAB][M_LAB])
 * \brief	Affiche le labyrinthe
 *
 * Affiche le labyrinthe \c labyrinthe sur la sortie standard
 *
 * \param[in]	labyrinthe	Labyrinthe de \c N_LAB lignes et \c M_LAB colonnes à
 *							afficher
 */
void aff_lab(const char labyrinthe[N_LAB][M_LAB]);

/*!
 * \fn		void coord_alea(int x, int y, int * x2, int * y2)
 * \brief	Renvoie des coordonnées aléatoires
 *
 * Renvoie des coordonnées aléatoires voisines à \c x et \c y dans \c x2 et
 * \c y2.
 *
 * \param[in]	x	Coordonnée horizontale de la case d'origine
 * \param[in]	y	Coordonnée verticale de la case d'origine
 * \param[out]	x2	Coordonnée horizontale de la nouvelle case
 * \param[out]	y2	Coordonnée verticale de la case
 */
void coord_alea(int x, int y, int * x2, int * y2);

/*!
 * @}
 * \name	Fonctions sur les chemins
 * @{
 */

/*!
 * \fn		void chemin_alea(char demi_lab[N_LAB][M_LAB / 2], int x, int y)
 * \brief	Génère aléatoirement un chemin
 *
 * Génère aléatoirement un chemin à partir des coordonnées \c x et \c y.
 *
 * \param[in,out]	demi_lab	Demi-labyrinthe de \c N_LAB lignes et
 * 								<tt>M_LAB / 2</tt> colonnes
 * \param[in]		x			Coordonnée horizontale de départ
 * \param[in]		y			Coordonnée verticale de départ
 */
void chemin_alea(char demi_lab[N_LAB][M_LAB / 2], int x, int y);

/*!
 * \fn		int est_chemin(char case_lab)
 * \brief	Teste si \c case_lab est un chemin
 *
 * Renvoie vrai si le caractere \c case_lab correspond a un chemin (avec ou sans
 * item), faux sinon.
 *
 * \param[in]	case_lab	Case du labyrinthe à tester
 * \retval		0			La case n'est pas un chemin
 * \retval		1			La case est un chemin
 */
int est_chemin(char case_lab);

/*!
 * \fn		int nb_chemins_voisins(const char labyrinthe[N_LAB][M_LAB], int x, int y)
 * \brief	Nombre de chemins voisins d'une case
 *
 * Renvoie le nombre de chemins voisins de la case <tt>labyrinthe[y][x]</tt>.
 *
 * \param[in]	labyrinthe	Labyrinthe de \c N_LAB lignes et \c M_LAB colonnes
 * \param[in]	x			Coordonnée horizontale de la case
 * \param[in]	y			Coordonnée verticale de la case
 * \return		Nombre de chemins voisins de cette case
 */
int nb_chemins_voisins(const char labyrinthe[N_LAB][M_LAB], int x, int y);

/*!
 * \fn		int nb_chemins_voisins_demi(const char demi_lab[N_LAB][M_LAB / 2], int x, int y)
 * \brief	Nombre de chemins voisins d'une case
 *
 * Renvoie le nombre de chemins voisins de la case <tt>demi_lab[y][x]</tt>.
 * La fonction considère que le labyrinthe sera répliqué en mirroir pour compter
 * le nombre de chemins voisins des cases sur l'extrémité droite de la matrice.
 *
 * \param[in]	demi_lab	Demi-labyrinthe de \c N_LAB lignes et
 * 							<tt>M_LAB / 2</tt> colonnes
 * \param[in]	x			Coordonnée horizontale de la case
 * \param[in]	y			Coordonnée verticale de la case
 * \return		Nombre de chemins voisins de cette case
 */
int nb_chemins_voisins_demi(const char demi_lab[N_LAB][M_LAB / 2], int x,
							int y);

/*!
 * \fn		int place_permise(const char demi_lab[N_LAB][M_LAB / 2], int x, int y)
 * \brief	Teste si on peut générer un chemin aux coordonnées (x,y)
 *
 * Teste si un chemin peut être générer à la case <tt>demi_lab[y][x]</tt>
 * selon un ensemble de règles.
 *
 * \param[in]	demi_lab	Demi-labyrinthe de \c N_LAB lignes et
 *							<tt>M_LAB / 2</tt> colonnes
 * \param[in]	x			Coordonnée horizontale de la case
 * \param[in]	y			Coordonnée verticale de la case
 * \retval		0			Interdit de générer un chemin à cet emplacement
 * \retval		1			Génération d'un chemin autorisée
 */
int place_permise(const char demi_lab[N_LAB][M_LAB / 2], int x, int y);

void debouche_cds(char demi_lab[N_LAB][M_LAB/2], int x, int y);

/*!
 * \fn		void suppr_cds(char demi_lab[N_LAB][M_LAB / 2], int x, int y)
 * \brief	Supprime les culs-de-sac
 *
 * Supprime le cul-de-sac du demi-labyrinthe \c demi_lab aux coordonnées (x,y)
 * et appelle récursivement la fonction jusqu'à ce que ce chemin sans issu soit
 * totalement bouché.
 *
 * \param[in,out]	demi_lab	Demi-labyrinthe de \c N_LAB lignes et
 * 								<tt>M_LAB / 2</tt> colonnes
 * \param[in]		x			Coordonnée horizontale du cul-de-sac
 * \param[in]		y			Coordonnée verticale du cul-de-sac
 */
void suppr_cds(char demi_lab[N_LAB][M_LAB / 2], int x, int y);

/*!
 * @}
 * \name	Fonctions sur les murs
 * @{
 */

/*!
 * \fn		int epaisseur_mur(const char demi_lab[N_LAB][M_LAB / 2], int x, int y, int * xe, int * ye)
 * \brief	Renvoie l'épaisseur du mur
 *
 * Écrit l’épaisseur du mur en (x,y) dans \c xe et \c ye.
 *
 * \param[in]	demi_lab	Demi-labyrinthe de \c N_LAB lignes et
 *							<tt>M_LAB / 2</tt> colonnes
 * \param[in]	x			Coordonnée horizontale de la case
 * \param[in]	y			Coordonnée verticale de la case
 * \param[out]	xe			Largeur du mur
 * \param[out]	ye			Hauteur du mur
 * \retval		0			Aucune erreur
 * \retval		1			<tt>demi_lab[y][x]</tt> n'est pas un mur
 */
int epaisseur_mur(const char demi_lab[N_LAB][M_LAB / 2], int x, int y, int * xe,
				  int * ye);

/*!
 * \fn		int epaissir_mur_x(char demi_lab[N_LAB][M_LAB / 2], int x, int y)
 * \brief	Élargit le mur
 *
 * Épaissit le mur en (x, y) d'une case de largeur.
 *
 * \param[in,out]	demi_lab	Demi-labyrinthe de \c N_LAB lignes et
 * 								<tt>M_LAB / 2</tt> colonnes
 * \param[in]		x			Coordonnée horizontale du mur
 * \param[in]		y			Coordonnée verticale du mur
 * \retval			0			Aucune erreur
 * \retval			1			<tt>demi_lab[y][x]</tt> n'est pas un mur
 */
int epaissir_mur_x(char demi_lab[N_LAB][M_LAB / 2], int x, int y);

/*!
 * \fn		int epaissir_mur_y(char demi_lab[N_LAB][M_LAB / 2], int x, int y)
 * \brief	Épaissit le mur en y
 *
 * Épaissit le mur en (x, y) d'une case de hauteur.
 *
 * \param[in,out]	demi_lab	Demi-labyrinthe de \c N_LAB lignes et
 * 								<tt>M_LAB / 2</tt> colonnes
 * \param[in]		x			Coordonnée horizontale du mur
 * \param[in]		y			Coordonnée verticale du mur
 * \retval			0			Aucune erreur
 * \retval			1			<tt>demi_lab[y][x]</tt> n'est pas un mur
 */
int epaissir_mur_y(char demi_lab[N_LAB][M_LAB / 2], int x, int y);

/*!
 * @}
 */

#endif
