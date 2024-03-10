#ifndef __COLLISION__
#define __COLLISION__

#define MARGE_DISTANCE 1.00
#include "Moteur_de_jeu.h"


/*verifie si un joueur est dans la position d'un objet du jeu
    @param joueur *g: pointeur vers jouieur
*/
int est_dans_zone_objet(Position *joueur, Position_obj *objet);
/*renvoie 1 si le joueur est sur un relique ou 0 sinon*/
/*int est_dans_relique(Joueur const *j, Relique const *r);*/

/*renvoie 1 si la pos du joueur est sur la meme pos que la tuile ou 0 sinon.*/
/*int est_dans_tuile(Joueur const *j, Tuile const *t);*/

/*verifie le gardien detecte le joeur*/
int gardien_detecte_joueur(Plateau *p);
/*verifie le gardien detecte une relique disparu*/
int gardien_detecte_relique(Plateau *plateau, double *sec);

/*Fonction qui calcule et renvoie la distance entre l'agent (Joueur/Gardien)
et le prochain mur par rapport aux coord actuelles*/
int distance_vers_mur(Plateau const *plateau, Position const *pos, Direction const *dir);
/*distance de collision contremur*/
int collision_contre_mur(Plateau const *plateau, Position *pos, Direction const *dir,double/* float*/ *vitesse);

#endif
