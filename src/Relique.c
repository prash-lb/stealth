#include "../include/Relique.h"


/*massi*/

/*Initialise une relique*/
void initialise_relique(Relique *r){
    assert(NULL != r);

    r->etat = NON_RECUPERER;
}


/*affiche TEMPORAIRE*/
/*static*/ void affiche_info_relique(Relique const *r);

void affiche_info_relique(Relique const *r){
    assert(NULL != r);
    switch(r->etat){
        case NON_RECUPERER : printf("NON RECUPERER\n"); break;
        case RECUPERER : printf("RECUPERER\n"); break;
        default : printf("ETAT INCORRECT !\n"); break;
    }
    printf("Position [x][y] : [%d][%d]\n", r->pos.x, r->pos.y);
}
