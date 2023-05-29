#include "ant.h"

int MAX_RESSOURCES = 0;
int MAX_EGGS = 0;
int TURN = 0;
int GOAL = 0;
int CRYSTAL = 0;
int STRATEGY = 1;
int START_CRYSTALL = 0;


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

	t_target *targets = malloc(sizeof(t_target) * number_of_bases + 1);
	for (int i = 0; i < number_of_bases; i++) {
		targets[i] = calculate_targets(cells, number_of_cells, my_base_indices, i);
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
				for (int b = 0; b < number_of_bases; b++)
				{
					for (int x = 0; x < MAX_EGGS; x++)
					{
						if (targets[b].eggs[x].cell_index == i)
						{
							delete_egg(targets[b].eggs, x);
						}
					}
					for (int x = 0; x < MAX_RESSOURCES; x++)
					{
						if (targets[b].ressources[x].cell_index == i)
						{
							delete_resource(targets[b].ressources, x);
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
