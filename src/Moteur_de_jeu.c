#include "../include/Moteur_de_jeu.h"


/*Prashath*/

/*Fabrique le côté des murs*/
static void make_wall_on_board(int i, int j, int nb, int direction, Plateau *game){
    /*printf("Poser a la position x %d et y %d avec un nb de %d\n",i,j,nb);*/
    int cpt;

    assert(NULL != game);

    if(nb == 0){
        return;
    }
    if(direction == 0){
        for(cpt = 1; cpt < nb + 1; cpt++){
            game->plateau[i][j + cpt] = MUR;
        }
    }
    if(direction == 1){
        for(cpt = 1; cpt < nb + 1; cpt++){
            game->plateau[i][j - cpt] = MUR;
        }
    }
    if(direction == 2){
        for(cpt = 1; cpt < nb + 1; cpt++){
            game->plateau[i + cpt][j] = MUR;
        }
    }
    if(direction == 3){
        for(cpt = 1; cpt < nb + 1; cpt++){
            game->plateau[i-cpt][j] = MUR;
        }
    }
}

/**/
static int verification_case(int i, int j, Plateau const *game, int direction){
    int x, y;

    assert(NULL != game);

    if(i > minside - 1 && direction != 3 && direction != 2){
        for(x = 1; x < minside; x++){
            if(game->plateau[i - x][j] == MUR){
                return 0;
            }
        }
    }
    if(i < LARGEUR_PLATEAU - 10 && direction != 2 && direction != 3){
        for(y = 1; y < minside; y++){
            if(game->plateau[i + y][j] == MUR){
                return 0;
            }
        }
    }
    if(j < LONGEUR_PLATEAU - 10 && direction != 0 && direction != 1){
        for(x = 1; x < minside; x++){
            if(game->plateau[i][j + x] == MUR){
                return 0;
            }
        }
    }
    if(j > minside - 1 && direction != 1 && direction != 0){
        for(y = 1; y < minside; y++){
            if(game->plateau[i][j - y] == MUR){
                /*printf(" i = %d j = %d direction = %d 4\n",i,j,direction);*/
                return 0;
            }
        }
    }
    return 1;
}


static int lenght_of_wall_verification(int x, int y, Plateau const *game, int direction){
    int i, j, cpt;

    assert(NULL != game);

    cpt = 0;
    if(direction == 0 && y < LONGEUR_PLATEAU - 1){
        for(j = y + 1; j < LONGEUR_PLATEAU; ++j){
            if(game->plateau[x][j] == 1){
                return cpt;
            }
            if(verification_case(x, j, game, direction) == 0){
                return 0;
            }
            ++cpt;
        }
    }
    else if(direction == 1 && y > 0){
        for(j = y - 1; j >= 0; --j){
            if(game->plateau[x][j] == 1){
                return cpt;
            }
            if(verification_case(x, j, game, direction) == 0){
                return 0;
            }
            ++cpt;
        }
    }
    else if(direction == 3 && x > 0){
        for(i = x - 1; i >= 0; i--){
            if(game->plateau[i][y] == 1){
                return cpt;
            }
            if(verification_case(i, y, game, direction) == 0){
                return 0;
            }
            cpt++;
        }
    }
    else if(direction == 2 && x < LARGEUR_PLATEAU - 1){
        for(i = x + 1; i < LARGEUR_PLATEAU; i++){
            if(game->plateau[i][y] == MUR){
                return cpt;
            }
            if(verification_case(i, y, game, direction) == 0){
                return 0;
            }
            cpt++;
        }
    }
    return 0;
}

static int line_of_wall_respected(int x, int y, Plateau const *game, int direction){
    int i, j, cpt;

    assert(NULL != game);

    i = 0, j = 0, cpt = 0;

    if((direction == 0 || direction == 1)){
        if((direction == 0 && y > LONGEUR_PLATEAU - 1) || (direction == 1 && y < 1)){
            return 0;
        }
        for(i = x; i < LARGEUR_PLATEAU; i++){
            if(direction == 0 && game->plateau[i][y + 1] == MUR){
                return (cpt >= minside + 1) ? 1 : 0;
            }
            if(direction == 1 && game->plateau[i][y - 1] == MUR){
                return (cpt >= minside + 1) ? 1 : 0;
            }
            cpt++;
        }
    }
    if((direction == 2 || direction == 3)){
        if((direction == 2 && x > LARGEUR_PLATEAU - 1) || (direction == 3 && x < 1)){
            return 0;
        }
        for(j = y; j < LONGEUR_PLATEAU; j++){
            if(direction == 2 && game->plateau[x + 1][j] == MUR){
                return (cpt >= minside + 1) ? 1 : 0;
            }
            if(direction == 3 && game->plateau[x - 1][j] == MUR){
                return (cpt >= minside + 1) ? 1 : 0;
            }
            cpt++;
        }
    }
    return (cpt >= minside) ? 1 : 0;
}


static void generation_wall_on_game_by_line(double line, int direction, int nb, Plateau *game){
    int i, j, cpt;

    assert(NULL != game);

    cpt = i = j = 0;
    if(direction == 0 || direction == 1){
        for(j = 0; j < LONGEUR_PLATEAU; j++){
            for(i = 0; i < LARGEUR_PLATEAU; i++){
                if(game->plateau[i][j] == MUR){
                    cpt++;
                }
                if(game->plateau[i][j] == VIDE){
                    cpt = 0;
                }
                if(cpt >= (int)line && line_of_wall_respected(i, j, game, direction) == 1){
                    if(lenght_of_wall_verification(i, j, game, direction) > 6){
                        if(rand() % nb == 0){
                            make_wall_on_board(i, j, lenght_of_wall_verification(i, j, game, direction) - 3, direction, game);
                            return ;
                        }
                    }
                }
            }
        }
    }
    if(direction == 2 || direction == 3){
        for(i = 0; i < LARGEUR_PLATEAU; i++){
            for(j = 0; j < LONGEUR_PLATEAU; j++){
                if(game->plateau[i][j] == MUR){
                    cpt++;
                }
                if(game->plateau[i][j] == VIDE){
                    cpt = 0;
                }
                if(cpt >= (int)line && line_of_wall_respected(i, j, game, direction) ==1){
                    if(lenght_of_wall_verification(i, j, game, direction) > 6){
                        if(rand() % nb == 0){
                            make_wall_on_board(i, j, lenght_of_wall_verification(i, j, game, direction) - 3, direction, game);
                            return ;
                        }
                    }
                }
            }
        }
    }
}

static void generation_lenght_wall(double height, double lenght, int nb, Plateau *game){
    double x, y, line;
    int mur;

    assert(NULL != game);

    x = height < lenght ? lenght : height;
    y = height < lenght ? height : lenght;
    if(x < (2 * minside + 1)){
        return ;
    }
    if(x < (4 * minside)){
        if(rand() % 2 == 0){
            return ;
        }
    }
    line = x / 2;
    mur = rand() % 4 ;/* 0 droite, 1 gauche , 2 bas ,3 haut*/
    generation_wall_on_game_by_line(line, mur, nb, game);
    generation_lenght_wall(line, y, nb + 2, game);
    generation_lenght_wall(line, y, nb + 2, game);
}


static void generation_wall_ext(Plateau *game){
    int i, j;

    assert(NULL != game);

    for(i = 0; i < LARGEUR_PLATEAU; i++){
        for(j = 0; j < LONGEUR_PLATEAU; j++){
            if(i == 0 || i == LARGEUR_PLATEAU - 1 || j == 0 || j == LONGEUR_PLATEAU - 1){
                game->plateau[i][j] = MUR;
            }
            else{
                game->plateau[i][j] = VIDE;
            }
        }
    }
}



static int not_on_openside(int x, int y, Plateau const *game){
    int i, hor, vertic;

    assert(NULL != game);

    i = 0, hor = 0, vertic = 0;
    for(i = 1; i <= 3; i++){
        if(game->plateau[x - i][y] == MUR){
            hor++;
            break;
        }
    }
    for(i = 1; i <= 3; i++){
        if(game->plateau[x + i][y] == MUR){
            hor++;
            break;
        }
    }
    for(i = 1; i <= 3; i++){
        if(game->plateau[x][y - i] == MUR){
            vertic++;
            break;
        }
    }
    for(i = 1; i <= 3; i++){
        if(game->plateau[x][y + i] == MUR){
            vertic++;
            break;
        }
    }
    if(vertic == 2 || hor == 2){
        return 0;
    }
    return 1;
}


static int position_verification(int x, int y, Plateau const *game){
    int value;

    assert(NULL != game);
    value = (int)(sqrt((1 - x)*(1 - x) + (1 - y)*(1 - y)));
    if(game->plateau[x][y] == VIDE && value >= DISTANCE_MIN_JOUEUR_GARDIEN_OBJ && not_on_openside(x, y, game) == 1){
        return 1;
    }
    return 0;
}


static void init_Gardien(Plateau *game){
    int i, x, y;

    assert(NULL != game);

    x = 0, y = 0;
    for(i = 0; i < NB_GARDIEN; i++){
        initalise_gardien(&(game->gardien[i]));
        while(1){
            x = 1 + rand() % 57;
            y = 1 + rand() % 42;
            if(position_verification(x, y, game) == 1){
                game->gardien[i].pos.x = x;
                game->gardien[i].pos.y = y;
                break;
            }
        }
    }
}

static void init_Relique(Plateau *game){
    int i, x, y;

    assert(NULL != game);

    x = 0, y = 0;
    for(i = 0; i < NB_RELIQUE; i++){
        initialise_relique(&(game->relique[i]));
        while(1){
            x = 1 + rand() % 57;
            y = 1 + rand() % 42;
            if(position_verification(x, y, game) == 1){
                game->relique[i].pos.x = x;
                game->relique[i].pos.y = y;
                break;
            }
        }
    }
}

static void init_tuile(Plateau *game){
    int i, x, y;

    assert(NULL != game);

    x = 0, y = 0;
    for(i = 0; i < NB_TUILE; i++){
        game->tuile[i].mana = QUANTITE_MANA_TUILE;
        game->tuile[i].etat = NON_RECUPERER;
        while(1){
            x = 1 + rand() % 56;
            y = 1 + rand() % 42;
            if(position_verification(x, y, game) == 1){
                game->tuile[i].pos.x = x;
                game->tuile[i].pos.y = y;
                break;
            }
        }
    }
}

static void init_plateau(Plateau *p){
    int i, j;

    assert(NULL != p);

    for(i = 0; i < LARGEUR_PLATEAU; ++i){
        for(j = 0; j < LONGEUR_PLATEAU; ++j){
            p->plateau[i][j] = VIDE;
        }
    }
}


static void init_objects_in_map(Plateau *game){
    int i;

    assert(NULL != game);

    initialise_joueur(&(game->joueur));
    game->cpt_mana = 0;
    game->mana_conso = 0;
    init_Gardien(game);
    init_Relique(game);
    init_tuile(game);
    game->plateau[(int)game->joueur.pos.x][(int)game->joueur.pos.y] = JOUEUR;
    for(i = 0; i < NB_GARDIEN; i++){
        game->plateau[(int)(game->gardien[i].pos.x)][(int)(game->gardien[i].pos.y)] = GARDIEN;
    }
    for(i = 0; i < NB_RELIQUE; i++){
        game->plateau[game->relique[i].pos.x][game->relique[i].pos.y] = RELIQUE;
    }
    for(i = 0; i < NB_TUILE; i++){
        game->plateau[game->tuile[i].pos.x][game->tuile[i].pos.y] = TUILE;
    }
}



void create_map(Plateau *game){
    assert(NULL != game);

    init_plateau(game);
    generation_wall_ext(game);
    generation_lenght_wall(58.0, 43.0, 1, game);
    init_objects_in_map(game);
}


/*Change l'etat d'un objet ou d'une relique*/
void change_etat_obj(Etat_objet *o){
    assert(NULL != o);

    switch(*o){
        case NON_RECUPERER : *o = RECUPERER; break;
        case RECUPERER : *o = NON_RECUPERER; break;
        default : printf("ETAT INCORRECT !\n"); break;
    }
}
