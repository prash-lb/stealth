#include "../include/Joueur.h"

/*s'occupe de changer la vitesse selon le mode*/
static void change_vitesse_joueur(Mode_joueur *mode, double/*float */*vitesse){
    if(*mode == MODE_ACCELERE && *vitesse < 1.2){
        *vitesse += INCREMENTE_VITESSE_JOUEUR;
        if(*vitesse > 1.2){
            *vitesse = 1.2;
        }
    }
    else if(*vitesse < 0.9){
            *vitesse += INCREMENTE_VITESSE_JOUEUR;
            if(*vitesse > 0.9){
                *vitesse = 0.9;
            }
    }
}

/*augmente la vitesse d'un joueur */
void augmente_vitesse_joueur(Mode_joueur *mode, /**float*/double *vitesse){
    switch(*mode){
        case AUCUN_MODE :  change_vitesse_joueur(mode, vitesse);
                            break;
        case MODE_INVISIBLE :   change_vitesse_joueur(mode, vitesse);
                                break;
        case MODE_ACCELERE :    change_vitesse_joueur(mode, vitesse);
                                break;
        default : printf("Mode incorrect\n"); *vitesse = 0; break;
    }
}

void config_joueur_mode_normal(Joueur *j){
    j->mode = AUCUN_MODE;
    j->direction = -1;
    j->nb_relique = 0;
    j->mana = 0;
    j->pos.x = j->pos.y = 2;
    j->vitesse = VITESSE_JOUEUR_BASE;
}

void initialise_joueur(Joueur *j){
    assert(NULL != j);
    if(NULL == j){
        fprintf(stderr, "Le joueur est NULL !\n");
        return;
    }
    config_joueur_mode_normal(j);
}



/*static*/ void affiche_info_joueur(Joueur const *j){
    assert(NULL != j);
    if(NULL == j){
        fprintf(stderr, "Le joueur est NULL !\n");
        return;
    }
    puts("");
    switch(j->mode){
        case AUCUN_MODE : printf("mode :MODE NORMAL\n"); break;
        case MODE_INVISIBLE :  printf("mode :MODE INVISIBLE\n"); break;
        case MODE_ACCELERE : printf("mode :MODE ACCELERE\n"); break;
        default : printf("Mode incorrect\n"); break;
    }
    printf("nombre de relique : %d\n", j->nb_relique);
    printf("nb de mana : %d %c\n", j->mana, '%');
    printf("position [x][y] : [%f][%f]\n", j->pos.x, j->pos.y);
    printf("direction -1 à l'initial : %d\n", j->direction);
    printf("Vitesse : %.2f\n", j->vitesse);
}
