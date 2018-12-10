#ifndef affichage
#define affichage
#include "grille.h"

//System Color
#define color(param) printf("\033[%sm",param)
#define reset "0"
#define black "30"
#define red "31"
#define green "32"
#define blue "34"
#define white "37"
#define invert "7"
#define back_red "41"



int entrer(grid_t * active, grid_t * background);
void draw(grid_t * active, grid_t * background, int debug, int fin, int reste, int coup);
int select(grid_t * active, grid_t * background, int l, int c);
int drapeau(grid_t * active, int l, int c);
int case_restante(grid_t * active, grid_t * background);
int score(grid_t * active, grid_t * background, int size, int coup, int etat);
void clean_buffer();

#endif
