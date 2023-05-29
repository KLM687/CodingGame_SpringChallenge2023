#include "ant.h"

void	basic_strategy(t_target *targets, int number_of_bases)
{
	for (int i = 0; i < number_of_bases; i++)
	{
		if (TURN < 3)
		{
			for (int y = 0; y < 3; y++){
				if (targets[i].eggs[y].cell_index > 0 && MAX_EGGS > 0)
					printf("LINE %d %d %d;", targets[i].base_index, targets[i].eggs[y].cell_index, 1);
			}
		}
		else
		{
			for (int x = 0; x < TURN ; x++)
			{
				if (targets[i].eggs[x].cell_index > 0 && MAX_EGGS > 0)
					printf("LINE %d %d %d;", targets[i].base_index, targets[i].eggs[x].cell_index, 1);
			}
			for (int x = 0; x < TURN / 3; x++){
				if (targets[i].ressources[x].cell_index > 0 && MAX_RESSOURCES > 0)
					printf("LINE %d %d %d;", targets[i].base_index, targets[i].ressources[x].cell_index, 1);
			}	
		}
	}
	printf("\n");
}

void print_targets(t_target *targets, int number_of_bases){
	if (STRATEGY == 1)
		basic_strategy(targets, number_of_bases);
	TURN++;
}