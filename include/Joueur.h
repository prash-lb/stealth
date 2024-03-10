#ifndef __JOUEUR__
#define __JOUEUR__

#define LONGUEUR 60
#define LARGEUR 45
#define VITESSE_JOUEUR_BASE 0.1
#define COORD_FIN_DE_JEU_X 2
#define COORD_FIN_DE_JEU_Y 2
#define INCREMENTE_VITESSE_JOUEUR 0.03

#include "Deplacement.h"
#include <assert.h>


typedef enum{
    AUCUN_MODE,
    MODE_INVISIBLE,
    MODE_ACCELERE
}Mode_joueur;

typedef struct joueur{
    int nb_relique; /*temporaire pour le nombre de relique*/
    int mana; /*temporaire pour la quantité de mana*/
    Direction direction;
    Mode_joueur mode;
    /*float*/double vitesse;
    Position pos;
}Joueur;


/*Initialise la vitesse d ujoeur.
    @param double *vitesse: pointeur.
*/
void init_vitesse_joueur(/*float*/double *vitesse);
/*change la vitesse d ujoeur.
    @param double *vitesse: pointeur.
*/
void augmente_vitesse_joueur(Mode_joueur *mode, /*float*/double *vitesse);
/*configure les param pour un joueur
    @param double *vitesse: pointeur.
*/
void config_joueur_mode_normal(Joueur *j);
/*Initialise le joeur
    @param double *vitesse: pointeur.
*/
void initialise_joueur(Joueur *j);


void affiche_info_joueur(Joueur const *j);

#endif
