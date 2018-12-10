#include "stdio.h"
#include "stdlib.h"

#include "affichage.h"
#include "grille.h"

int entrer(grid_t * active, grid_t * background){
    //Retourne 0 : quitter / 1 : continuer / 2 : perdu 
	int l, c, choix;
	int size = active->size;

	printf("\nEntrer '-1' pour quitter.\n");
	printf("Entrer '-2' pour placer ou enlever un drapeau.\n");

	do{
		printf("Entrer une ligne (ou choix) : ");
        	scanf("%d", &choix);
        	clean_buffer();
	}while(choix < -2 || choix > size-1);

	//Drapeau
	if(choix == -2){
		do{
			printf("Entrer ligne : ");
            		scanf("%d", &l);
            		clean_buffer();
            		printf("Entrer colonne : ");
            		scanf("%d", &c);
            		clean_buffer();
		}while(!drapeau(active, l, c));
		return 1;
	}

	//Quitter
	if(choix == -1)
		return 0;

	//Ouvrir case
	if(choix >= 0){
		do{
			l = choix;
			printf("Entrer colonne : ");
			scanf("%d", &c);
			clean_buffer();
    		}while(c < 0 || c > size-1 || read_cell(active, l, c) == 2);
       		return select(active, background, l, c);
	}
	
    return 0;
}

void draw(grid_t * active, grid_t * background, int debug, int fin, int reste, int coup){
	int size = active->size;
	int value;	

	//interface
	system("clear");
	int hub_size = (size/2 -4);
	for(int i = 0; i < hub_size; i++)
		printf("   ");
	printf("\t Demineur\n");
	printf("Cases restantes sans mine : %d\n", reste);
	printf("Nombre de coups : %d\n\n", coup);

	//Lignes
	for(int i = -1; i < size; i++){
		//Entete des lignes
		color(invert);
		if(i == -1)
			printf("  ");
		else{
			if(i < 10)
				printf("%d ", i);
			else
				printf("%d", i);
		}
		color(reset);
		//Colonnes
		for(int j = 0; j < size; j++){
			if(fin && read_cell(background, i, j) == 10 && read_cell(active, i ,j) != 2){
						write_cell(active, i, j, 1);
			}
			//Grille
			if(i > -1){
				value = read_cell(active, i, j);
				if(debug){
					value = 1;
				}
					
				switch(value){
					case 0: // case non active
						color(blue);
						printf("#");
						color(reset);
						printf("  ");
						break;
						
					case 1: // case active
						switch(read_cell(background, i, j)){
							case 0 : // case background vide
								printf(".  ");
								break;
								
							case 10 : // case background bombe
								color(back_red);
								printf("*");
								color(reset);
								printf("  ");
								break;
								
							default : // 1 chiffre dans background
								color(green);
								printf("%d", read_cell(background, i, j));
								color(reset);
								printf("  ");
								break; 
						}
						break;
					case 2: // case active avec un drapeau
						if(fin){
							if (read_cell(background, i, j) == 10)
								color(green);
							else
								color(red);
							printf("P");
							color(reset);
							printf("  ");
						}
						else
						{
							color(white);
							printf("P");
							color(reset);
							printf("  ");
						}
						break;
				}
			}
			else{
			//Entete des colonnes
			color(invert);
			if(j < 10)
				printf("%d  ", j);
			else
				printf("%d ", j);
			}
			color(reset);
		}
		printf("\n");
	}
}

int select(grid_t * active, grid_t * background, int l, int c){
	int size = active->size;
	if(read_cell(background, l, c) == 10){  //Si c'est une bombe, on ouvre la case et return 3 (game over)
		write_cell(active, l, c, 1);
		return 3;
	}
	else{
		write_cell(active, l, c, 1);
		if(read_cell(background, l, c) == 0){
			//Gauche
			if(c-1 >= 0 && read_cell(active, l, c-1) != 1){
				select(active, background, l, c-1);
			}

			//Droite
			if(c+1 < size && read_cell(active, l, c+1) != 1){
				select(active, background, l, c+1);
			}

			//BAS
			if(l-1 >= 0 && read_cell(active, l-1, c) != 1){
				select(active, background, l-1, c);
			}

			//HAUT
			if(l+1 < size && read_cell(active, l+1, c) != 1){
				select(active, background, l+1, c);
			}
		}
		return 1;
	}
}

int drapeau(grid_t * active, int l, int c){
	//Retourne 1 si on peux placer ou retirer le drapeau sinon 0
	int size = active->size;
	if(read_cell(active, l, c) != 1 && l >= 0 && l < size && c >= 0 && c < size){
		if(read_cell(active, l, c) == 0)
    			write_cell(active, l, c, 2); //Place
		else 
			write_cell(active, l, c, 0); //Retire
		return 1;
	}
	else
		return 0;
}

int case_restante(grid_t * active, grid_t * background){
    //Verifie que les cases encore cachées ne continnent pas que des bombes
	int size = active->size;
    int restant = 0;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(read_cell(active, i, j) == 0 && read_cell(background, i, j) != 10){
                restant++;
            }
        }
    }
    return restant;
}

int score(grid_t * active, grid_t * background, int size, int coup, int etat){ 
	//Retourne le score, etat = 2 (gagner) ou 3 (perdu)
	int score = 0;
	if (coup < 0.5*size && etat == 2) // le nombre de coups joués est inférieur à 50% de la taille de la grille
		score = score + 50; // = +50pts
	for(int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			if(read_cell(active, i, j) == 2 && read_cell(background, i, j) == 10)
				score = score + 100;
			else if (read_cell(active, i, j) == 1)
				score = score + read_cell(background, i, j);
		}
	}
	return score;	
}

void clean_buffer(){
    //Vide le buffer
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
