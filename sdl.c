#include <stdio.h>
#include <stdlib.h>
#include "sdl.h"

/***Définition des fonctions***/

/***********************************************************************************/

sdl_t* creer_sdl(int max){
  sdl_t * res = (sdl_t *)malloc(sizeof(sdl_t));
  res->tab = (piece_t *)malloc(sizeof(piece_t) * max);
  res->taille_max = max;
  res->taille = 0;
  res->debut = 0;
  return res;
}

/*******************************************************************/

void detruire_sdl(sdl_t *s){
  free(s->tab);
  free(s);
}

/********************************************************************/

int sdl_vide(sdl_t *s){
  if(s->taille == 0)
    return 1;
  return 0;
}

/*********************************************************************/

int sdl_taille(sdl_t *s){
  return s->taille;
}

/*********************************************************************/

int sdl_max(sdl_t *s){
  return s->taille_max;
}

/*********************************************************************/

void afficher_sdl(sdl_t *s){
  int i, pos;
  for(i = 0, pos = s->debut; i<s->taille; i++, pos = ((pos+1)%s->taille_max)){
    piece_afficher(s->tab[pos]);
    printf("  ");
  }
}

/********************************************************************/

void sdl_ajouter_debut(sdl_t *s, piece_t p){
  if(s->taille != s->taille_max){
    s->tab[(s->debut + s->taille) % s->taille_max] = p;
    s->taille++;
  }
  else
    printf("Erreur : la structure est pleine\n");
}

/********************************************************************/

piece_t sdl_extraire_debut(sdl_t *s){
  piece_t res;
  if(!sdl_vide(s)){
    res = s->tab[s->debut];
    s->debut = (s->debut + 1) % s->taille_max;
    s->taille --;
  }
  else
    printf("Erreur : la liste est vide\n");
  return res;
}

/*******************************************************************/

piece_t sdl_extraire_fin(sdl_t *s){
  piece_t res;
  if(!sdl_vide(s)){
    s->taille--;
    res = s->tab[s->taille];
  }
  else
    printf("Erreur : la liste est vide\n");
  return res;
}

/*******************************************************************/
 
  
