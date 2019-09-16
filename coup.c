#include <stdlib.h>
#include "coup.h"


/******************************************************************************/

coordonnee_t creer_coordonnee(int x, int y){

  coordonnee_t res;
  res.x = x;
  res.y = y;
  return res;

}

/*****************************************************************************/
  
coup_t* creer_coup(coordonnee_t d, coordonnee_t a, int c){

  coup_t *res =(coup_t*)malloc(sizeof(coup_t));
  res->depart = d;
  res->arrivee = a;
  res->capture = c;
  return res;
  
}

/******************************************************************************/
  
void detruire_coup(coup_t *c){

  free(c);

}

/******************************************************************************/
