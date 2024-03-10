#ifndef __MOTEUR_DE_JEU__
#define __MOTEUR_DE_JEU__

#include "Relique.h"
#include "Gardien.h"
#include "Joueur.h"
#include <assert.h>
#include <math.h>

#define LARGEUR_PLATEAU 45
#define LONGEUR_PLATEAU 60
#define DISTANCE_MIN_JOUEUR_GARDIEN_OBJ 20
#define NB_RELIQUE 3
#define NB_GARDIEN 5
#define NB_TUILE 20
#define QUANTITE_MANA_TUILE 60
#define LIMITE_NB_PANIQUE 3
#define minside 9

typedef enum element_de_jeu{
    VIDE,
    MUR,
    GARDIEN,
    RELIQUE,
    JOUEUR,
    TUILE
}Element_de_jeu;


typedef struct tuile{
    Etat_objet etat;
    Position_obj pos;
    int mana;/*60*/
}Tuile;

typedef struct plateau{
    int cpt_mana, mana_conso;
    int plateau[LARGEUR_PLATEAU][LONGEUR_PLATEAU];
    Joueur joueur;
    Gardien gardien[NB_GARDIEN];
    Relique relique[NB_RELIQUE];
    Tuile tuile[NB_TUILE];
} Plateau;

/*Crée le contenu du plateau et initialise ses elements.
    @PLateau *game: pointeur sur plateau
*/
void create_map(Plateau *game);
/*Change l'état d'une relique ou d'une tuile
    @Etat_obj *o: pointeur sur Etat_obj.
*/
void change_etat_obj(Etat_objet *o);

#endif
