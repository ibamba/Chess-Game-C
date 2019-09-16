/*La liste des coups joués : cette liste est doublement chaînées.
  liste_cj = liste des coups joués */

#ifndef _LISTE_CJ_H
#define _LISTE_CJ_H

#include "coup.h"

typedef struct maillon_s{

  coup_t *coup;
  struct maillon_s *suivant;
  struct maillon_s *precedent;

} maillon_t;


typedef struct liste_cj_s{

  maillon_t *premier;
  maillon_t *dernier;
  int taille;

} liste_cj_t;


/**************************************************************************************************/

maillon_t* creer_maillon(coup_t *c);
void detruire_maillon(maillon_t *m);
liste_cj_t* liste_cj_initialiser();
int liste_cj_vide(liste_cj_t *l);
void liste_cj_ajouter_debut(liste_cj_t *l, maillon_t *m);
void liste_cj_ajouter_fin(liste_cj_t *l, maillon_t *m);
maillon_t* liste_cj_extraire_debut(liste_cj_t *l);
maillon_t* liste_cj_extraire_fin(liste_cj_t *l);                    
void liste_cj_detruire(liste_cj_t *l);


#endif
