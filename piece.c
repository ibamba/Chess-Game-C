#include <stdlib.h>
#include <stdio.h>

#include "piece.h"
#include <ctype.h> /*Pour islower */



/*****Définition des fonctions qui utilisent la strucure piece*****/


/****************************************************************************/

piece_t piece_creer(couleur_t coul, type_t t){
  piece_t res;
  res.couleur = coul;
  res.type = t;
  return res;
}

/******************************************************************************/

char piece_couleur(piece_t p){
  return p.couleur;
}

/******************************************************************************/

piece_t piece_identifier(char c){
  piece_t res;
  res.type = c;
  if(c == '.')
    res.couleur = 'G'; /*Les cases vides sont représentées par des . disont de couleurs grises.*/
  else if( islower(c) > 0) /*Teste si c est en miniscule*/
    res.couleur = 'B';
  else
    res.couleur = 'N';
  return res;
}

/******************************************************************************/

char piece_caractere(piece_t p){
  return p.type;
}

/*****************************************************************************/

void piece_afficher(piece_t p){

  printf("%c", p.type);
  
}

/****************************************************************************/

