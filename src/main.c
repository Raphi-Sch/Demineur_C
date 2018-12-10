#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "grille.h"
#include "setup.h"
#include "affichage.h"
#include "liste.h"
#include "save.h"

enum choix_t {QUITTER, CONTINUE, GAGNER, PERDU};

//Lancer normal 	./demineur
//Lancer debug  	./demineur debug
//Lancer auto	 	./demineur auto

int main(int argc, char * argv[]){
	//Paramètres de lancement
	int debug = 0, autoplay = 0;
	if(argc > 1){
		if(!strcmp(argv[1], "debug"))
			debug = 1;
		if(!strcmp(argv[1], "auto"))
			autoplay = 1;
	}

	//Variables Générales
	int size;
	grid_t * active;
	grid_t * background;
	enum choix_t continuer_prgm = CONTINUE, continuer_jeu;
	int reste, coup;
	char * pseudo;
	int score_joueur;

	//Boucle principale
	while(continuer_prgm){
		//Choix de la taille
		size = menu(debug, pseudo);

		//Génération des grilles
		active = init_array(size);
		background = init_array(size);
		build(background);

		//Variable de l'interface
        	reste = size * size;
		coup = 0;
		continuer_jeu = CONTINUE;

		//Boucle du jeu
		while(continuer_jeu){
			//Dessine la grille + interface
			draw(active, background, debug, 0, reste, coup);

			//Action du joueur
			if(!autoplay)
				continuer_jeu = entrer(active, background);
			else{
				continuer_jeu = select(active, background, random(0,size), random(0,size));
				system("sleep 0.5s");
			}

			//Calcul le nb de coup + case restante
			reste = case_restante(active, background);
			coup++;

			
			if(reste == 0)
				continuer_jeu = GAGNER;

			continuer_prgm = continuer_jeu;

			if(continuer_jeu == GAGNER || continuer_jeu == PERDU){
				if(continuer_jeu == GAGNER)
					draw(active, background, 0, 0, reste, coup);
				else
					draw(active, background, 0, 1, reste, coup);
				
				if(continuer_jeu == GAGNER){
					score_joueur = score(active, background, size, coup, GAGNER);
					continuer_prgm = quitter("GAGNER", score_joueur);
				}
				else{
					score_joueur = score(active, background, size, coup, PERDU);
					continuer_prgm = quitter("PERDU", score_joueur);
				}
				continuer_jeu = QUITTER;
			}

			
		
		}
		//Supprime les grilles de la mémoire
		free_array(active);
		free_array(background);
	}

	system("clear");
	return EXIT_SUCCESS;
}
