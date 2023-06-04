#include "ant.h"

bool	half_egg()
{
	if (number_of_bases == 1)
	{
		if (MYANT >= (EGG_NB / 3))
			return (true);
		else if (MYANT >= CRYSTAL)
			return (true);
	}
	else if (number_of_bases == 2)
	{
		if (MYANT >= (EGG_NB / 2))
			return (true);
		else if (MYANT >= CRYSTAL)
			return (true);
		
	}
	return (false);
}

void 	print_road(t_cell *cells)
{
	for (int i = 0; i < MAX_CELLS; i++)
	{
		if (cells[i].is_beacon == true)
			printf("BEACON %d %d;", i, cells[i].current_weigth);
	}
}

void	basic_strategy(t_cell *cells, t_target *targets, int number_of_bases)
{
	int eggs = (MAX_EGGS / 2);
	if(MAX_EGGS % 2 != 0 && eggs > 1)
		eggs++;
	//int rss = MYSCORE;
	for (int i = 0; i < number_of_bases; i++) {
		cells[targets[i].base_index].is_beacon = true;
	}
	for (int i = 0; i < number_of_bases; i++)
	{
		if (MYANT < CRYSTAL)
		{
			create_road_eggs(cells, targets, i);
			print_road(cells);
		}
	}
		//if (half_egg())
		//{
			//for (int r = 0; r < MAX_RESSOURCES; r++)
			//{
				//if (cells[targets[i].ressources[r].cell_index].initial_ressources > 0)
					//rss += cells[targets[i].ressources[r].cell_index].initial_ressources;
				//fprintf(stderr, "rss: %d\n", targets[i].ressources[r].cell_index);
				//if (rss >= GOAL)
				//{
					//calculate_closest_beacon(cells, targets[i].ressources[r].cell_index);
					//break;
				//}
				//calculate_closest_beacon(cells, targets[i].ressources[r].cell_index);

			//}
		//}
	printf("MESSAGE AAAAAAAAAAAAAAH;");
	printf("\n");
}

void delete_useless_eggs(t_target *targets, int number_of_bases, float del_ratio)
{
    int del = MAX_EGGS * del_ratio;
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

//void	big_strategy(t_cell *cells, t_target *targets, int number_of_bases)
//{
	//int eggs = (MAX_EGGS / 2);
	//if(MAX_EGGS % 2 != 0 && eggs > 1)
		//eggs++;
	//int rss = MYSCORE;
	//for (int i = 0; i < number_of_bases; i++) {
		//cells[targets[i].base_index].is_beacon = true;
		//printf("BEACON %d %d;", targets[i].base_index, 1);
	//}
	//for (int i = 0; i < number_of_bases; i++) {
  		//if (MYANT < CRYSTAL)
		//{  	
			//for (int y = 0; y < eggs; y++) {
				//fprintf(stderr, "index %d distance to base: %d\n",targets[i].eggs[y].cell_index, targets[i].eggs[y].distance_to_base);
				//if (MYANT < (targets[i].eggs[y].distance_to_base * 2) && y != 0)
					//break;
   	  		   	//if (targets[i].eggs[y].cell_index != -1 && MAX_EGGS > 0) {
					//if (cells[targets[i].eggs[y].cell_index].is_beacon == false)
					//{
						//calculate_closest_beacon(cells, targets[i].eggs[y].cell_index);
					//}
        		//}  
    		//}
		//}
		//fprintf(stderr, "TURN: %d\n", TURN);
		//if (half_egg())
		//{
			//fprintf(stderr,"MAX_RSS = %d\n", MAX_RESSOURCES);
			//for (int r = 0; r < MAX_RESSOURCES; r++)
			//{
				//if (cells[targets[i].ressources[r].cell_index].initial_ressources > 0)
					//rss += cells[targets[i].ressources[r].cell_index].initial_ressources;
				//fprintf(stderr, "rss: %d\n", targets[i].ressources[r].cell_index);
				//if (rss >= GOAL)
				//{
					//calculate_closest_beacon(cells, targets[i].ressources[r].cell_index);
					//break;
				//}
				//calculate_closest_beacon(cells, targets[i].ressources[r].cell_index);

			//}
		//}
	//}
	//fprintf(stderr, "rss %d goal %d\n", rss, GOAL);
	//printf("MESSAGE HELLO FROM 42 PARIS <3;");
	//printf("\n");
//}

void compute_targets(t_cell *cells, t_target *targets, int number_of_bases){
	if (number_of_bases == 2)
		FORCE = MYANT / 2;
	else
		FORCE = MYANT;
	//if (STRATEGY == 1)
	//{
		//delete_useless_eggs(targets, number_of_bases, 0.5);
		basic_strategy(cells, targets, number_of_bases);
	//}
	//else if (STRATEGY == 2)
	//{
		//delete_useless_eggs(targets, number_of_bases, 0.70);
		//big_strategy(cells, targets, number_of_bases);
	//}
	TURN++;
}
