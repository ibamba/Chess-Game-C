#include <stdlib.h>
#include "echiquier.h"

/*******************Définition des fonctions******************************/

echiquier_t* echiquier_initialiser(){

  /*Allocation de la mémoire nécessaire pour l'échiquier de taille 8*8 */
  echiquier_t *res = (echiquier_t*)malloc(sizeof(echiquier_t));
  int i, j;
  res->t = (piece_t**)malloc(8*sizeof(piece_t*));
  for(i=0; i<8; i++)
    res->t[i] = malloc(8*sizeof(piece_t));

  /*Remplissage du tableau avec les pions; chaque pion, au début du jeu, a une position bien définie*/
  res->t[0][0] = piece_creer('N', 'T');
  res->t[0][1] = piece_creer('N', 'C');
  res->t[0][2] = piece_creer('N', 'F');
  res->t[0][3] = piece_creer('N', 'R');
  res->t[0][4] = piece_creer('N', 'E');
  res->t[0][5] = piece_creer('N', 'F');
  res->t[0][6] = piece_creer('N', 'C');
  res->t[0][7] = piece_creer('N', 'T');
  for(i=0; i<8; i++)
    res->t[1][i] = piece_creer('N', 'P');
  for(i=0; i<8; i++)
    res->t[6][i] = piece_creer('B', 'p');
  res->t[7][0] = piece_creer('B', 't');
  res->t[7][1] =piece_creer('B', 'c');
  res->t[7][2] =piece_creer('B', 'f');
  res->t[7][3] =piece_creer('B', 'r');
  res->t[7][4] =piece_creer('B', 'e');
  res->t[7][5] =piece_creer('B', 'f');
  res->t[7][6] =piece_creer('B', 'c');
  res->t[7][7] =piece_creer('B', 't');
  for(i=2; i<6; i++){
    for(j=0; j<8; j++)
      res->t[i][j] = piece_creer('G', '.');/*Les cases vides correspondent à des points disons de couleurs grises*/
  }
  
  return res;
}

/************************************************************************/
void echiquier_detruire(echiquier_t *e){
  int i = 0;
  for(; i<8; i++)
    free(e->t[i]);
  free(e->t);
  free(e);
}

/***********************************************************************/

