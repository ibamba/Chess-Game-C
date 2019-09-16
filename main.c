#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "partie.h"


int main(int argc, char **argv){

  
  partie_t *jeu;
  FILE *f;
  double t;
  char c[3]; /*Pour la lecture du format des fichiers*/

  if(argc == 1){ /*Il n'y a pas d'argument entrée après celui de l'exécution du prog*/
    printf("\v\vBienvenu dans le jeu d'échec\n\v"
	   "Vous allez commencer une nouvelle partie\n");
    sleep(1);
    jeu = partie_nouvelle();
    partie_jouer(jeu);
  }
  
  else{ 
    
    if((f = fopen(argv[1], "r")) != NULL){
      fread(&c, sizeof(char), 2, f);
     
      if(!strncmp("PL", c, 2)){ /*On compare seulement les 2 prémiers caractères*/
	printf("\v\v\v\t\t\t Partie %s chargée\n", argv[1]);
	jeu = partie_charger(f);
	partie_jouer(jeu);
      }
      
      else if(!strncmp("PR", c, 2)){
	printf("\v\v\t\t\t\t Votre partie va rejouer\n");
	sleep(1);
	jeu = partie_nouvelle();
	if(argc == 2) /*Il n'y a pas de parametre pour l'animation donc animation par defaut*/
	  replay_jouer(jeu, f, 1);
	
	else if(argc > 2){
	  if(sizeof(argv[2]) == sizeof(double)){ /*On s'assure que le parametre est bien un double*/
	    t = argv[2][0];
	    replay_jouer(jeu, f, t);
	  }
	  else
	    printf(" %s n'est pas un réel. Erreur.\n", argv[2]);
	}
      }
      
      fclose(f);
    }
    
    else
      printf("Echec de la lecture du fichier %s\n", argv[1]);
    
  }
  
  partie_detruire(jeu);
  printf("\v\v\v");

  return EXIT_SUCCESS;

}
