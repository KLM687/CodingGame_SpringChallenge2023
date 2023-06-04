#include "ant.h"

void parse_rs_eggs(t_cell *cells, int number_of_cells, t_ressource *ressources, t_eggs *eggs) {
    int ressource_index = 0;
	int egg_index = 0;
	
    for (int i = 0; i < number_of_cells; i++) {
		if (cells[i].type == 1){
			eggs[egg_index].type = cells[i].type;
			eggs[egg_index].cell_index = cells[i].index;
			eggs[egg_index].distance_to_base = cells[i].distance_to_base;
			eggs[egg_index].distance_to_enemy_base = cells[i].distance_to_enemy_base;
			egg_index++;
		}
        if (cells[i].type == 2) {
            ressources[ressource_index].type = cells[i].type;
            ressources[ressource_index].cell_index = cells[i].index;
            ressources[ressource_index].distance_to_base = cells[i].distance_to_base;
			ressources[ressource_index].distance_to_enemy_base = cells[i].distance_to_enemy_base;
            ressource_index++;
        }
    }
	if (MAX_RESSOURCES > 0)
		qsort(ressources, MAX_RESSOURCES, sizeof(t_ressource), compare_ressources);
	if (MAX_EGGS > 0)
		qsort(eggs, MAX_EGGS, sizeof(t_eggs), compare_eggs);
}

t_target calculate_targets(t_cell* cells, int number_of_cells, int *my_base_indices, int* opp_base_indices, int i) {
    t_target* targets = malloc(sizeof(t_target) * 1);

        int base_index = my_base_indices[i];
		int enemy_index = opp_base_indices[i];
		cells[base_index].optimal_weigth = INT_MAX - 1;
		cells[base_index].base = true;

		// Calculer les distances
        calculate_distances(cells, number_of_cells, base_index);
		calculate_distances_enemy(cells, number_of_cells, enemy_index);

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
              &cells[i].type, &cells[i].initial_ressources,
              &cells[i].neigh_0, &cells[i].neigh_1, &cells[i].neigh_2,
              &cells[i].neigh_3, &cells[i].neigh_4, &cells[i].neigh_5);
		if (cells[i].type == 1) {
			EGG_NB += cells[i].initial_ressources;
			cells[i].optimal_weigth = cells[i].initial_ressources / OPTI_EGG;
			MAX_EGGS++;
		}
		else if (cells[i].type == 2) {
			CRYSTAL += cells[i].initial_ressources;
			cells[i].optimal_weigth = cells[i].initial_ressources / OPTI_RSS;
			MAX_RESSOURCES++;
		}
		else if (cells[i].type == 0) {
			cells[i].optimal_weigth = 0;
		}

		cells[i].distance_to_base = -1;
		cells[i].tmp_distance = -1;
		cells[i].is_beacon = false;
		cells[i].current_weigth = 0;
		cells[i].my_ants = 0;
		cells[i].opp_ants = 0;
		cells[i].base = false;
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
