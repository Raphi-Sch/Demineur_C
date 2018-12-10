#include "stdio.h"
#include "stdlib.h"

#include "grille.h"

//Create - Destruct
grid_t * init_array(int size){
	int square_size = size * size; 

	//Dynamic Memory
	grid_t * array = (grid_t*) malloc(sizeof(grid_t));
	array->size = size;
	array->grid = (int*) malloc(square_size * sizeof(int));
	
	//Set all cells at 0
	for(int i = 0; i < square_size; i++){
		array->grid[i] = 0;
	}
	return array;
}

void free_array(grid_t * array){
	free(array->grid);
	free(array);
}

//Index - Read - Write
int index(const grid_t * array, int l, int c){
	return l*array->size + c;
}

int read_cell(const grid_t * array, int l, int c){
	return array->grid[index(array, l, c)];
}

void write_cell(grid_t * array, int l, int c, int value){
	array->grid[index(array, l, c)] = value;
}




