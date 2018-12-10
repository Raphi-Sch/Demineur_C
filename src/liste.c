#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

#include "liste.h"


liste_t ConsVide(){	
	return NULL;
}

int estVide(liste_t L){
	return (L == ConsVide());
}

liste_t Cons(liste_t L, char * pseudo, int score){
	elem_list * P = (elem_list *)malloc(1*sizeof(elem_list));
	P->pseudo = pseudo;
	P->score = score;
	P->suc = L;
	return P;
}


char * Tete_pseudo(liste_t L){	
	return L->pseudo;
}

int Tete_score(liste_t L){
	return L->score;
}

liste_t Reste(liste_t L){
	return L->suc;
}

int longeur(const liste_t L){
	if(estVide(L))
		return 0;
		
	return (1 + longeur(Reste(L)));
}


void afficher(liste_t L){
	while(!estVide(L)){
		printf("%s", Tete_pseudo(L));
		printf(" : ");
		printf("%d", Tete_score(L));
		printf("\n");
		L = Reste(L);
	}
}

liste_t inserer(liste_t L, char * pseudo, int score, int pos){
	if(estVide(L) || pos == 1)
		return Cons(L, pseudo, score);
	else{
		liste_t L1 = L;
		liste_t L2 = ConsVide();

		while(pos > 1 && !estVide(L1)){
			L2 = L1;
			L1 = Reste(L1);
			pos--;	
		}

		L1 = Cons(L1, pseudo, score);
		L2->suc = L1;
		
	}
	return L;
}

liste_t free_liste(liste_t L){
	liste_t L1;
	while(!estVide(L)){
		L1 = Reste(L);
		free(L);
		L = L1;
	}
	return L;
}


