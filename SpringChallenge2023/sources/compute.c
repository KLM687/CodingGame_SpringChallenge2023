#include "ant.h"

void print_targets(int my_base_index, t_ressource *ressources, t_eggs *eggs){
	if (MAX_RESSOURCES > 0)
		printf("LINE %d %d %d;", my_base_index, ressources[0].cell_index, 3);
	if (MAX_EGGS > 0)
		printf("LINE %d %d %d", my_base_index, eggs[0].cell_index, 1);
	if (MAX_EGGS == 0)
		printf("LINE %d %d %d;", my_base_index, ressources[0].cell_index, 3);
	printf("\n");
}
