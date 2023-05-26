#include "ant.h"

void print_targets(t_target *targets, int number_of_bases){

	for (int i = 0; i < number_of_bases; i++){
		fprintf(stderr, "BASE %d\n", i);
		for (int x = 0; x < TURN; x++) {
			if (x < MAX_EGGS)
				printf("LINE %d %d %d;", targets[i].base_index, targets[i].eggs->cell_index, 1);
		}
		if (TURN > 4 || MAX_EGGS == 0)
		{
			for (int x = 0; x < TURN; x++){
				if (x < MAX_RESSOURCES)
					printf("LINE %d %d %d;", targets[i].base_index, targets[i].ressources->cell_index, 1);}
		}
	}
	TURN++;
	printf("\n");
}