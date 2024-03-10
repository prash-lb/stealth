#ifndef __GARDIEN__
#define __GARDIEN__

#define NORMAL 4
#define PANIQUE 6
#define TEMPS_PANIQUE 30

#include "Deplacement.h"


typedef enum{
    MODE_NORMAL,
    MODE_PANIQUE
}Etat_gardien;

typedef enum{
    JOUEUR_NON_DETECTE,
    JOUEUR_DETECTE
}Etat_detecte;

typedef struct gardien {
    int cpt_panique;
    Etat_gardien alerte; /*type d'alerte du gardien*/
    Etat_detecte detecte; /*detection d'un joueur*/
    int distance_detection;
    Direction direction;
    Position pos;
    double/*float*/ vitesse;
    double chrono_panique;
}Gardien;

/*change la vitesse d'un gardien*/
void change_vitesse_gardien(Etat_gardien *etat, double/*float*/ *vitesse);
/*change la direction d'un gardien*/
void change_direction_(Direction *d);
/*configure un gardien en mode NORMAL
    @param Gardien *g: pointeur vers gardien
*/
void config_gardien_mode_normal(Gardien *g);
/*configure un gardien en mode PARNIQUE
    @param Gardien *g: pointeur vers gardien
*/
void config_gardien_mode_panique(Gardien *g);
/*Initialise un gardien
    @param Gardien *g: pointeur vers gardien
*/
void initalise_gardien(Gardien *g);


void affiche_info_gardien(Gardien *g);

#endif
