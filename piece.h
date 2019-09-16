#ifndef _PIECE_H
#define _PIECE_H

typedef char couleur_t; /*Toutes les couleurs sont de types char*/
typedef char type_t; /*Tous les types sont de types char*/

typedef struct piece_s{

  couleur_t couleur;
  type_t type;

} piece_t;


/*****************************************************************************/

piece_t piece_creer(couleur_t coul, type_t t);
char piece_couleur(piece_t p);
piece_t piece_identifier(char c);
char piece_caractere(piece_t p);
void piece_afficher(piece_t p);


#endif
