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
	int rss = MYSCORE;
	for (int i = 0; i < number_of_bases; i++) {
		printf("BEACON %d %d;", targets[i].base_index, 1);
		cells[targets[i].base_index].is_beacon = true;
    	for (int y = 0; y < eggs; y++) {
        	if (targets[i].eggs[y].cell_index > 0 && MAX_EGGS > 0) {
				if (cells[targets[i].eggs[y].cell_index].is_beacon == false)
				{
					calculate_closest_beacon(cells, targets[i].eggs[y].cell_index);
				}
        	}  
    	}
		fprintf(stderr, "TURN: %d\n", TURN);
		if (TURN > 3)
		{
			fprintf(stderr,"MAX_RSS = %d\n", MAX_RESSOURCES);
			for (int r = 0; r < MAX_RESSOURCES; r++)
			{
				if (cells[targets[i].ressources[r].cell_index].initial_ressources > 0)
					rss += cells[targets[i].ressources[r].cell_index].initial_ressources;
				fprintf(stderr, "rss: %d\n", targets[i].ressources[r].cell_index);
				if (rss >= GOAL)
				{
					fprintf(stderr, "BREAK\n");
					int ok = 0;
					ok = calculate_closest_beacon(cells, targets[i].ressources[r].cell_index);
					fprintf(stderr, "ok: %d\n", ok);
					break;
				}
				int ok = 0;
				ok = calculate_closest_beacon(cells, targets[i].ressources[r].cell_index);
				fprintf(stderr, "ok: %d\n", ok);

			}
		}
	}
	fprintf(stderr, "rss %d goal %d\n", rss, GOAL);
	printf("MESSAGE SMALL STRATEGY;");
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

void	big_strategy(t_cell *cells, t_target *targets, int number_of_bases)
{
	int eggs = (MAX_EGGS / 2);
	if(MAX_EGGS % 2 != 0 && eggs > 1)
		eggs++;
	int rss = MYSCORE;
	for (int i = 0; i < number_of_bases; i++) {
		printf("BEACON %d %d;", targets[i].base_index, 1);
		cells[targets[i].base_index].is_beacon = true;
    	for (int y = 0; y < eggs; y++) {
        	if (targets[i].eggs[y].cell_index > 0 && MAX_EGGS > 0) {
				if (cells[targets[i].eggs[y].cell_index].is_beacon == false)
				{
					calculate_closest_beacon(cells, targets[i].eggs[y].cell_index);
				}
        	}  
    	}
		fprintf(stderr, "TURN: %d\n", TURN);
		if (TURN > 5)
		{
			fprintf(stderr,"MAX_RSS = %d\n", MAX_RESSOURCES);
			for (int r = 0; r < MAX_RESSOURCES; r++)
			{
				if (cells[targets[i].ressources[r].cell_index].initial_ressources > 0)
					rss += cells[targets[i].ressources[r].cell_index].initial_ressources;
				fprintf(stderr, "rss: %d\n", targets[i].ressources[r].cell_index);
				if (rss >= GOAL)
				{
					fprintf(stderr, "BREAK\n");
					int ok = 0;
					ok = calculate_closest_beacon(cells, targets[i].ressources[r].cell_index);
					fprintf(stderr, "ok: %d\n", ok);
					break;
				}
				int ok = 0;
				ok = calculate_closest_beacon(cells, targets[i].ressources[r].cell_index);
				fprintf(stderr, "ok: %d\n", ok);

			}
		}
	}
	fprintf(stderr, "rss %d goal %d\n", rss, GOAL);
	printf("MESSAGE BIG STRATEGY;");
	printf("\n");
}

void compute_targets(t_cell *cells, t_target *targets, int number_of_bases){
	if (STRATEGY == 1)
	{
		delete_useless_eggs(targets, number_of_bases);
		basic_strategy(cells, targets, number_of_bases);
	}
	else if (STRATEGY == 2)
	{
		big_strategy(cells, targets, number_of_bases);
	}
	TURN++;
}
