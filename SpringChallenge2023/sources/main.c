#include "ant.h"

int MAX_RESSOURCES = 0;
int MAX_EGGS = 0;
int TURN = 0;
int GOAL = 0;
int CRYSTAL = 0;
int STRATEGY = 1;
int START_CRYSTALL = 0;
int MAX_CELLS = 0;
int MYSCORE = 0;
int OPPSCORE = 0;
int MYANT = 0;
int FORCE = 0;
int EGG_NB = 0;
int number_of_bases = 0;

int OPTI_RSS = 5;
int OPTI_EGG = 10;

int main() {

	int number_of_cells;
	scanf("%d", &number_of_cells);

	MAX_CELLS = number_of_cells;
	t_cell cells[number_of_cells + 1];
	
	// parse cells
	parse_cells(cells, number_of_cells);

	// NOMBRE DE BASES
    scanf("%d", &number_of_bases);

    int* my_base_indices = malloc(sizeof(int) * number_of_bases);
    int* opp_base_indices = malloc(sizeof(int) * number_of_bases);

    for (int i = 0; i < number_of_bases; i++) {
        scanf("%d", &my_base_indices[i]);
    }
    for (int i = 0; i < number_of_bases; i++) {
        scanf("%d", &opp_base_indices[i]);
    }

	t_target *targets = malloc(sizeof(t_target) * number_of_bases + 1);
	for (int i = 0; i < number_of_bases; i++) {
		targets[i] = calculate_targets(cells, number_of_cells, my_base_indices, opp_base_indices, i) ;
	}

	GOAL = (CRYSTAL / 2);
	compute_strategy();
    // MAIN LOOP
	while (1)
	{
		MYANT = 0;
		scanf("%d", &MYSCORE);
		scanf("%d", &OPPSCORE);
		for (int i = 0; i < number_of_cells; i++)
		{
            scanf("%d %d %d", &cells[i].initial_ressources, &cells[i].my_ants, &cells[i].opp_ants);
			cells[i].is_beacon = false;
			cells[i].current_weigth = 0;
			MYANT += cells[i].my_ants;
			if (cells[i].initial_ressources == 0)
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
		compute_targets(cells, targets, number_of_bases);
	}
	free(my_base_indices);
    free(opp_base_indices);
    return 0;
}
