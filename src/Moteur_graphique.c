#include "../include/Moteur_graphique.h"
#include "MLV/MLV_all.h"

/*Massi*/

static void fenetre_temps(double *sec){
    char *tmp;
    tmp = (char*)malloc(sizeof(char) * 50);

    assert(NULL != sec);

    sprintf(tmp, "%.0f", *sec);
    strcat(tmp, " s");
    MLV_draw_text(LONGUEUR_FENETRE + TAILLE_CASE, 10, "TEMPS", MLV_COLOR_WHITE);
    MLV_draw_text(LONGUEUR_FENETRE + TAILLE_CASE, 25, tmp, MLV_COLOR_WHITE);
    free(tmp);
}

static void mana_du_joueur(const int *mana){
    char *tmp;
    tmp = (char*)malloc(sizeof(char) * 50);
    assert(NULL != mana);
    sprintf(tmp, "Mana : %.d", *mana);
    MLV_draw_text(LONGUEUR_FENETRE + TAILLE_CASE, 50, tmp, MLV_COLOR_WHITE);
    free(tmp);
}

static void dessine_quadrillage(int longueur, int largeur){
    int i;
    for(i = 0; i <= largeur; i += TAILLE_CASE){
        MLV_draw_filled_rectangle(0, i, longueur, 0, MLV_COLOR_BLACK);
    }
    for(i = 0; i <= longueur; i += TAILLE_CASE){
        MLV_draw_filled_rectangle(i, 0, 0, largeur, MLV_COLOR_BLACK);
    }
    /*printf("q-OK\n");*/
}

static void dessine_mur(int *x, int *y, int taille_mur){
    assert(NULL != y);
    assert(NULL != x);
    MLV_draw_filled_rectangle(*x, *y, taille_mur, taille_mur, MLV_COLOR_BLACK);
}

static void dessine_gardien(Plateau const *p){
    int i;
    assert(NULL != p);
    for(i = 0; i < NB_GARDIEN; ++i){
        switch(p->gardien[i].alerte){
            case MODE_NORMAL : MLV_draw_filled_circle(p->gardien[i].pos.x * TAILLE_CASE,
                                                        p->gardien[i].pos.y * TAILLE_CASE,
                                                         TAILLE_CASE / 2, MLV_COLOR_BLUE);
                               MLV_draw_circle(p->gardien[i].pos.x * TAILLE_CASE,
                                                p->gardien[i].pos.y * TAILLE_CASE,
                                                 TAILLE_CASE * p->gardien[i].distance_detection,
                                                  MLV_COLOR_BLUE);
                               break;
            case MODE_PANIQUE : MLV_draw_filled_circle(p->gardien[i].pos.x * TAILLE_CASE,
                                                        p->gardien[i].pos.y * TAILLE_CASE,
                                                         TAILLE_CASE / 2, MLV_COLOR_GREEN);
                                MLV_draw_circle(p->gardien[i].pos.x * TAILLE_CASE,
                                                 p->gardien[i].pos.y * TAILLE_CASE,
                                                  TAILLE_CASE * p->gardien[i].distance_detection,
                                                   MLV_COLOR_BLUE);
                                break;

            default : break;
        }

    }
}

static void dessine_relique(Plateau const *p){
    int i;
    assert(NULL != p);
    for(i = 0; i < NB_RELIQUE; ++i){
        switch(p->relique[i].etat){
            case NON_RECUPERER : MLV_draw_filled_circle(p->relique[i].pos.x * TAILLE_CASE,
                                                        p->relique[i].pos.y * TAILLE_CASE,
                                                         TAILLE_CASE / 2, MLV_COLOR_LIGHT_BLUE);
                               break;
            /*case RECUPERER : MLV_draw_filled_circle(p->relique[i].pos.x * TAILLE_CASE,
                                                        p->relique[i].pos.y * TAILLE_CASE,
                                                         TAILLE_CASE / 2, MLV_COLOR_PURPLE);
                                break;*/

            default : break;
        }

    }
}

static void dessine_tuile(Plateau const *p){
    int i;
    for(i = 0; i < NB_TUILE; ++i){
        switch(p->tuile[i].etat){
            case NON_RECUPERER : MLV_draw_filled_circle(p->tuile[i].pos.x * TAILLE_CASE,
                                                        p->tuile[i].pos.y * TAILLE_CASE,
                                                         TAILLE_CASE / 2, MLV_COLOR_ORANGE);
                               break;
            case RECUPERER : MLV_draw_filled_circle(p->tuile[i].pos.x * TAILLE_CASE,
                                                        p->tuile[i].pos.y * TAILLE_CASE,
                                                         TAILLE_CASE / 2, MLV_COLOR_PURPLE);
                                break;

            default : break;
        }

    }
}


static void dessine_joueur(Joueur const *joueur){
    switch(joueur->mode){
        case AUCUN_MODE : MLV_draw_filled_circle(joueur->pos.x * TAILLE_CASE,
                                                    joueur->pos.y * TAILLE_CASE,
                                                     TAILLE_CASE / 2, MLV_COLOR_RED);
                          break;
        case MODE_INVISIBLE : MLV_draw_filled_circle(joueur->pos.x * TAILLE_CASE,
                                                      joueur->pos.y * TAILLE_CASE,
                                                       TAILLE_CASE / 2, MLV_COLOR_WHITE);
                              break;
        case MODE_ACCELERE : MLV_draw_filled_circle(joueur->pos.x * TAILLE_CASE,
                                                     joueur->pos.y * TAILLE_CASE,
                                                      TAILLE_CASE / 2, MLV_COLOR_PINK);
                             break;
        default : break;
    }
}


void dessine_plateau_graphique(Plateau const *p, int longueur, int largeur, double *sec){
    int i, j, case_x, case_y;
    MLV_clear_window(MLV_COLOR_GREY40);
    dessine_quadrillage(longueur * TAILLE_CASE, largeur * TAILLE_CASE);

    for(i = 0; i < largeur; ++i){
        case_y = i * TAILLE_CASE;
        for(j = 0; j < longueur; ++j){
            case_x = j * TAILLE_CASE;
            /*printf("%d : %d __ %d : %d\n", i, case_y, j, case_x);*/
            switch(p->plateau[i][j]){
                case 1 : dessine_mur(&case_x, &case_y, TAILLE_CASE); break;
                case 4 : dessine_joueur(&(p->joueur)); break;
                default : break;
            }
        }
    }
    dessine_gardien(p);
    dessine_tuile(p);
    dessine_relique(p);
    fenetre_temps(sec);
    mana_du_joueur(&(p->joueur.mana));
    MLV_actualise_window();
}
