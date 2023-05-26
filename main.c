#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>


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

// GLOBALS
int MAX_RESSOURCES = 0;
int MAX_EGGS = 0;

void calculate_distances(t_cell *cells, int number_of_cells, int base_index);
int compare_ressources(const void *a, const void *b);
int compare_eggs(const void *a, const void *b);
void delete_resource(t_ressource *ressources, int index);
void delete_egg(t_eggs *eggs, int index);
void parse_cells(t_cell *cells, int number_of_cells);
void parse_rs_eggs(t_cell *cells, int number_of_cells, t_ressource *ressources, t_eggs *eggs);
void print_targets(int my_base_index, t_ressource *ressources, t_eggs *eggs);

int main() {

	int number_of_cells;
	scanf("%d", &number_of_cells);

	t_cell cells[number_of_cells + 1];
	
	// parse cells
	parse_cells(cells, number_of_cells);

	// NOMBRE DE BASES
    int number_of_bases;
    scanf("%d", &number_of_bases);

    int* my_base_indices = malloc(sizeof(int) * number_of_bases);
    int* opp_base_indices = malloc(sizeof(int) * number_of_bases);

    for (int i = 0; i < number_of_bases; i++) {
        scanf("%d", &my_base_indices[i]);
    }
    for (int i = 0; i < number_of_bases; i++) {
        scanf("%d", &opp_base_indices[i]);
    }

    int my_base_index = my_base_indices[0];

    // calculate distances
    calculate_distances(cells, number_of_cells, my_base_index);
	//parse ressources and eggs
	t_ressource *ressources = malloc(sizeof(t_ressource) * MAX_RESSOURCES + 1);
	t_eggs *eggs = malloc(sizeof(t_eggs) * MAX_EGGS + 1);
	
	if (ressources == NULL || eggs == NULL)
	{
		fprintf(stderr, "malloc failed\n");
		return 1;
	}

	bzero(ressources, sizeof(t_ressource) * MAX_RESSOURCES + 1);
	bzero(eggs, sizeof(t_eggs) * MAX_EGGS + 1);
	
	parse_rs_eggs(cells, number_of_cells, ressources, eggs);

	fprintf(stderr, "----------------\n");
	for (int x = 0 ; x < MAX_RESSOURCES; x++){
		fprintf(stderr, "Ressource %d, distance %d\n;", ressources[x].cell_index, ressources[x].distance_to_base);
	}
	for (int x = 0; x < MAX_EGGS; x++) {
        fprintf(stderr, "EGGS %d, distance %d\n", eggs[x].cell_index, eggs[x].distance_to_base);
    }

    // MAIN LOOP
    while (1) {
        for (int i = 0; i < number_of_cells; i++) {
            int nb_resources;
            int my_ants;
            int opp_ants;
            scanf("%d %d %d", &nb_resources, &my_ants, &opp_ants);
			if (nb_resources == 0)
			{
				for (int x = 0; x < MAX_RESSOURCES; x++)
				{
					if (ressources[x].cell_index == i && cells[i].type == 2)
					{
						delete_resource(ressources, x);
						fprintf(stderr, "MAX_RESSOURCES = %d\n", MAX_RESSOURCES);
					}
					if (eggs[x].cell_index == i && cells[i].type == 1)
					{
						delete_egg(eggs, x);
						fprintf(stderr, "MAX_EGGS = %d\n", MAX_EGGS);
					}
				}
			}
        }
		print_targets(my_base_index, ressources, eggs);
		break;
    }
    free(my_base_indices);
    free(opp_base_indices);
    return 0;
}

//------------------ FUNCTIONS ------------------//

void parse_rs_eggs(t_cell *cells, int number_of_cells, t_ressource *ressources, t_eggs *eggs) {
    int ressource_index = 0;
	int egg_index = 0;
	
    for (int i = 0; i < number_of_cells; i++) {
		fprintf(stderr,	"Cell %d, type %d\n", cells[i].index, cells[i].type);
		if (cells[i].type == 1){
			eggs[egg_index].type = cells[i].type;
			eggs[egg_index].cell_index = cells[i].index;
			eggs[egg_index].distance_to_base = cells[i].distance_to_base;
			egg_index++;
		}
        if (cells[i].type == 2) {
            ressources[ressource_index].type = cells[i].type;
            ressources[ressource_index].cell_index = cells[i].index;
            ressources[ressource_index].distance_to_base = cells[i].distance_to_base;
            ressource_index++;
        }
		fprintf(stderr, "\n");
    }
	if (MAX_RESSOURCES > 0)
		qsort(ressources, MAX_RESSOURCES, sizeof(t_ressource), compare_ressources);
	if (MAX_EGGS > 0)
		qsort(eggs, MAX_EGGS, sizeof(t_eggs), compare_eggs);
}

void print_targets(int my_base_index, t_ressource *ressources, t_eggs *eggs){
	if (MAX_RESSOURCES >= 0)
		printf("LINE %d %d %d;", my_base_index, ressources[0].cell_index, 1);
	if (MAX_EGGS >= 0)
		printf("LINE %d %d %d", my_base_index, eggs[0].cell_index, 1);
	if (MAX_EGGS == -1)
		printf("LINE %d %d %d;", my_base_index, ressources[0].cell_index, 1);
	printf("\n");
}

void parse_cells(t_cell *cells, int number_of_cells){
	for (int i = 0; i < number_of_cells; i++)
	{
		cells[i].index = i;
        scanf("%d %d %d %d %d %d %d %d",
              &cells[i].type, &cells[i].initial_resources,
              &cells[i].neigh_0, &cells[i].neigh_1, &cells[i].neigh_2,
              &cells[i].neigh_3, &cells[i].neigh_4, &cells[i].neigh_5);
		if (cells[i].type == 1) {
			MAX_EGGS++;
		}
		if (cells[i].type == 2) {
			MAX_RESSOURCES++;
		}
	}
};

// Fonction pour supprimer une ressource du tableau ressources
void delete_resource(t_ressource* ressources, int index) {
    if (index >= 0 && index < MAX_RESSOURCES) {
        for (int i = index; i < MAX_RESSOURCES - 1; i++) {
            ressources[i] = ressources[i + 1];
        }
        MAX_RESSOURCES--;
    }
}

void delete_egg(t_eggs* eggs, int index) {
    if (index >= 0 && index < MAX_EGGS) {
        for (int i = index; i < MAX_EGGS - 1; i++) {
            eggs[i] = eggs[i + 1];
        }
        MAX_EGGS--;
    }
}

// Fonction pour comparer deux ressources utiliser par qsort
int compare_ressources(const void* a, const void* b) {
    const t_ressource* ressource_a = (const t_ressource*)a;
    const t_ressource* ressource_b = (const t_ressource*)b;

	if (ressource_a->distance_to_base < ressource_b->distance_to_base)
		return -1;
	else if (ressource_a->distance_to_base > ressource_b->distance_to_base)
		return 1;
	else
		return 0;
}


int compare_eggs(const void* a, const void* b) {
	t_eggs* egg_a = (t_eggs*)a;
	t_eggs* egg_b = (t_eggs*)b;

	if (egg_a->distance_to_base < egg_b->distance_to_base) 
		return -1;
	else if (egg_a->distance_to_base > egg_b->distance_to_base) 
		return 1;
	else 
		return 0;
}

void calculate_distances(t_cell* cells, int number_of_cells, int base_index) {
    int* queue = malloc(sizeof(int) * number_of_cells);
    bool* visited = calloc(number_of_cells, sizeof(bool));

    for (int i = 0; i < number_of_cells; i++) {
        cells[i].distance_to_base = INT_MAX;
    }

    int front = 0;
    int rear = 0;

    queue[rear++] = base_index;
    visited[base_index] = true;
    cells[base_index].distance_to_base = 0;

    while (front < rear) {
        int current_index = queue[front++];
        int current_distance = cells[current_index].distance_to_base + 1;

        if (current_distance > INT_MAX - 1) {
            break;
        }

        int neigh_0 = cells[current_index].neigh_0;
        int neigh_1 = cells[current_index].neigh_1;
        int neigh_2 = cells[current_index].neigh_2;
        int neigh_3 = cells[current_index].neigh_3;
        int neigh_4 = cells[current_index].neigh_4;
        int neigh_5 = cells[current_index].neigh_5;

        if (neigh_0 >= 0 && !visited[neigh_0]) {
            cells[neigh_0].distance_to_base = current_distance;
            queue[rear++] = neigh_0;
            visited[neigh_0] = true;
        }
        if (neigh_1 >= 0 && !visited[neigh_1]) {
            cells[neigh_1].distance_to_base = current_distance;
            queue[rear++] = neigh_1;
            visited[neigh_1] = true;
        }
        if (neigh_2 >= 0 && !visited[neigh_2]) {
            cells[neigh_2].distance_to_base = current_distance;
            queue[rear++] = neigh_2;
            visited[neigh_2] = true;
        }
        if (neigh_3 >= 0 && !visited[neigh_3]) {
            cells[neigh_3].distance_to_base = current_distance;
            queue[rear++] = neigh_3;
            visited[neigh_3] = true;
        }
        if (neigh_4 >= 0 && !visited[neigh_4]) {
            cells[neigh_4].distance_to_base = current_distance;
            queue[rear++] = neigh_4;
            visited[neigh_4] = true;
        }
        if (neigh_5 >= 0 && !visited[neigh_5]) {
            cells[neigh_5].distance_to_base = current_distance;
            queue[rear++] = neigh_5;
            visited[neigh_5] = true;
        }
    }
    free(queue);
    free(visited);
}