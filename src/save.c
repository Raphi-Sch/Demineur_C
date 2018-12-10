#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

#include "liste.h"
#include "save.h"


//Lecture-Ecriture Fichier
void save_file(const liste_t L){
	liste_t temp = L;

	FILE * fichier = fopen("scores", "w+");
	
	while(!estVide(temp)){
		fprintf(fichier, "%s\t%d\n", Tete_pseudo(temp),Tete_score(temp));
		temp = Reste(temp);
	}

	fclose(fichier);
}

liste_t load_file(){
	liste_t scores = ConsVide();
	char* pseudo;
	int best;
	int i;
	
	FILE* fichier = fopen("scores", "r");
	if (fichier != NULL)
	{
		for (i=1; i<6; i++)// 5 scores stockés
		{
			pseudo = (char *)malloc(sizeof(char)*10);
			fscanf(fichier,"%s\t%d\n", pseudo, &best);
			scores = inserer(scores, pseudo, best, i);
		}
		fclose(fichier);
	}
	else // fichier inexistant
		scores = premiers_scores(scores);
		
	return scores;	
}


//Action sur la liste des scores
void save(liste_t scores, int best, int pos_save){
	char* pseudo = (char*)malloc(sizeof(char)*10);

	printf("\nFelicitations, vous avez un tres bon score !\nVotre pseudo (10 caracteres max) : ");
	scanf("%s",pseudo);
	
	scores = inserer(scores, pseudo, best, pos_save);

	save_file(scores);
}


int position( liste_t scores, int best){
	int pos = 0, i = 1;
	while(pos == 0 && i < 6){
		if(Tete_score(scores) < best)
			pos = i;
		scores = Reste(scores);
		i++;	
	}
	return pos;
}

liste_t premiers_scores(liste_t scores){
	scores = inserer(scores, "Iron_Man", 25, 1);
	scores = inserer(scores, "C_America", 20, 2);
	scores = inserer(scores, "Hulk", 19, 3);
	scores = inserer(scores, "OeilFaucon", 18, 4);
	scores = inserer(scores, "B_Widow", 17, 5);
	return scores;
}
