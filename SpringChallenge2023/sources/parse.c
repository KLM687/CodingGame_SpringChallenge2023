#include "ant.h"

void parse_rs_eggs(t_cell *cells, int number_of_cells, t_ressource *ressources, t_eggs *eggs) {
    int ressource_index = 0;
	int egg_index = 0;
	
    for (int i = 0; i < number_of_cells; i++) {
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
    }
	if (MAX_RESSOURCES > 0)
		qsort(ressources, MAX_RESSOURCES, sizeof(t_ressource), compare_ressources);
	if (MAX_EGGS > 0)
		qsort(eggs, MAX_EGGS, sizeof(t_eggs), compare_eggs);
}

t_target calculate_targets(t_cell* cells, int number_of_cells, int *my_base_indices,int i) {
    t_target* targets = malloc(sizeof(t_target) * 1);

        int base_index = my_base_indices[i];

        // Calculer les distances
        calculate_distances(cells, number_of_cells, base_index);

        // Allouer de la mémoire pour les ressources et les œufs
        t_ressource* ressources = malloc(sizeof(t_ressource) * (MAX_RESSOURCES + 1));
        t_eggs* eggs = malloc(sizeof(t_eggs) * (MAX_EGGS + 1));

        // Initialiser les tableaux avec des zéros
        memset(ressources, 0, sizeof(t_ressource) * (MAX_RESSOURCES + 1));
        memset(eggs, 0, sizeof(t_eggs) * (MAX_EGGS + 1));

        // Analyser les ressources et les œufs
        parse_rs_eggs(cells, number_of_cells, ressources, eggs);

        // Assigner les valeurs aux cibles
        targets[0].base_index = base_index;
        targets[0].ressources = ressources;
        targets[0].eggs = eggs;

    return *targets;
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

void delete_resource(t_ressource* ressources, int index) {
    for (int i = index; i < MAX_RESSOURCES - 1; i++) {
        ressources[i] = ressources[i + 1];
    }
    memset(&ressources[MAX_RESSOURCES - 1], -1, sizeof(t_ressource));
}

void delete_egg(t_eggs* eggs, int index) {
    for (int i = index; i < MAX_EGGS - 1; i++) {
        eggs[i] = eggs[i + 1];
    }

    memset(&eggs[MAX_EGGS - 1], -1, sizeof(t_ressource));
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
