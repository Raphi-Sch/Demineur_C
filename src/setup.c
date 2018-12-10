#include "stdio.h"
#include "stdlib.h"

#include "setup.h"
#include "time.h"
#include "grille.h"


int menu(int debug, char * pseudo){
	int size;
	system("clear");
	printf("Bienvenue dans Demineur !\n");

	if(debug)
		printf("\n MODE DEBUG \n");

	do{
		printf("Entrer la taille de la grille (5-25) : ");
		scanf("%d", &size);

		//Vide le buffer
		int c;
		do {
		    c = getchar();
		} while (c != '\n' && c != EOF);

	}while(size < 5 || size > 25);

	return size;
}

int quitter(char * etat, int score){
	int continuer;
        int pos_save;
        liste_t liste_scores;
        
        printf("%s!", etat);
        printf("\nVotre score est %d", score);
        liste_scores = load_file();
        printf("\n\nLes meilleurs scores sont :\n");
        afficher(liste_scores);
        pos_save = position(liste_scores, score);
        if (pos_save != 0)
        	save(liste_scores, score, pos_save);
        
        printf("\nRecommencer ? 0 pour quitter, 1 pour continuer\t");

	do{
		scanf("%d", &continuer);
	}while(continuer < 0 && continuer > 1);

	return continuer;
}

void build(grid_t * array){
	int size = array->size;
	srand(time(NULL));
	//Bombes
	int nb_bombe = (size*size)*0.1; //10% du nombre de case
	int x, y;
	for(int i = 0; i < nb_bombe; i++){
		do{
			x = random(0,size);
			y = random(0,size);
		}while(read_cell(array,x,y) == 10);
		write_cell(array, x, y, 10);
	}
	// On lance maintenant la reconnaissance des bombes
	for(int l = 0; l < size; l++){
	for (int c = 0; c < size; c++){
		//Si la case est une bombe
		if (read_cell(array, l, c) == 10){
			//Ligne -1 / 0 / 1
			for(int i = -1; i <= 1; i++){
			//Colonne -1 / 0 / 1
			for(int j = -1; j <= 1; j++){
				if(l+i >= 0  && l+i < size && c+j >= 0 && c+j < size){
					if(read_cell(array, l+i, c+j) != 10){
						write_cell(array, l+i, c+j, read_cell(array, l+i, c+j) + 1);
					}
				}
			}
			}
		}
	}
	}

}

int random(int min, int max){
	return rand()%max +min;
}


