#include "../include/Score.h"

static void choose_username(char pseudo[]){
    printf("Entrer un pseudo :");
    scanf("%s", pseudo);
}


void saisie_ici(Score *new_score, double *sec, double *ms, int *mana_conso){
    assert(NULL != mana_conso);
    assert(NULL != ms);
    assert(NULL != sec);
    assert(NULL != new_score);
    choose_username(new_score->username);
    new_score->time = *sec + *ms;
    new_score->used_mana = *mana_conso;
}


/*returns 0 if yours score is bad and 1 if your score is good*/
int add_score(Tab_score *s, Score new_score){
    int i, flag;
    assert(NULL != s);
    flag = 0;
    s->score[s->element].username[0] = '\0';
    s->score[s->element].time = 0.0;
    s->score[s->element].used_mana = 0;
    for(i = 0; i <= s->element; ++i){
        if(s->score[i].username[0] == '\0' && s->score[i].time == 0.0 && s->score[i].used_mana == 0){
            strcpy(s->score[i].username, new_score.username);
            s->score[i].time = new_score.time;
            s->score[i].used_mana = new_score.used_mana;
            s->element += 1;
            flag = 1;
            break;
        }
        else if(s->score[i].used_mana > new_score.used_mana && s->element >= MAX_SCORE){
            strcpy(s->score[i].username, new_score.username);
            s->score[i].time = new_score.time;
            s->score[i].used_mana = new_score.used_mana;
            flag = 1;
        }
    }
    return (flag == 0)? 0 : 1;
}


int read_score_file(Tab_score *tmp){
    FILE *file;
    size_t read_element;
    assert(NULL != tmp);
    file = fopen("score", "rb");
    if(NULL == file){
        fprintf(stderr, "Erreur lors de l'ouverture du fichier score !\n");
        return 1;
    }
    read_element = fread(tmp, sizeof(tmp), 1, file);
    fclose(file);
    if(read_element == 0){
        fprintf(stderr, "Erreur lors de la lecture de votre fichier.\n");
        return 2;
    }
    return 0;
}

int save_score(Tab_score new_score){
    FILE *file;
    size_t number_element;

    file = fopen("score", "wb");
    if(NULL == file){
        fprintf(stderr, "Erreur lors de l'ouverture du fichier score !\n");
        return 1;
    }
    number_element = fwrite(&new_score, sizeof(new_score), 1, file);
    fclose(file);
    if(number_element == 0){
        fprintf(stderr, "Erreur lors de la sauvegarde, fichier non sauvegardé\n");
        return 2;
    }
    return 0;
}


/*Used to initialize the score*/
/*

static void build_empty_score(Score *s){
    s->username[0] = '\0';
    s->time = 0.0;
    s->used_mana = 0;
}

int first_score(){
    int i;
    FILE *file;
    size_t number_element;
    Tab_score new_score;

    file = fopen("score", "wb");
    if(NULL == file){
        fprintf(stderr, "Erreur lors de l'ouverture du fichier score !\n");
        return 1;
    }
    new_score.element = 0;
    for(i = 0; i < MAX_SCORE; ++i){
        build_empty_score(&(new_score.score[i]));
        print_score(&new_score.score[i]);
    }
    number_element = fwrite(&new_score, sizeof(new_score), 1, file);
    fclose(file);
    if(number_element == 0){
        fprintf(stderr, "Erreur lors de la sauvegarde, fichier non sauvegardé\n");
        return 2;
    }
    return 0;
}

*/
