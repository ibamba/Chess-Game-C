#include <stdio.h>
#include <stdlib.h>
#include "liste_cj.h"

/****************************************************************************/

maillon_t* creer_maillon(coup_t *c){
  maillon_t *res = (maillon_t*)malloc(sizeof(maillon_t));
  res->coup = malloc(sizeof(coup_t));
  res->precedent = NULL;
  res->suivant = NULL;
  res->coup = c;
  return res;
}

/**************************************************************************/

void detruire_maillon(maillon_t *m){
  detruire_coup(m->coup);
  free(m);
}

/*****************************************************************************/

liste_cj_t* liste_cj_initialiser(){
  liste_cj_t *res = malloc(sizeof(liste_cj_t));
  res->premier = NULL;
  res->dernier = NULL;
  res->taille = 0;
  return res;
}

/*****************************************************************************/

int liste_cj_vide(liste_cj_t *l){
  if(l->taille == 0)
    return 1;
  return 0; 
}

/*****************************************************************************/

void liste_cj_ajouter_debut(liste_cj_t *l, maillon_t *m){
  if(liste_cj_vide(l))
    l->dernier = m;
  else{
    m->suivant = l->premier;
    l->premier->precedent = m;
  }
  l->taille++;
  l->premier = m;
}

/****************************************************************************/

void liste_cj_ajouter_fin(liste_cj_t *l, maillon_t *m){
  if(liste_cj_vide(l))
    l->premier = m;
  else{
    m->precedent = l->dernier;
    l->dernier->suivant = m;
  }
  l->dernier = m;
  l->taille++;
}

/******************************************************************************/

maillon_t* liste_cj_extraire_debut(liste_cj_t *l){
  maillon_t * res = l->premier;
  if(!liste_cj_vide(l)){
    l->premier=res->suivant;
    res->suivant=NULL;
    l->taille--;
    if(liste_cj_vide(l))
      l->dernier = NULL;
    else
      l->premier->precedent=NULL;
  }
  return res;
}

/******************************************************************************/

maillon_t* liste_cj_extraire_fin(liste_cj_t *l){
  maillon_t *res = l->premier;
  if(!liste_cj_vide(l)){
    l->premier = res->precedent;
    res->precedent = NULL;
    l->taille--;
    if(liste_cj_vide(l))
      l->premier = NULL;
    else
      l->dernier->suivant = NULL;
  }
  return res;
}

/******************************************************************************/

void liste_cj_detruire(liste_cj_t *l){
  while(!liste_cj_vide(l))
    detruire_maillon(liste_cj_extraire_debut(l));
  free(l);
}
/******************************************************************************/
