#ifndef ANT_H
# define ANT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

extern int MAX_RESSOURCES;
extern int MAX_EGGS;
extern int TURN;

// Structure pour stocker les informations d'une cellule
typedef struct s_cell {
    int index;
    int type;
    int initial_resources;
    int neigh_0;
    int neigh_1;
    int neigh_2;
    int neigh_3;
    int neigh_4;
    int neigh_5;
    int distance_to_base;
} t_cell;


// Structure pour stocker les informations d'une ressource
typedef struct s_ressource {
    int type;
    int cell_index;
    int distance_to_base;
} t_ressource;

// Structure pour stocker les informations d'un oeuf
typedef struct s_eggs {
    int type;
    int cell_index;
    int distance_to_base;
} t_eggs;

typedef struct s_target {
	int base_index;
	t_ressource *ressources;
	t_eggs *eggs;
} t_target;

void calculate_distances(t_cell *cells, int number_of_cells, int base_index);
int compare_ressources(const void *a, const void *b);
int compare_eggs(const void *a, const void *b);
void delete_resource(t_ressource *ressources, int index);
void delete_egg(t_eggs *eggs, int index);
void parse_cells(t_cell *cells, int number_of_cells);
void parse_rs_eggs(t_cell *cells, int number_of_cells, t_ressource *ressources, t_eggs *eggs);
void print_targets(t_target *targets, int number_of_bases);

#endif
