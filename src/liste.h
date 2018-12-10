#ifndef _LISTE_
#define _LISTE_


typedef struct eltlst{
	char * pseudo;
	int score;
	struct eltlst * suc; 
}elem_list, * liste_t; 


liste_t ConsVide();
int estVide(liste_t L);
liste_t Cons(liste_t L, char * pseudo, int score);
liste_t free_liste(liste_t L);

char * Tete_pseudo(liste_t L);
int Tete_score(liste_t L);
liste_t Reste(liste_t L);

void afficher(liste_t L);
liste_t inserer(liste_t L, char * pseudo, int score, int pos);
int longeur(const liste_t L);


#endif
