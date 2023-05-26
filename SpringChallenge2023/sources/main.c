#include "ant.h"

int MAX_RESSOURCES = 0;
int MAX_EGGS = 0;
int TURN = 1;

int main() {

	int number_of_cells;
	scanf("%d", &number_of_cells);

	t_cell cells[number_of_cells + 1];
	
	// parse cells
	parse_cells(cells, number_of_cells);

	// NOMBRE DE BASES
    int number_of_bases;
    scanf("%d", &number_of_bases);
	fprintf(stderr, "number of bases: %d\n", number_of_bases);

    int* my_base_indices = malloc(sizeof(int) * number_of_bases);
    int* opp_base_indices = malloc(sizeof(int) * number_of_bases);

    for (int i = 0; i < number_of_bases; i++) {
        scanf("%d", &my_base_indices[i]);
    }
    for (int i = 0; i < number_of_bases; i++) {
        scanf("%d", &opp_base_indices[i]);
    }

	for (int i = 0; i < number_of_bases; i++) {
		fprintf(stderr, "my base index: %d\n", my_base_indices[i]);
	}

	t_target *targets = malloc(sizeof(t_target) * number_of_bases);

	for (int i = 0; i < number_of_bases; i++){
		// calculate distances
    	calculate_distances(cells, number_of_cells, my_base_indices[i]);
		//parse ressources and eggs
		t_ressource *ressources = malloc(sizeof(t_ressource) * MAX_RESSOURCES + 1);
		t_eggs *eggs = malloc(sizeof(t_eggs) * MAX_EGGS + 1);
		bzero(ressources, sizeof(t_ressource) * MAX_RESSOURCES + 1);
		bzero(eggs, sizeof(t_eggs) * MAX_EGGS + 1);
		parse_rs_eggs(cells, number_of_cells, ressources, eggs);
		targets[i].base_index = my_base_indices[i];
		targets[i].ressources = ressources;
		targets[i].eggs = eggs;
		free(ressources);
		free(eggs);
	}

	//fprintf(stderr, "----------------\n");
	//for (int i = 0; i < number_of_bases; i++){
		//fprintf(stderr, "BASE %d\n", i);
		//for (int x = 0; x < MAX_EGGS; x++) {
			//if (x < MAX_EGGS)
				//fprintf(stderr, "EGGS %d, distance %d\n", targets[i].eggs[x].cell_index, targets[i].eggs[x].distance_to_base);
		//}
		//for (int x = 0; x < MAX_RESSOURCES; x++){
			//fprintf(stderr, "Ressource %d, distance %d\n", targets[i].ressources[x].cell_index, targets[i].ressources[x].distance_to_base);
		//}
	//}


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
					for (int y = 0; y < number_of_bases; y++)
					{
						if (targets[y].ressources[x].cell_index == i)
						{
							delete_resource(targets[y].ressources, x);
							fprintf(stderr, "MAX_RESSOURCES = %d\n", MAX_RESSOURCES);
						}
						if (targets[y].eggs[x].cell_index == i)
						{
							delete_egg(targets[y].eggs, x);
							fprintf(stderr, "MAX_EGGS = %d\n", MAX_EGGS);
						}
					}
				}
			}
        }
		print_targets(targets, number_of_bases);
    }
    free(my_base_indices);
    free(opp_base_indices);
    return 0;
}
