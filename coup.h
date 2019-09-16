#ifndef _COUP_H
#define _COUP_H


typedef struct coordonnee_s{

  int x;
  int y;

} coordonnee_t;

typedef struct coup_s{

  coordonnee_t depart;
  coordonnee_t arrivee;
  int capture;

} coup_t;

/*****************************************************************************/

coordonnee_t creer_coordonnee(int x, int y);
coup_t* creer_coup(coordonnee_t d, coordonnee_t a, int c);
void detruire_coup(coup_t *c);

#endif
