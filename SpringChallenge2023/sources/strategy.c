#include "ant.h"

void compute_strategy(void){
	if (MAX_CELLS < 50)
		STRATEGY = 1;
	if (MAX_CELLS > 50)
		STRATEGY = 2;
}
