#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> /*Pour sleep*/
#include <string.h>

#include "partie.h"


/*****************************************************************************************************************************************/
/**
   Cette fonction teste si une case de l'échiquier est vide.
   @param part est la partie en cours
   @param c est la coordonnée de la case à tester
   @return 1 si la case est vide et 0 sinon
*/
int case_vide(partie_t *part, coordonnee_t c){

  if(piece_caractere(part->echiquier[c.x][c.y]) == '.')
    return 1;
  return 0;

}

/*****************************************************************************************************************************************/
/**
   Cette fonction modifie une case de l'échiquier de la partie en cours en insérant une piece dans une case donnée
   @param part est la partie en cours
   @param p est la piece qu'on veut déplacer
   @param c est la case dans laquelle on veut déplacer la piece
*/
void modifier_case(partie_t *part, piece_t p, coordonnee_t c){

  part->echiquier[c.x][c.y] =  p;
  
}

/*****************************************************************************************************************************************/
/**
   Cette fonction change le joueur de la partie
   @param part est la partie en cours, partie qu'on veut changer le joueur
*/
void changer_joueur(partie_t *part){

  part->joueur ++;
  part->joueur = part->joueur % 2;

}

/*****************************************************************************************************************************************/
/**
   Permet d'afficher sur le terminal l'échiquier d'une partie
   @param part est la partie à afficher
*/
void afficher_echiquier(partie_t *part){

  int i, j, k;
  
  for(i = 0; i < 10; i++){
    printf("\v");
    if(i < 6)
      printf("\t"); /*Pour centrer l'échiquier à l'écran*/
  }
  /*On affiche d'abord les coordonnées horizontales*/
  for(i = 0; i < 8; i++)
    printf("%d  ",i);
  printf("\t\t Liste des pieces capturées\n");
  printf("\v\v");
  printf("\t\t joueur 1");
  printf("\t\t");
  printf("0\t"); /*Pour la premiere coordonee verticale*/

  /*On affiche maintenant les pièces*/
  for(i = 0; i < 8;){
    for(j = 0; j < 8; j++){
      piece_afficher(part->echiquier[i][j]);
      printf("  ");
    }
    if(i == 0){
      if(!liste_pc_vide(part->lpc)){
	printf("\t\t ");
	afficher_liste_pc(part->lpc); /*On affiche la liste des pieces capturées*/
      }
    }
    printf("\n"); //On va à la ligne si on a affiché 8 cases
    i++;
    if(i < 8){
      if(i != 7){
	for(k = 0; k < 5 ; k++)
	  printf("\t");
      }
      else{
	printf("\t\t joueur 0");
	printf("\t\t");
      }
      printf("%d\t",i); //Pour afficher les coordonnées verticales
    }

  }

  
  printf("\v\v\v");

}

/******************************************************************************************************************************************/
/**
   Lorsque le déplacement est valide, est réalise le déplacement éffectuée et modifie les listes de la parties si nécessaire
   @param part est la partie en cours
   @param d et a sont les coordonnées des cases de départ là où la piece se trouve, et d'arrivée là où on veut la déplacer
*/
void deplacement(partie_t *part, coordonnee_t d, coordonnee_t a){
  
  int i = 0;
  coup_t *c;
  maillon_t *m;
  
  if(!case_vide(part, a)){
    /*Alors la pièce à cet emplacement sera capturée on l'ajoute donc à la liste des pièces capturées*/
    empiler_liste_pc(part->lpc, part->echiquier[a.x][a.y]);
    i++;
  }	  
  /*On modifie l'échiquier*/
  modifier_case(part, part->echiquier[d.x][d.y], a);
  part->echiquier[d.x][d.y] = piece_creer('G', '.');
  /*On ajoute le coup dans la liste des coups*/
  c = creer_coup(d, a, i);
  m = creer_maillon(c);
  liste_cj_ajouter_debut(part->lcj, m);
  /*Le pion se transforme en reine s'il a parcouru tout l'échiquier*/
  if(piece_caractere(part->echiquier[a.x][a.y]) == 'p' && a.x == 0)
    modifier_case(part, piece_creer('B', 'e'), a);
  if(piece_caractere(part->echiquier[a.x][a.y]) == 'P' && a.x == 7)
    modifier_case(part, piece_creer('N', 'E'), a);
  /*On change le joueur après chaque déplacement réalisé*/
  changer_joueur(part);

}

/******************************************************************************************************************************************/
/**
   Elle revient à la partie précédent le dernier coup réalisé. 
   Ainsi, l'échiquier et les listes reviennent à leur niveau prec : annule le dernier coup.
   @param la partie en cours
*/
   
void annuler_deplacement(partie_t *part){

  if(!liste_cj_vide(part->lcj)){
    maillon_t *m = liste_cj_extraire_debut(part->lcj);
    modifier_case(part, part->echiquier[m->coup->arrivee.x][m->coup->arrivee.y], m->coup->depart); 
    if(m->coup->capture == 0)
      part->echiquier[m->coup->arrivee.x][m->coup->arrivee.y] = piece_creer('G', '.');
    else /*Alors une piece a été capturée*/
      part->echiquier[m->coup->arrivee.x][m->coup->arrivee.y] = depiler_liste_pc(part->lpc);
    changer_joueur(part);
  }
  else
    printf("Impossible ! Liste vide.\n");

}

/******************************************************************************************************************************************/
/**
   Cette fonction demande aux joueurs de saisir une case et leur permet de réaliser un déplacement ou mettre fin à la partie.
   @return la coordonnéee de la case saisie.
*/ 
coordonnee_t saisie_case(){

  coordonnee_t res;
  int x, y;

  printf("Saisir une case : abscisse x, ordonné y compris entre 0 et 7\n\v"
	 "ou : -8- pour annuler le déplacement précédent\n"
	 "     -9- pour commencer une nouvelle partie\n"
	 "     -10- pour quitter la partie\n");
  
  scanf("%d", &x);
  if(x > 7) /*On a pas fait de déplacement; on a décidé de sortir ou d'annuler un déplacement*/
    res = creer_coordonnee(x, x);
  else{
    scanf("%d", &y);
    res = creer_coordonnee(x, y);
  }

  return res;
}


/******************************************************************************************************************************************/
/**
   Cette fonction alloue l'espace mémoire nécessaire pour une partie d'échec.
   Chaque case de l'échiquier peut être à vide ou conténir un pion ou une pièce. 
   Chaque liste de la partie est initialisée à vide.
   @return une partie allouée
*/
partie_t* partie_creer(){
  
  int i;
  partie_t *res = (partie_t*)malloc(sizeof(partie_t));

  res->echiquier = (piece_t**)malloc(8*sizeof(piece_t*));
  for(i=0; i<8; i++)
    res->echiquier[i] = malloc(8*sizeof(piece_t));
  
  res->lcj = liste_cj_initialiser();
  res->lpc = creer_liste_pc(32);/* 32 = 8*4 pieces qui peuvent etre capturées*/
  res->joueur = 0;
  
  return res;
  
}

/******************************************************************************************************************************************/
/**
   Libère l'espace mémoire occupée par une partie.
   @param l'espace mémoire à libérer.
*/
void partie_detruire(partie_t *part){

  int i;
  
  detruire_liste_pc(part->lpc);
  liste_cj_detruire(part->lcj);

  for(i = 0; i < 8; i++)
    free(part->echiquier[i]);
  free(part->echiquier);
  
  free(part);
  
}

/******************************************************************************************************************************************/
/**
   Sauvegarde la partie en cours de jeu dans un fichier entré par le joueur.
   @param part est la partie à sauvegarder.
   @param s est le chemin du fichier
*/
void partie_sauvegarder(partie_t *part, char *s){

  int i, j;
  FILE *f;

  if((f=fopen(s, "w")) != NULL){
    fprintf(f, "PL\n");
    for(i = 0; i < 8; i++){
      for(j = 0; j < 8; j++)
	fprintf(f,"%c", piece_caractere(part->echiquier[i][j]));
      fprintf(f,"\n");
    }
    fclose(f);
    printf("Sauvegarde réussie\n");
  }
  else
    printf("Sauvegarde échouée\n");
  
}

/******************************************************************************************************************************************/
/**
   Charge une partie qui a déjà été sauvegadée et permet aux joueurs de reprendre leur partie où ils l'ont laissée.
   @param un fichier f déjà ouvert dans le main. On teste le format du fichier avant d'appeler cette fonction.
   @return une partie chargée.
*/
partie_t* partie_charger(FILE *f){
  
  int i, j;
  partie_t *res = partie_creer();
  char c; /*Pour stocker les caracteres des pieces lus dans le flux*/ 

  fgetc(f);/*On a déjà lu le format dans le main avant d'appeler la fonction. Donc on va à la ligne.*/
  for(i = 0; i < 8; i++){
    for(j = 0; j < 8; j++){
      c =  fgetc(f);
      res->echiquier[i][j] = piece_identifier(c);
    }
    fgetc(f);
  }
  return res;
  
}

/******************************************************************************************************************************************/
/**
   Cette fonction initialise une partie d'échec.
   L'échiquier de nouvelle partie est chargée et initialisée.
   @return une structure partie initialisée.
*/
partie_t* partie_nouvelle(){

  FILE *f;
  int i, j;
  char c1[2];
  char c;

  partie_t *res = partie_creer();
  
  /*On charge le plateaux de début de partie*/
  if((f = fopen("Plateaux/plateaux_initialiser.plt", "r")) != NULL){
    fread(&c1, sizeof(char), 2, f);
    fgetc(f);//On connait déjà le format du fichier, pas besoin de le vérifier. On va directement à la ligne
    for(i = 0; i < 8; i++){
      for(j = 0; j < 8; j++){
	c =  fgetc(f);
	res->echiquier[i][j] = piece_identifier(c);
      }
      fgetc(f);
    }
    fclose(f);
  }
  else{
    printf("error\n");
    exit(0);
  }
 
  return res;
  
}

/******************************************************************************************************************************************/
/**
   Contient la boucle principale du jeu. Elle demande aux joueurs de jouer et réalise leur coup si celui-ci est valide tant qu'ils jouent. 
   Elle gère l'ajout et le retrait dans les listes de la partie si nécessaire.
   Elle permet la sauvegarde d'une partie lorsque ceux-ci décident de sortir du jeu.
   @param l'instance de la partie d'échec.
*/
void partie_jouer(partie_t *part){
  
  char fichier[60];
  int i, j = 0,  k; 
  coordonnee_t a;
  coordonnee_t d;


  part->joueur = 0;
  afficher_echiquier(part);
  
  do{
    
    printf("Au tour du joueur %d de jouer\n", part->joueur);
    d = saisie_case();
    
    if(d.x >= 0 && d.x < 8 && d.y >= 0 && d.y < 8){
      while(!droit(part, d)){
	printf("Vous n'avez pas le droit\n");
	d = saisie_case();
      }
      a = saisie_case();
      if(a.x >= 0 && a.x < 8 && a.y >= 0 && a.y < 8){
	if(deplacement_valide(part, d, a)){
	  deplacement(part, d, a);
	  afficher_echiquier(part); /*On affiche l'échiquier après chaque déplacement*/
	}
	else  /*Alors le joueur reste inchangé*/
	  printf("Déplacement non valide. Réessayez.\n");
      }
      else
	printf("Déplacement non valide. Réessayez.\n");
    }
    
    if(d.x == 8){
      annuler_deplacement(part);
      afficher_echiquier(part);
    }
    
    if(d.x == 9){
      printf("\n\v\v\v\t\t\t Nouvelle Partie\n");
      part = partie_nouvelle();
      partie_jouer(part);
    }
  }
  
  /*Les deplacements se chargent de changer le joueur*/

  while(d.x != 10); /*On pourra quitter la partie en entrant 10 à la premiere saisie*/
 
  
  /*On sort de la boucle donc on a décidé de quitter la partie*/
  
  do{
    if(j > 0)
      printf("Choix non valide\n"); /*On veut afficher un message d'erreur*/
    printf("Voulez - vous vraiment quitter la partie ?\n"
	   "-1- oui                  -0- non\n");
    scanf("%d", &k);
    j++;
  }
  while(k != 0 && k != 1);
   
  
  if(k == 0)
    partie_jouer(part);
  
  if(k == 1){
    j = 0;
    do{
      system("clear"); /*On efface l'ecran*/
      if(j > 0)
	printf("Choix non valide\n"); /*On veut afficher un message d'erreur*/
      printf("Voulez - vous sauvegarder votre partie en cours ?\n"
	     "-1- oui                                 -0- non\n");
      scanf("%d", &i);
      j++;
    }
    while(i != 0 && i != 1);
    
    if(i == 1){
      printf("Dans quels fichier dois - je sauvegarder votre partie ?\n\v"
	     "Entrez votre fichier .plt précédé du dossier Plateaux/ :\n");
      scanf("%60s", fichier);
      partie_sauvegarder(part, fichier);
      printf("Entrez maintenant votre fichier .part précédé du dossier Parties/ :\n");
      scanf("%60s", fichier);
      replay_sauvegarder(part, fichier); /*On donne aux joueurs la possibilité de rejouer une partie*/
    }
    printf("Au revoire\n");
  }
  
}

/******************************************************************************************************************************************/
/**
   Cette fonction donne l'occasion aux joueurs de rejouer une partie jouée. Elle sauvegarde les coups jouées durant la partie.
   @param la partie qu'on voudra rejouer.
   @param le chemin du fichier où on veut sauvgarder la partie jouée.
*/
void replay_sauvegarder(partie_t *part, char *s){

  maillon_t *m;
  FILE *f;
  
  if((f=fopen(s, "w")) != NULL){
    fprintf(f, "PR\n");
    for(m = part->lcj->dernier; m != NULL; m = m->precedent) /*On part du dernier au premier car on a ajouté au debut de la liste*/
      fprintf(f, "%d %d %d %d\n", m->coup->depart.x,  m->coup->depart.y,  m->coup->arrivee.x,  m->coup->arrivee.y);

    fclose(f);
    printf("Sauvegarde réussie\n");
  }
  else
    printf("Echec de la sauvegarde\n");
  
}

/******************************************************************************************************************************************/
/**
   charge la partie qu'on veut rejouer.
   Cette fonction charge dans un fichier la liste des coups joués durant une partie.
   @param le chemin du fichier dans lequel se trouvent les coups.
   @return la liste des coups joués chargés.
*/
liste_cj_t* replay_charger(FILE *f){
  
  int tab[4];
  coordonnee_t d, a;
  maillon_t *m;
  
  liste_cj_t *l = liste_cj_initialiser(); /*Pour stocker les coups chargés*/
  
  fgetc(f);/*Idem que partie charger*/
  
  while(!feof(f)){
    fscanf(f, "%d %d %d %d", &tab[0], &tab[1], &tab[2], &tab[3]);
    d = creer_coordonnee(tab[0], tab[1]);
    a = creer_coordonnee(tab[2], tab[3]);
    m = creer_maillon(creer_coup(d, a, 0));
    liste_cj_ajouter_fin(l, m);
  }
   
  return l;
  
}

/******************************************************************************************************************************************/
/**
   Cette fonction rejoue une partie déjà jouée par les joueurs.
   Elle execute tout les déplacements effectués lors de la partie sauvegardée.
   @param part est la partie qu'on va rejouer.
   @param f est le chemin où se trouve la liste des coups joués tout comme précédemment.
   @param t est pour "sleep", le temps entre deux animations.
*/
void replay_jouer(partie_t *part, FILE *f, double t){

  maillon_t *m;
  liste_cj_t *l = replay_charger(f);
  int i = 1;

  afficher_echiquier(part);
  while(i < l->taille){ /*Pour parcourir toute la liste*/
    m = liste_cj_extraire_debut(l);
    deplacement(part, m->coup->depart, m->coup->arrivee);
    sleep(t);
    afficher_echiquier(part);
  }
  liste_cj_detruire(l);
  printf("\n\v\v\t\t\t\t Fin d'animation. Votre partie est terminée.\n"
	 "\v\t\t\t\t\t\t Au revoire\n\v\v");
  
}


/******************************************************************************************************************************************/

/***********************************************LES DEPLACEMENTS**********************************************************/
/**
   Les fonctions de déplacements testent si un déplacement réalisé par un joueur est valide. 
   Elles assurent l'application des règles du jeu d'échec.
   @param case de départ de la pièce et celle où on veut la déplacer.
   @return 1 si le déplacement est valide et 0 sinon.
*/
/******************************************************************************************************************************************/
/**
   Vérifie que le joueur utilise bien une pièce de sa couleur et non celle de son adversaire ni une case vide.
   @param l'instance de la partie en cours.
   @param la case qu'on utilise.
   @return si le joueur a bien le droit.
*/ 
int droit(partie_t *part, coordonnee_t c){
  
  if(part->joueur == 0){ /*C'est le joueur blanc qui joue*/
    if(piece_couleur(part->echiquier[c.x][c.y]) == 'B')
      return 1;
  }
  else{ /*C'est le joueur noir qui joue*/
    if(piece_couleur(part->echiquier[c.x][c.y]) == 'N')
      return 1;
  }
  
  return 0;
  
}

/******************************************************************************************************************************************/

int deplacement_horizontal(coordonnee_t d, coordonnee_t a){

  if(a.x == d.x && a.y != d.y)/*L'ordonnée ne varie pas donc on reste sur la meme ligne droite horizontale; le deplacement est horizontal*/ 
    return 1;
  return 0;

}

/******************************************************************************************************************************************/

int deplacement_vertical(coordonnee_t d, coordonnee_t a){

   if(a.y == d.y && a.x != d.x)/*L'abssice ne varie pas donc on reste sur la meme ligne droite verticale; le deplacement est vertical*/ 
    return 1;
  return 0;

}

/******************************************************************************************************************************************/

int deplacement_diagonal(coordonnee_t d, coordonnee_t a){

  /*On teste si le deplacement est diagonal*/

  int i;
  for(i = 1; i < 7; i++){ /*On pourra sortir des coordonnées de l'échiquier mais on ne  risque rien car si ça arrive, arrivée sera toujours différents de depart +/- i dans ce cas*/

    if(abs(a.x - d.x) == i && abs(a.y - d.y) == i) 
      return 1;
  }

  return 0;

}

/******************************************************************************************************************************************/

/**
   Cette fonction teste si toutes les cases situées sur la ligne reliant la case de départ à la case de destination 
   privé de celles de depart et de destination sont inoccupées.
   @param la partie en cours.
   @param la case de départ et celle d'arrivée.
   @return s'il n'y a pas de pièces présents sur cette ligne.
*/
int test_case(partie_t *part, coordonnee_t d, coordonnee_t a){
  
  int i, j;
  coordonnee_t tmp;

  if(deplacement_horizontal(d, a)){
   
    if(a.y > d.y){
      for(i = d.y + 1; i < a.y;){ /*On ne teste ni la case de depart ni celle d'arrivee*/
	tmp = creer_coordonnee(d.x, i);
	if(case_vide(part, tmp))
	  i++; /*Car on augmente en coordonnée*/
	else
	  return 0; 
      }
    }
    else{
      for(i = d.y - 1; i > a.y;){
	tmp = creer_coordonnee(d.x, i);
	if(case_vide(part, tmp))
	  i--; /*Ici, on diminue*/
	else
	  return 0; 
      }
    }
    /*On sort de la boucle si toutes les cases parcourues sont vides*/
    return 1;
  }
  
  if(deplacement_vertical(d, a)){
    
    if(a.x > d.x){
      for(i = d.x + 1; i < a.x;){ /*On part de la case de départ à la case d'arrivée*/
	tmp = creer_coordonnee(i, d.y);
	if(case_vide(part, tmp))
	  i++; /*Car on augmente en coordonnée*/
	else
	  return 0; 
      }
    }
    else{
      for(i = d.x - 1; i > a.x;){
	tmp = creer_coordonnee(i, d.y);
	if(case_vide(part, tmp))
	  i--; /*Ici, on diminue*/
	else
	  return 0; 
      }
    }
    return 1;
  }


  if(deplacement_diagonal(d, a)){

    if(a.x < d.x && a.y < d.y){
      for(i = d.x - 1; i > a.x;){
	for(j = d.y - 1; j > a.y;){
	  tmp = creer_coordonnee(i, j);
	  if(case_vide(part, tmp)){
	    i--; j--;
	  }
	  else
	    return 0;
	}
      }
    }
    
    else if(a.x > d.x && a.y > d.y){
      for(i = d.x + 1;  i < a.x;){
	for(j = d.y + 1; j < a.y;){
	  tmp = creer_coordonnee(i, j);
	  if(case_vide(part, tmp)){
	    i--; j--;
	  }
	  else
	    return 0;
	}
      }
    }
    
    else if(a.x > d.x && a.y < d.y){
      for(i = d.x + 1; i < a.x;){
	for(j = d.y - 1; j > a.y;){
	  tmp = creer_coordonnee(i, j);
	  if(case_vide(part, tmp)){
	    i++; j--;
	  }
	  else
	    return 0;
	}
      }
    }
     
    else if(a.x < d.x && a.y > d.y){
      for(i = d.x - 1; i > a.x;){
	for(j = d.y + 1; j < a.y;){
	  tmp = creer_coordonnee(i, j);
	  if(case_vide(part, tmp)){
	  i--; j++;
	  }
	  else
	    return 0;
	}
      } 
    }
    
    return 1;
    
  }

  return 0; /*Ce n'est aucun des trois types de deplacements*/
  
}
   
/******************************************************************************************************************************************/

int deplacement_valide_pion(partie_t *part, coordonnee_t d, coordonnee_t a){
    
  if(part->joueur == 0){ /*Joueur blanc*/
    if(deplacement_vertical(d, a)){
      if(case_vide(part, a)){
	if(a.x == d.x - 1)
	  return 1;
	if(a.x == d.x - 2 && d.x == 6)
	  return 1;
      }
    }
    else{
      if(!case_vide(part, a)){
	if(a.x == d.x - 1 && a.y == d.y - 1)
	  return 1;
	if(a.x == d.x - 1 && a.y == d.y + 1)
	  return 1;
      }
    }
  }
  
  else{ /*Joueur noir*/
    if(deplacement_vertical(d, a)){
      if(case_vide(part, a)){
	if(a.x == d.x + 1)
	  return 1;
	if(a.x == d.x + 2 && d.x == 1)
	  return 1;
      }
    }
    else{
      if(!case_vide(part, a)){
	if(a.x == d.x + 1 && a.y == d.y - 1)
	  return 1;
	if(a.x == d.x + 1 && a.y == d.y + 1)
	  return 1;
      }
    }
  }
  
  return 0;

}

/******************************************************************************************************************************************/

int deplacement_valide_cavalier(coordonnee_t d, coordonnee_t a){

  if(abs(a.x - d.x) == 2 && abs(a.y - d.y) == 1)
    return 1;
  if(abs(a.x - d.x) == 1 && abs(a.y - d.y) == 2)
    return 1;

  return 0;

}

/******************************************************************************************************************************************/

int deplacement_valide_tour(coordonnee_t d, coordonnee_t a){
  
  if(deplacement_horizontal(d, a) || deplacement_vertical(d, a))
    return 1; 
  return 0;
    
}

/******************************************************************************************************************************************/

int deplacement_valide_fou(coordonnee_t d, coordonnee_t a){

  if(deplacement_diagonal(d, a))
    return 1;
  return 0;

}

/******************************************************************************************************************************************/

int deplacement_valide_roi(coordonnee_t d, coordonnee_t a){

  /*Le roi se déplace que d'une case*/
  
  if(deplacement_horizontal(d, a)){
    if(a.y == d.y + 1 || a.y == d.y - 1)
      return 1;
  }
    
  else if(deplacement_vertical(d, a)){
    if(a.x == d.x + 1 || a.x == d.x - 1)
      return 1;
  }
    
  else if(deplacement_diagonal(d,a)){
    if(abs(a.x - d.x) == 1 && abs(a.y - d.y) ==  1)
      return 1;
  }

  return 0;
  
}

/******************************************************************************************************************************************/

int deplacement_valide_reine(coordonnee_t d, coordonnee_t a){
  
  if(deplacement_valide_tour(d, a) || deplacement_valide_fou(d, a))
    return 1;
  return 0;

}

/******************************************************************************************************************************************/
/**
   Cette fonction identifie le type de pièce présent dans la case choisie au départ 
   et vérifie si le déplacement appelé est valide en appelant à son tour, le déplacement de la pièce correspondant. 
*/

int deplacement_valide(partie_t *part, coordonnee_t d, coordonnee_t a){

    
  if(piece_couleur(part->echiquier[d.x][d.y]) != piece_couleur(part->echiquier[a.x][a.y])){ /*Une piece ne peut pas bouffer une piece de meme couleur qu'elle*/

    if(piece_caractere(part->echiquier[d.x][d.y]) == 'C' || piece_caractere(part->echiquier[d.x][d.y]) == 'c')
      return deplacement_valide_cavalier(d, a);

    else{
      if(test_case(part, d, a)){
 
	if(piece_caractere(part->echiquier[d.x][d.y]) == 'P' || piece_caractere(part->echiquier[d.x][d.y]) == 'p')
	  return deplacement_valide_pion(part, d, a);
	
	if(piece_caractere(part->echiquier[d.x][d.y]) == 'T' || piece_caractere(part->echiquier[d.x][d.y]) == 't')
	  return deplacement_valide_tour(d, a);	
	
	if(piece_caractere(part->echiquier[d.x][d.y]) == 'F' || piece_caractere(part->echiquier[d.x][d.y]) == 'f')
	  return deplacement_valide_fou(d, a);
	
	if(piece_caractere(part->echiquier[d.x][d.y]) == 'R' || piece_caractere(part->echiquier[d.x][d.y]) == 'r')
	  return deplacement_valide_roi(d, a);
	
	if(piece_caractere(part->echiquier[d.x][d.y]) == 'E' || piece_caractere(part->echiquier[d.x][d.y]) == 'e')
	  return deplacement_valide_reine(d, a);
      }
    }
  }

  return 0; /*Aucun des pions au depart donc une case vide ou une piece de meme couleur a l'arrivee : le deplacement n'est pas valide. Ou le joueur n'a tout simplement pas le droit*/
  
}

/******************************************************************************************************************************************/
