#ifndef _PARTIE_H
#define _PARTIE_H

#include "liste_pc.c"
#include "liste_cj.h"

/**
   La structure partie contient la grille du jeu en elle même : l'échiquier, les listes des coups que joueront les joueurs et des pieces qui seront capturées et permet d'identifier le joueur qui jouera au tour suivant
 */

typedef struct partie_s{
  
  piece_t **echiquier;
  liste_pc_t *lpc;
  liste_cj_t *lcj;
  int joueur;

} partie_t;



/********************************Déclaration des fonctions**************************************************/

int case_vide(partie_t *part, coordonnee_t c);
void modifier_case(partie_t *part, piece_t p, coordonnee_t c);
void changer_joueur(partie_t *part);
void afficher_echiquier(partie_t *part);
void deplacement(partie_t *part, coordonnee_t d, coordonnee_t a);
void annuler_deplacement(partie_t *part);
coordonnee_t saisie_case();
partie_t* partie_creer();
void partie_detruire(partie_t *part);
void partie_sauvegarder(partie_t *part, char *s);
partie_t* partie_charger(FILE *f); 
partie_t* partie_nouvelle();
void partie_jouer(partie_t *part);
int droit(partie_t *part, coordonnee_t c);
void replay_sauvegarder(partie_t *part, char *s);
liste_cj_t* replay_charger(FILE *f);
void replay_jouer(partie_t *part, FILE *f, double t);

int deplacement_horizontal(coordonnee_t d, coordonnee_t a);
int deplacement_vertical(coordonnee_t d, coordonnee_t a);
int deplacement_diagonal(coordonnee_t d, coordonnee_t a);
int test_case(partie_t *part, coordonnee_t d, coordonnee_t a);
int deplacement_valide_pion(partie_t *part, coordonnee_t d, coordonnee_t a);
int deplacement_valide_cavalier(coordonnee_t d, coordonnee_t a);
int deplacement_valide_tour(coordonnee_t d, coordonnee_t a);
int deplacement_valide_fou(coordonnee_t d, coordonnee_t a);
int deplacement_valide_roi(coordonnee_t d, coordonnee_t a);
int deplacement_valide_reine(coordonnee_t d, coordonnee_t a);
int deplacement_valide(partie_t *part, coordonnee_t d, coordonnee_t a);
  


#endif

