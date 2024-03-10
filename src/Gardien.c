#include "../include/Gardien.h"

/*massi*/


/*attribue une vitesse aleatoire*/
void change_vitesse_gardien(Etat_gardien *etat, double/*float*/ *vitesse){
    assert(NULL != vitesse);
    assert(NULL != etat);
    switch(*etat){
        case MODE_NORMAL : *vitesse = (10.0 + rand() % (50 - 10)) / 100.0; break;
        case MODE_PANIQUE : *vitesse = 1.0; break;
        default : *vitesse = 0.0; break;
    }
}

/*Change la direction d'un gardien
tenir compte dans la fonction :
                - des murs à proximité (si il est en face d'un mur qui retourne pas dedans quoi)
*/
void change_direction_(Direction *d){
    int pos;
    assert(NULL != d);
    do{
        pos = rand();
    }while((pos % 4) == *d);
    *d = pos % 4;
}

/*configure le mode normal*/
void config_gardien_mode_normal(Gardien *g){
    assert(NULL != g);
    g->alerte = MODE_NORMAL;
    g->detecte = JOUEUR_NON_DETECTE;
    g->distance_detection = NORMAL;
    g->chrono_panique = 0;
    change_vitesse_gardien(&(g->alerte), &(g->vitesse));
    change_direction_(&(g->direction));
}
/*configure le mode panique*/
void config_gardien_mode_panique(Gardien *g){
    assert(NULL != g);
    g->alerte = MODE_PANIQUE;
    g->detecte = JOUEUR_NON_DETECTE;
    g->distance_detection = PANIQUE;
    g->chrono_panique = 0;
    change_vitesse_gardien(&(g->alerte), &(g->vitesse));
    change_direction_(&(g->direction));
}

/*Initialise les champs d'un gardien*/
void initalise_gardien(Gardien *g){
    assert(NULL != g);

    if(NULL == g){
        fprintf(stderr, "Gardien NULL");
        return;
    }
    g->direction = -1;
    g->cpt_panique = 0;
    config_gardien_mode_normal(g);
}


/*A SUPP APRES - Affiche les info d'un gardien*/
/*static*/ void affiche_info_gardien(Gardien *g);

void affiche_info_gardien(Gardien *g){
    assert(NULL != g);

    if(NULL == g){
        fprintf(stderr, "Gardien NULL");
        return;
    }
    switch(g->alerte){
        case MODE_NORMAL : printf("Mode : Mode normal\n"); break;
        case MODE_PANIQUE : printf("Mode : Mode panique\n"); break;
        default : printf("MODE INCORRECT\n"); break;
    }
    switch(g->detecte){
        case JOUEUR_NON_DETECTE : printf("Etat de detection : Joueur non detecté\n"); break;
        case JOUEUR_DETECTE : printf("Etat de detection : Joueur dectecté\n"); break;
        default : printf("ETAT INCORRECT\n"); break;
    }
    switch(g->direction){
        case HAUT : printf("Direction : HAUT\n"); break;
        case BAS : printf("Direction : BAS\n"); break;
        case GAUCHE : printf("Direction : GAUCHE\n"); break;
        case DROITE : printf("Direction : DROITE\n"); break;
        default : printf("DIRECTION INCORRECT\n"); break;
    }
    printf("rayon detection : %d\n", g->distance_detection);
    printf("Position [x][y] : [%f][%f]\n", g->pos.x, g->pos.y);
    printf("Vitesse : %f\n", g->vitesse);
    printf("Nombre d'entrée en mode panique : %d\n", g->cpt_panique);
}
