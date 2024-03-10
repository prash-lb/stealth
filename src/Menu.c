#include "../include/Menu.h"


/*Fonction pour afficher une case du menu*/
void fabrique_case_menu(char nom_case[], int taille_interlinge, int type_case){
    MLV_draw_adapted_text_box(
        ((HAUTEUR_FENETRE - strlen(nom_case) * DIFFERENCE_HAUTEUR) + EXTENSION) / 2,
        LARGEUR_FENETRE / type_case,
        nom_case,
        taille_interlinge,
        MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
        MLV_TEXT_CENTER
    );
}

void fabrique_case_retour(char nom_case[], int taille_interlinge, int largeur){
    MLV_draw_adapted_text_box(
        ((HAUTEUR_FENETRE - strlen(nom_case) * DIFFERENCE_HAUTEUR) + EXTENSION) / 2,
        largeur,
        nom_case,
        taille_interlinge,
        MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
        MLV_TEXT_CENTER
    );
}

void affiche_case_menu(char nom_case_1[], char nom_case_2[], int taille_interlinge, int type_case_1, int type_case_2){
    MLV_clear_window(MLV_COLOR_BLACK);
    fabrique_case_menu(nom_case_1, taille_interlinge, type_case_1);
    fabrique_case_menu(nom_case_2, taille_interlinge, type_case_2);
    MLV_actualise_window();
}

/*temporaire*/


void affiche_option(char nom_case_1[], char nom_case_2[], int taille_interlinge, int type_case_1, int type_case_2){
    char lance_jeu[10];
    char retour[10];
    int x, y;
    int n, clic_x, clic_y;
    Retour etat;
    FILE *file;
    size_t read_element;
    Tab_score tmp;

    file = fopen("score", "rb");
    if(NULL == file){
        fprintf(stderr, "Erreur lors de l'ouverture du fichier score !\n");
        exit(EXIT_FAILURE);
    }
    read_element = fread(&tmp, sizeof(tmp), 1, file);
    fclose(file);
    if(read_element == 0){
        fprintf(stderr, "Erreur lors de la lecture de votre fichier.\n");
    }

    x = ((HAUTEUR_FENETRE - strlen(retour) * DIFFERENCE_HAUTEUR) + EXTENSION) / 2;
    y = LARGEUR_FENETRE;
    n = 0;
    etat = AUTRE;
    sprintf(lance_jeu, "SCORES");
    sprintf(retour, "RETOUR");
    /*Action*/
    MLV_clear_window(MLV_COLOR_BLACK);
    fabrique_case_menu(lance_jeu, taille_interlinge, LARGEUR_FENETRE);
    fabrique_case_retour(retour, taille_interlinge, LARGEUR_FENETRE - (taille_interlinge * 3 + 5));
    affiche_score_bis(&tmp);
    MLV_actualise_window();
    while(n == 0){
        MLV_wait_mouse(&clic_x, &clic_y);
        if(clic_x <= (x + strlen(retour) * (taille_interlinge + 3)) && clic_x >= x && clic_y <= y && clic_y >= (y - (4 * taille_interlinge) + 5)){
            etat = RETOUR;
            n = 1;
        }
        switch(etat){
            case RETOUR : affiche_case_menu(nom_case_1, nom_case_2, taille_interlinge, type_case_1, type_case_2); break;
            default : break;
        }
    }
}

/*fct qui affiche le menu*/
void affiche_menu(){
    char lance_jeu[15];
    char option[15];
    int taille_interlinge;
    int clic_x, clic_y, x, y_jeu, y_opt;
    int n;
    Menu etat;

    n = 0;
    taille_interlinge = 10;
    etat = MENU;
    sprintf(lance_jeu, "Lancer Le Jeu");
    sprintf(option, "Scores de Jeu");

    x = ((HAUTEUR_FENETRE - strlen(lance_jeu) * DIFFERENCE_HAUTEUR) + EXTENSION) / 2;
    y_jeu = LARGEUR_FENETRE / LANCE_JEU;
    y_opt = LARGEUR_FENETRE / OPTION_JEU;
    /*Action*/
    /*affichage des cases pour lance et option */
    affiche_case_menu(lance_jeu, option, taille_interlinge, LANCE_JEU, OPTION_JEU);
    MLV_actualise_window();
    /*Attente_clic etc pour option et lance jeu*/
    while(n == 0){
        etat = MENU;
        MLV_wait_mouse(&clic_x, &clic_y);
        if(clic_x <= (x + taille_interlinge*(taille_interlinge + 1)) && clic_x >= x && clic_y >= y_jeu && clic_y <= (y_jeu + (3 * taille_interlinge) + 5)){
            etat = JEU;
            n = 1;
        }
        else if(clic_x <= (x + taille_interlinge*(taille_interlinge + 1)) && clic_x >= x && clic_y >= y_opt && clic_y <= (y_opt + (3 * taille_interlinge) + 5)){
            etat = OPTION;
        }
        switch(etat){
            case JEU : break;
            case OPTION : affiche_option(lance_jeu, option, taille_interlinge, LANCE_JEU, OPTION_JEU); break;
            default : break;
        }
    }
    MLV_actualise_window();
}

static void ecran_gagnant(double *s, double *ms, int *mana){
    char win[100];

    assert(NULL != s);
    assert(NULL != ms);
    assert(NULL != mana);

    sprintf(win, "You win this game, your time is %.2fs and you use %d mana", *s + *ms, *mana);
    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_draw_text((LONGUEUR_FENETRE - EXTENSION * 3) / 2,(LARGEUR_FENETRE) / 2, win, MLV_COLOR_ORANGE);
    MLV_actualise_window();
    sleep(DELAI_ATTENTE);
    affiche_score(s, ms, mana);
}

static void ecran_perdant(){
    MLV_Image *pic;
    pic = MLV_load_image("loose.jpg");
    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_draw_image(pic, 0, EXTENSION);
    MLV_actualise_window();
    sleep(DELAI_ATTENTE);
    MLV_free_image(pic);
}

void ecran_fin_de_jeu(int *fin_de_jeu, double *s, double *ms, int *mana){

    switch(*fin_de_jeu){
        case LOOSE : ecran_perdant(); break;
        case WIN : ecran_gagnant(s, ms, mana); break;
        default : break;
    }
}

void affiche_score(double *s, double *ms, int *mana){
    int quit;
    MLV_Keyboard_button sym;
    Tab_score tmp;
    Score new_score;
    FILE *file;
    size_t read_element;

    assert(NULL != s);
    assert(NULL != ms);
    assert(NULL != mana);

    file = fopen("score", "rb");
    if(NULL == file){
        fprintf(stderr, "Erreur lors de l'ouverture du fichier score !\n");
        exit(EXIT_FAILURE);
    }
    read_element = fread(&tmp, sizeof(tmp), 1, file);
    fclose(file);
    if(read_element == 0){
        fprintf(stderr, "Erreur lors de la lecture de votre fichier.\n");
    }
    quit = 0;

    MLV_draw_text((LONGUEUR_FENETRE - EXTENSION * 3) / 2,(LARGEUR_FENETRE + EXTENSION) / 2, "Go to the terminal", MLV_COLOR_ORANGE);
    MLV_actualise_window();
    saisie_ici(&new_score, s, ms, mana);
    add_score(&tmp, new_score);

    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_draw_text(0, TAILLE_CASE, "Press -s to print score", MLV_COLOR_ORANGE);
    MLV_draw_text(0, TAILLE_CASE * 2, "Press -q to quit", MLV_COLOR_ORANGE);
    MLV_actualise_window();
    while(quit == 0){
        MLV_wait_event(&sym, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
        switch(sym){
            case MLV_KEYBOARD_s : affiche_score_bis(&tmp);
                                  break;
            case MLV_KEYBOARD_q : quit = 1;
                                  break;
            default : break;
        }
    }
    save_score(tmp);
}


void affiche_score_bis(Tab_score *all_score){
    int i;
    char tmp[20];


    MLV_draw_text(100, TAILLE_CASE * 4, "- Position -", MLV_COLOR_ORANGE);
    MLV_draw_text(250, TAILLE_CASE * 4, "- Username -", MLV_COLOR_ORANGE);
    MLV_draw_text(600, TAILLE_CASE * 4, "- Time in sec -", MLV_COLOR_ORANGE);
    MLV_draw_text(800, TAILLE_CASE * 4, "- Mana used -", MLV_COLOR_ORANGE);
    for(i = 0; i < all_score->element; ++i){
        sprintf(tmp, "%d", i + 1);
        MLV_draw_text(100, TAILLE_CASE * (4 * INCREMENTE_SCORE(i)), tmp, MLV_COLOR_WHITE);
        MLV_draw_text(250, TAILLE_CASE * (4 * INCREMENTE_SCORE(i)), all_score->score[i].username, MLV_COLOR_WHITE);
        sprintf(tmp, "%.2f", all_score->score[i].time);
        MLV_draw_text(600, TAILLE_CASE * (4 * INCREMENTE_SCORE(i)), tmp, MLV_COLOR_WHITE);
        sprintf(tmp, "%d", all_score->score[i].used_mana);
        MLV_draw_text(800, TAILLE_CASE * (4 * INCREMENTE_SCORE(i)), tmp, MLV_COLOR_WHITE);
    }
    MLV_actualise_window();
}
