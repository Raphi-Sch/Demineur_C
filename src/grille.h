#ifndef grille
#define	grille

typedef struct{
	int * grid;
	int size;
}grid_t;

//Create - Destruct
grid_t * init_array(int size);
void free_array(grid_t * array);

//Index - Read - Write
int index(const grid_t * array, int l, int c);
int read_cell(const grid_t * array, int l, int c);
void write_cell(grid_t * array, int l, int c, int value);


#endif
