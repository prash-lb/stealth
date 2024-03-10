#ifndef __MOTEUR_GRAPHIQUE__
#define __MOTEUR_GRAPHIQUE__

#include "Gestion_terrain.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#define TAILLE_CASE 15
#define LONGUEUR_FENETRE (LONGEUR_PLATEAU * TAILLE_CASE)
#define LARGEUR_FENETRE (LARGEUR_PLATEAU * TAILLE_CASE)
#define EXTENSION 100

/*
0 : case vide
1 : mur
2 : gardien
3 : relique
4 : joueur
*/

/*Dessine le contenu de la fenetre graphique avec le conttenu de plateau.
    @PLateau *p: pointeur sur plateau
    @param int longueur: pointeur sur plateau
    @param int largeur: pointeur sur plateau
    @param double sec: pointeur sur plateau
*/
void dessine_plateau_graphique(Plateau const *p, int longueur, int largeur, double *sec);

#endif
