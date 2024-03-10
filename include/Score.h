#ifndef __SCORE__
#define __SCORE__

#define MAX_SCORE 10
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef struct score {
    int used_mana;
    double time;
    char username[20];
}Score;

typedef struct tab_score {
    Score score[MAX_SCORE];
    int element;
}Tab_score;

void saisie_ici(Score *new_score, double *sec, double *ms, int *mana_conso);
/*int first_score();*/
int add_score(Tab_score *s, Score new_score);
int read_score_file(Tab_score *tmp);
int save_score(Tab_score new_score);
#endif
