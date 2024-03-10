#ifndef __RELIQUE__
#define __RELIQUE__


#include "Deplacement.h"
#include <assert.h>


typedef enum{
    NON_RECUPERER,
    RECUPERER
}Etat_objet;

typedef struct relique{
    Etat_objet etat;
    Position_obj pos;
}Relique;


/*initialise la reliques
    @Relique *r: pointeur sur relique
*/
void initialise_relique(Relique *r);

/*affiche info relique
    @Relique *r: pointeur sur relique
*/
void affiche_info_relique(Relique const *r);

#endif
