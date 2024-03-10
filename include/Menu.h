#ifndef __MENU__
#define __MENU__

#define NB_CASE_HAUTEUR 60
#define NB_CASE_LARGEUR 45
#define HAUTEUR_FENETRE LONGUEUR_FENETRE
#define DIFFERENCE_HAUTEUR HAUTEUR_FENETRE / NB_CASE_HAUTEUR
#define DIFFERENCE_LARGEUR LARGEUR_FENETRE / NB_CASE_LARGEUR
#define DELAI_ATTENTE 5
#define LANCE_JEU 3
#define OPTION_JEU 2
#define LOOSE 1
#define WIN 2
#define INCREMENTE_SCORE(i) (i + 1)
#include "Moteur_graphique.h"
#include "Score.h"
#include <assert.h>

typedef enum {
    MENU,
    JEU,
    OPTION
}Menu;

typedef enum {
    RETOUR,
    AUTRE
}Retour;


void fabrique_case_menu(char *nom_case, int taille_interlinge, int type_case);
void fabrique_case_retour(char *nom_case, int taille_interlinge, int largeur);
void affiche_case_menu(char *nom_case_1, char *nom_case_2, int taille_interlinge, int type_case_1, int type_case_2);
void affiche_option(char *nom_case_1, char *nom_case_2, int taille_interlinge, int type_case_1, int type_case_2);
void affiche_menu();
void ecran_fin_de_jeu(int *fin_de_jeu, double *s, double *ms, int *mana);
void affiche_score(double *s, double *ms, int *mana);
void affiche_score_bis(Tab_score *tmp);

#endif
