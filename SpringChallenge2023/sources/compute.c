#include "ant.h"

void print_targets(t_target *targets, int number_of_bases){

			fprintf(stderr, "----------------\n");
	for (int i = 0; i < number_of_bases; i++){
		fprintf(stderr, "BASE %d index = %d\n", i, targets[i].base_index);
		for (int x = 0; x < MAX_EGGS; x++) {
			fprintf(stderr, "EGGS %d, distance %d\n", targets[i].eggs[x].cell_index, targets[i].eggs[x].distance_to_base);
		}
		for (int x = 0; x < MAX_RESSOURCES; x++){
			fprintf(stderr, "Ressource %d, distance %d\n", targets[i].ressources[x].cell_index, targets[i].ressources[x].distance_to_base);
		}
	}
		for (int i = 0; i < number_of_bases; i++){
		{
			for (int x = 0; x < TURN; x++)
			{
				if (targets[i].eggs[x].cell_index > 0 && MAX_EGGS > 0)
					printf("LINE %d %d %d;", targets[i].base_index, targets[i].eggs[x].cell_index, 1);
			}
			if (TURN > 2)
			{
				for (int x = 0; x < TURN; x++){
					if (targets[i].ressources[x].cell_index > 0 && MAX_RESSOURCES > 0)
						printf("LINE %d %d %d;", targets[i].base_index, targets[i].ressources[x].cell_index, 1);
				}	
			}
		}
	}
	TURN++;
	printf("\n");
}