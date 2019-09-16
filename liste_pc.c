/*La liste des pièces capturées : cette liste fonctionne comme une file.
  liste_pc = liste_des_pièces_capturées*/

#include "sdl.h"

typedef sdl_t liste_pc_t;

#define creer_liste_pc(max) creer_sdl((max))

#define detruire_liste_pc(s) detruire_sdl((s))

#define liste_pc_vide(s) sdl_vide((s))

#define liste_pc_taille(s) sdl_taille((s))

#define liste_pc_max(s) sdl_max((s))

#define afficher_liste_pc(s) afficher_sdl((s))

#define empiler_liste_pc(p,x) sdl_ajouter_debut((p),(x))

#define depiler_liste_pc(p) sdl_extraire_fin((p))
