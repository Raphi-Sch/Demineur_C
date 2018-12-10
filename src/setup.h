#ifndef setup
#define setup
#include "grille.h"
#include "liste.h"
#include "save.h"

int menu(int debug, char * pseudo);
int quitter(char * etat, int score);
void build(grid_t * array);
int random(int min, int max);


#endif
