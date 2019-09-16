#ifndef _SDL_H
#define _SDL_H

#include "piece.h"

typedef struct sdl_s{
  piece_t *tab;
  int taille_max;
  int taille;
  int debut;
} sdl_t;


sdl_t * creer_sdl(int max);
void detruire_sdl(sdl_t *s);
int sdl_vide(sdl_t *s);
int sdl_max(sdl_t *s);
void afficher_sdl(sdl_t *s);
void sdl_ajouter_debut(sdl_t *s, piece_t p);
piece_t sdl_extraire_debut(sdl_t *s);
piece_t sdl_extraire_fin(sdl_t *s);

#endif
