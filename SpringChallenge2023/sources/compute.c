#include "ant.h"

bool	not_hit(int cell_index, int *hit, int eggs)
{
	for (int i = 0; i < eggs; i++)
	{
		if (hit[i] == cell_index)
			return (false);
	}
	return (true);
}

void	basic_strategy(t_cell *cells, t_target *targets, int number_of_bases)
{
	int eggs = (MAX_EGGS / 2);
	if(MAX_EGGS % 2 != 0 && eggs > 1)
		eggs++;
	int hit[eggs];
	int r_hit[MAX_RESSOURCES];
	int e = 0;
	int r = 0;
	memset(hit, -1, sizeof(hit));
	for (int i = 0; i < number_of_bases; i++)
	{
		for (int y = 0; y < eggs; y++)
		{
			if (targets[i].eggs[y].cell_index > 0 && MAX_EGGS > 0)
			{
				if (not_hit(targets[i].eggs[y].cell_index, hit, eggs))
					printf("LINE %d %d %d;", targets[i].base_index, targets[i].eggs[y].cell_index, 1);
				for (int x = y; x < eggs; x++)
				{
					if ( x != y )
					{
						int distance = calculate_distance(cells, targets[i].eggs[y].cell_index, targets[i].eggs[x].cell_index);
						fprintf(stderr, "egg: %d egg: %d distance %d distbase %d\n",targets[i].eggs[y].cell_index, targets[i].eggs[x].cell_index, distance, targets[i].eggs[x].distance_to_base);
						if (distance < targets[i].eggs[x].distance_to_base)
						{
							printf("LINE %d %d %d;", targets[i].eggs[y].cell_index, targets[i].eggs[x].cell_index, 1);
							hit[e] = targets[i].eggs[x].cell_index;
							e++;
						}
					}
				}
			}
		}
		//if (TURN > 3)
		//{
			//for (int x = 0; x < TURN; x++)
			//{
				//if (targets[i].ressources[x].cell_index > 0 && MAX_RESSOURCES > 0)
				//{
					//if (not_hit(targets[i].ressources[x].cell_index, r_hit, MAX_RESSOURCES))
						//printf("LINE %d %d %d;", targets[i].base_index, targets[i].ressources[x].cell_index, 1);
					//for (int y = x; y < TURN; y++)
					//{
						//if ( y != x )
						//{
							//int distance = calculate_distance(cells, targets[i].ressources[x].cell_index, targets[i].ressources[y].cell_index);
							//if (distance < targets[i].ressources[y].distance_to_base)
							//{
								//printf("LINE %d %d %d;", targets[i].ressources[x].cell_index, targets[i].ressources[y].cell_index, 1);
								//r_hit[r] = targets[i].ressources[y].cell_index;
								//r++;
							//}
						//}
					//}
				//}
			//}
		//}
	}
	printf("MESSAGE %d;", MAX_CELLS);
	printf("\n");
}

void delete_useless_eggs(t_target *targets, int number_of_bases)
{
	int del = MAX_EGGS / 2;
	if (MAX_EGGS % 2 != 0)
		del++;
	for (int i = 0; i < number_of_bases; i++)
	{
		for (int y = del; y < MAX_EGGS; y++)
		{
			if (targets[i].eggs[y].cell_index > 0)
			{
				delete_egg(targets[i].eggs, y);
			}
		}
	}
}

void print_targets(t_cell *cells, t_target *targets, int number_of_bases){
	if (STRATEGY == 1)
	{
		delete_useless_eggs(targets, number_of_bases);
		basic_strategy(cells, targets, number_of_bases);
	}
	//if (STRATEGY == 1)
	//{
		//big_strategy(targets, number_of_bases);
	//}
	TURN++;
}
