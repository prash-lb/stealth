/*PAR MASSIOUANE MAIBECHE ET PRASHATH SIVAYANAMA*/

#define _GNU_SOURCE
#define _POSIX_C_SOURCE 1999309L
#define AJUSTEMENT_EXTRATIME 3
/*Uniquement car on utilise clock_gettime, car ce ,'est pas ansi C89'*/

#include "../include/Menu.h"
#include "../include/Score.h"
#include <time.h>

/*affiche le plateau en mode ascii*/
static void aff_plat(Plateau *plat){
    int i, j;
    printf("\n\n");
    for(i = 0; i < LARGEUR_PLATEAU; ++i){
        for(j = 0; j < LONGEUR_PLATEAU; ++j){
            if(plat->plateau[i][j] == 0){
                printf("  ");
            }
            else{
                printf("%d ", plat->plateau[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n\n");
}


int main(int argc, const char * const argv[]){
    int fin_de_partie;
    Plateau plateau;
    struct timespec new_time, end_time;
    double frametime, extratime;
    double sec, ms;
    struct timespec start, end;
    MLV_Keyboard_modifier mod;
    MLV_Keyboard_button sym;
    MLV_Button_state state;
    MLV_Event event;
    frametime = extratime = 0.0;
    fin_de_partie = 0;
    mod = MLV_KEYBOARD_KMOD_NONE;
    sym = MLV_KEYBOARD_NONE;
    state = MLV_RELEASED;
    event = MLV_NONE;

    srand(time(NULL));
    MLV_create_window("Stealth", "ka", LONGUEUR_FENETRE + EXTENSION, LARGEUR_FENETRE);
    create_map(&plateau);
    affiche_menu();
    clock_gettime(CLOCK_REALTIME, &start);

    while(fin_de_partie == 0){
        /*CALCUL_DE_TEMPS*/
        clock_gettime(CLOCK_REALTIME, &end);
        clock_gettime(CLOCK_REALTIME, &end_time);
        sec = (double) (end.tv_sec - start.tv_sec);
        dessine_plateau_graphique(&plateau, LONGEUR_PLATEAU, LARGEUR_PLATEAU, &sec);
        event = MLV_get_event(&sym, &mod, NULL, NULL, NULL, NULL, NULL, NULL, &state);

        deplacement_joueur(&plateau, &sym, &state, &mod);
        deplacement_gardien(&plateau);
        if(event == MLV_KEY){
            if(sym == MLV_KEYBOARD_t){
                aff_plat(&plateau);
                break;
            }
        }
        /*Mecanisme de jeu et tt*/
        fin_de_partie = gardien_detecte_joueur(&plateau);
        interaction_joueur_relique(&plateau);
        interaction_joueur_tuile(&plateau);
        interaction_gardien_gardien(&plateau);
        retour_mana_vers_tuile(&plateau);
        gardien_detecte_relique(&plateau, &sec);

        /*framerate*/
        clock_gettime(CLOCK_REALTIME, &new_time);
        frametime = new_time.tv_sec - end_time.tv_sec;
        frametime += (new_time.tv_sec - end_time.tv_sec) / 1.0E9;
        extratime = 1.0 / 60 - frametime;

        if(extratime > 0){
            MLV_wait_milliseconds((int)(extratime * 1000 * AJUSTEMENT_EXTRATIME));
        }
        /*fin de partie*/
        if(fin_de_jeu(&(plateau.joueur))){
            fin_de_partie = WIN;
        }
    }
    clock_gettime(CLOCK_REALTIME, &end);
    sec = (double) (end.tv_sec - start.tv_sec);
    ms = (double) ((end.tv_nsec - start.tv_nsec) / 1.0E9);
    ecran_fin_de_jeu(&fin_de_partie, &sec, &ms, &(plateau.mana_conso));

    printf("Durée de la partie = %.2fs\n", sec + ms);
    printf("Mana consommé = %d\n", plateau.mana_conso);
    MLV_free_window();
    return 0;
}
