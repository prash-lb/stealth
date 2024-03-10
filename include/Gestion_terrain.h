#ifndef __GESTION_TERRAIN__
#define __GESTION_TERRAIN__

#include "Collision.h"
#include "MLV/MLV_all.h"
#include <unistd.h>

/*Toute les actiosn se fonct avec le plateau.*/

/*Interaction entre le joueur et le plateau.*/
int interaction_joueur_relique(Plateau *p);
/*Interaction entre le joueur et la tuile.*/
int interaction_joueur_tuile(Plateau *p);
/*Deplacement du joeur*/
void deplacement_joueur(Plateau *plateau, MLV_Keyboard_button *sym, MLV_Button_state *state, MLV_Keyboard_modifier *mod);
/*Deplacement des gardien*/
void deplacement_gardien(Plateau *plateau);
/*faire en sorte de recevoir les 2 gardiens qui veulent se rentrer dedans et les renvoyant dans des direction differente*/
void interaction_gardien_gardien(Plateau *p);
void retour_mana_vers_tuile(Plateau *plateau);
void sortie_du_mode_panique(Plateau *plateau);
/*retourne 1 si le joueur possede les 3 reliques et qu'il se trouve dans ses coord initiale, ou 0 sinon.*/
int fin_de_jeu(Joueur const *j);


#endif
