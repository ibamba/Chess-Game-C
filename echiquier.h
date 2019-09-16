#ifndef _ECHIQUIER_H
#define _ECHIQUIER_H

#include "piece.h"

typedef struct echiquier_s{

  piece_t **t;

} echiquier_t;


/********Déclaration des fonctions********/

echiquier_t* echiquier_initialiser();
void echiquier_detruire(echiquier_t *e);

/*****************************************/

#endif
