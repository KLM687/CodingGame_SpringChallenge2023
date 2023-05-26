#include "ant.h"

void print_targets(t_target *targets, int number_of_bases){

		for (int i = 0; i < number_of_bases; i++){
		{
			for (int x = 0; x < TURN; x++)
			{
				if (targets[i].eggs[x].cell_index >= 0 && MAX_EGGS > 0)
					printf("LINE %d %d %d;", targets[i].base_index, targets[i].eggs[x].cell_index, 5);
			}
			if (TURN > 5)
			{
				for (int x = 0; x < TURN; x++){
					if (targets[i].ressources[x].cell_index >= 0 && MAX_RESSOURCES > 0)
						printf("LINE %d %d %d;", targets[i].base_index, targets[i].ressources[x].cell_index, 1);
				}	
			}
		}
	}
	TURN++;
	printf("\n");
}