#include "../include/Collision.h"


/*Prashath*/


/*en fait avant de deplacer le personnage
on renverra avec une fonction bis les coordonnées futur du Joueur
pour voir ce qu'il va y trouver*/
int est_dans_zone_objet(Position *joueur, Position_obj *objet){
    assert(NULL != joueur);
    assert(NULL != objet);
    if(joueur->x >= objet->x - MARGE_DISTANCE && joueur->x <= objet->x + MARGE_DISTANCE &&
        joueur->y >= objet->y - MARGE_DISTANCE && joueur->y <= objet->y + MARGE_DISTANCE){
            return 1;
        }
    return 0;
}


/*calcule la distance euclidienne entre le joueur et le gardien*/
static int rayon_detection_gardien(Position *joueur, Position *gardien){
    assert(NULL != joueur);
    assert(NULL != gardien);
    return sqrt((joueur->x - gardien->x)*(joueur->x - gardien->x) + (joueur->y - gardien->y)*(joueur->y - gardien->y));
}

static int mur(Plateau *plateau, int *num_gardien){
    int a;
    double Pa, Ya;
    assert(NULL != plateau);
    assert(NULL != num_gardien);
    /*côté de detection à gauche*/
    for(a = (int)plateau->joueur.pos.x + 1; a < (int)plateau->gardien[*num_gardien].pos.x; ++a){
        Pa = (a - plateau->gardien[*num_gardien].pos.x) / (plateau->joueur.pos.x - plateau->gardien[*num_gardien].pos.x);
        Ya = (Pa * plateau->joueur.pos.y) + (1 - Pa) * plateau->gardien[*num_gardien].pos.y;
        if(plateau->plateau[(int)Ya][a] == MUR){
            return 1;
        }
    }
    /*haut*/
    for(a = (int)plateau->joueur.pos.y + 1; a < (int)plateau->gardien[*num_gardien].pos.y; ++a){
        Pa = (a - plateau->gardien[*num_gardien].pos.y) / (plateau->joueur.pos.y - plateau->gardien[*num_gardien].pos.y);
        Ya = (Pa * plateau->joueur.pos.x) + (1 - Pa) * plateau->gardien[*num_gardien].pos.x;
        if(plateau->plateau[a][(int)Ya] == MUR){
            return 1;
        }
    }
    /*bas*/
    for(a = (int)plateau->gardien[*num_gardien].pos.y + 1; a < (int)plateau->joueur.pos.y; ++a){
        Pa = (a - plateau->joueur.pos.y) / (plateau->gardien[*num_gardien].pos.y - plateau->joueur.pos.y);
        Ya = Pa * plateau->gardien[*num_gardien].pos.x + (1 - Pa) * plateau->joueur.pos.x;
        if(plateau->plateau[a][(int)Ya] == MUR){
            return 1;
        }
    }
    /*côté de detection à droite*/
    for(a = (int)plateau->gardien[*num_gardien].pos.x + 1; a < (int)plateau->joueur.pos.x; ++a){
        Pa = (a - plateau->joueur.pos.x) / (plateau->gardien[*num_gardien].pos.x - plateau->joueur.pos.x);
        Ya = Pa * plateau->gardien[*num_gardien].pos.y + (1 - Pa) * plateau->joueur.pos.y;
        if(plateau->plateau[(int)Ya][a] == MUR){
            return 1;
        }
    }
    return 0;
}

/*renvoie 0 si le joueur est detecté et 1 sinon*/
int gardien_detecte_joueur(Plateau *plateau){
    int i;
    assert(NULL != plateau);
    for(i = 0; i < NB_GARDIEN; ++i){
        /*coté gauche du gardien*/
        if(rayon_detection_gardien(&(plateau->joueur.pos), &(plateau->gardien[i].pos)) <= plateau->gardien[i].distance_detection &&
            mur(plateau, &i) == 0 && plateau->joueur.mode != MODE_INVISIBLE){
            return 1;
        }
    }
    return 0;
}


static int rayon_detection_gardien_tuile(Position_obj *relique, Position *gardien){
    assert(NULL != relique);
    assert(NULL != gardien);
    return sqrt((relique->x - gardien->x) * (relique->x - gardien->x) +
        (relique->y - gardien->y) * (relique->y - gardien->y));
}

int gardien_detecte_relique(Plateau *plateau, double *sec){
    int i, j;
    assert(NULL != plateau);
    assert(NULL != sec);
    for(i = 0; i < NB_GARDIEN; ++i){
        for(j = 0; j < NB_RELIQUE; ++j){
            if(rayon_detection_gardien_tuile(&(plateau->relique[j].pos), &(plateau->gardien[i].pos)) <= plateau->gardien[i].distance_detection &&
                plateau->relique[j].etat == RECUPERER && plateau->gardien[i].cpt_panique <= LIMITE_NB_PANIQUE && plateau->gardien[i].alerte == MODE_NORMAL){
                    config_gardien_mode_panique(&(plateau->gardien[i]));
                    plateau->gardien[i].cpt_panique++;
                    plateau->gardien[i].chrono_panique = *sec + TEMPS_PANIQUE;
            }
            else if(plateau->gardien[i].chrono_panique <= *sec && plateau->gardien[i].alerte == MODE_PANIQUE){
                config_gardien_mode_normal(&(plateau->gardien[i]));
            }
        }
    }
    return 0;
}

/*testé et fonctionne
(peut être initialiser le cpt à -1)*/
int distance_vers_mur(Plateau const *plateau, Position const *pos, Direction const *dir){
    int cpt, indice_x, indice_y;
    assert(NULL != plateau);
    assert(NULL != pos);
    assert(NULL != dir);
    cpt = 0;
    switch(*dir){
        case HAUT : indice_y = (int)pos->y;
                    indice_x = (int)pos->x;
                    while(plateau->plateau[indice_y][indice_x] != 1){
                        --indice_y;
                        ++cpt;
                    }break;

        case BAS : indice_y = (int)pos->y;
                   indice_x = (int)pos->x;
                   while(plateau->plateau[indice_y][indice_x] != 1){
                       ++indice_y;
                       ++cpt;
                   }break;

        case GAUCHE : indice_y = (int)pos->y;
                      indice_x = (int)pos->x;
                      while(plateau->plateau[indice_y][indice_x] != 1){
                          --indice_x;
                          ++cpt;
                      }break;

        case DROITE : indice_y = (int)pos->y;
                      indice_x = (int)pos->x;
                      while(plateau->plateau[indice_y][indice_x] != 1){
                          ++indice_x;
                          ++cpt;
                      }break;

        default : break;
    }
    return cpt;
}

/*Si collision à gauche ou en haut (=selon dir_tmp) la vitesse est coupé, sinon aucune action*/
static void collision_coin_haut_gauche(Plateau const *plateau, Position *pos, double/*float*/ *vitesse, Direction *dir_tmp){
    int distance_du_mur;
    assert(NULL != plateau);
    assert(NULL != pos);
    assert(NULL != dir_tmp);
    assert(NULL != vitesse);
    distance_du_mur = distance_vers_mur(plateau, pos, dir_tmp);
    /*A CHANGER >>*/
    if(distance_du_mur > 1){return ;}
    switch(*dir_tmp){
        case GAUCHE: if(pos->x > (int)(pos->x) + 0.5){
                        if((int)(pos->y) + (*vitesse) > (int)(pos->y) + 1 - sqrt((1.0/4 - (pos->x - (int)(pos->x)) * (pos->x - (int)(pos->x))))){
                            *vitesse = 0.0;
                        }
                     }
                     break;
        case HAUT: if(pos->y < (int)(pos->y) + 0.5){
                     if((int)(pos->x) + (*vitesse) > (int)(pos->x) + 1 - sqrt((1.0/4 - (pos->y - (int)(pos->y)) * (pos->y - (int)(pos->y))))){
                         *vitesse = 0.0;
                     }
                  }
                  break;
        default : break;
    }
}

/*Si collision à droite ou en haut (=selon dir_tmp) la vitesse est coupé, sinon aucune action*/
static void collision_coin_haut_droite(Plateau const *plateau, Position *pos, double/*float*/ *vitesse, Direction *dir_tmp){
    int distance_du_mur;
    assert(NULL != plateau);
    assert(NULL != pos);
    assert(NULL != dir_tmp);
    assert(NULL != vitesse);
    distance_du_mur = distance_vers_mur(plateau, pos, dir_tmp);
    /*A CHANGER >>*/
    if(distance_du_mur > 1){return ;}
    switch(*dir_tmp){
        case DROITE: if(pos->x >= (int)(pos->x) + 0.5){
                        if((int)(pos->y) + (*vitesse) > (int)(pos->y) + 1 - sqrt((1.0/4 - (pos->x - (int)(pos->x)) * (pos->x - (int)(pos->x))))){
                            *vitesse = 0.0;
                        }
                     }
                     break;
        case HAUT: if(pos->y >= (int)(pos->y) + 0.5){
                     if((int)(pos->x) + (*vitesse) > (int)(pos->x) + 1 - sqrt((1.0/4 - (pos->y - (int)(pos->y)) * (pos->y - (int)(pos->y))))){
                         *vitesse = 0.0;
                     }
                  }
                  break;
        default : break;
    }
}

/*Si collision à gauche ou en bas (=selon dir_tmp) la vitesse est coupé, sinon aucune action*/
static void collision_coin_bas_gauche(Plateau const *plateau, Position *pos, double/*float*/ *vitesse, Direction *dir_tmp){
    int distance_du_mur;
    assert(NULL != plateau);
    assert(NULL != pos);
    assert(NULL != dir_tmp);
    assert(NULL != vitesse);
    distance_du_mur = distance_vers_mur(plateau, pos, dir_tmp);

    if(distance_du_mur > 1){return ;}
    switch(*dir_tmp){
        case GAUCHE: if(pos->x < (int)(pos->x) + 0.5){
                        if((int)(pos->y) + (*vitesse) > (int)(pos->y) + 1 - sqrt((1.0/4 - (pos->x - (int)(pos->x)) * (pos->x - (int)(pos->x))))){
                            *vitesse = 0.0;
                        }
                     }
                     break;
        case BAS: if(pos->y < (int)(pos->y) + 0.5){
                     if((int)(pos->x) + (*vitesse) > (int)(pos->x) + 1 - sqrt((1.0/4 - (pos->y - (int)(pos->y)) * (pos->y - (int)(pos->y))))){
                         *vitesse = 0.0;
                     }
                  }
                  break;
        default : break;
    }
}

/*Si collision à droite ou en bas (=selon dir_tmp) la vitesse est coupé, sinon aucune action*/
static void collision_coin_bas_droite(Plateau const *plateau, Position *pos, double/*float*/ *vitesse, Direction *dir_tmp){
    int distance_du_mur;
    assert(NULL != plateau);
    assert(NULL != pos);
    assert(NULL != dir_tmp);
    distance_du_mur = distance_vers_mur(plateau, pos, dir_tmp);
    if(distance_du_mur > 1){return ;}

    switch(*dir_tmp){
        case DROITE: if(pos->x >= (int)(pos->x) + 0.5){
                        if((int)(pos->y) + (*vitesse) > (int)(pos->y) + 1 - sqrt((1.0/4 - ((int)(pos->x) + 1 - pos->x) * ((int)(pos->x) + 1 - pos->x)))){
                            *vitesse = 0.0;
                        }
                    }
                    break;
        case BAS: if(pos->y >= (int)(pos->y) + 0.5){
                     if((int)(pos->x) + (*vitesse) > (int)(pos->x) + 1 - sqrt((1.0/4 - ((int)(pos->y) + 1 - pos->y) * ((int)(pos->y) + 1 - pos->y)))){
                        *vitesse = 0.0;
                     }
                  }
                  break;
        default : break;
    }

}

/*Retourne 0 si il n'y a aucune collision avec un mur et 1 sinon*/
int collision_contre_mur(Plateau const *plateau, Position *pos, Direction const *dir,double/* float*/ *vitesse){
    int distance_du_mur;
    Direction tmp_dir;
    assert(NULL != plateau);
    assert(NULL != pos);
    assert(NULL != dir);
    assert(NULL != vitesse);
    distance_du_mur = distance_vers_mur(plateau, pos, dir);
    if(distance_du_mur > 1) return 0;
    switch(*dir){
        case HAUT : if((int)(pos->y)  > (int)(pos->y) + 0.5){
                        *vitesse = VITESSE_NULLE;
                    }
                    tmp_dir = DROITE;
                    collision_coin_haut_droite(plateau, pos, vitesse, &tmp_dir);
                    tmp_dir = GAUCHE;
                    collision_coin_haut_gauche(plateau, pos, vitesse, &tmp_dir);
                    break;
        case BAS :  if((int)(pos->y)  > (int)(pos->y) + 0.5){
                        *vitesse = VITESSE_NULLE;
                    }
                    tmp_dir = DROITE;
                    collision_coin_bas_droite(plateau, pos, vitesse, &tmp_dir);
                    tmp_dir = GAUCHE;
                    collision_coin_bas_gauche(plateau, pos, vitesse, &tmp_dir);
                    break;
        case GAUCHE : if((int)(pos->x)  > (int)(pos->x) + 0.5){
                        *vitesse = VITESSE_NULLE;
                    }
                    tmp_dir = BAS;
                    collision_coin_bas_gauche(plateau, pos, vitesse, &tmp_dir);
                    tmp_dir = HAUT;
                    collision_coin_haut_gauche(plateau, pos, vitesse, &tmp_dir);
                    break;
        case DROITE : if((int)(pos->x)  > (int)(pos->x) + 0.5){
                        *vitesse = VITESSE_NULLE;
                    }
                    tmp_dir = BAS;
                    collision_coin_bas_droite(plateau, pos, vitesse, &tmp_dir);
                    tmp_dir = HAUT;
                    collision_coin_haut_droite(plateau, pos, vitesse, &tmp_dir);
                    break;
        default : break;
    }
    return 1;
}
