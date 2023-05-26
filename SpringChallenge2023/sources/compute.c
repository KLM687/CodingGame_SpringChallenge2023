#include "ant.h"

void print_targets(int my_base_index, t_ressource *ressources, t_eggs *eggs){
	for (int i = 0; i < TURN; i++){
		if(i < MAX_EGGS) 
			printf("LINE %d %d %d;", my_base_index, eggs[i].cell_index, 3);
	}
    if (TURN > 3)
    {
	    for (int i = 0; i < TURN; i++){
		    if (i < MAX_RESSOURCES)
			    printf("LINE %d %d %d;", my_base_index, ressources[i].cell_index, 3);
	    }
    }
	TURN++;
	printf("\n");
}