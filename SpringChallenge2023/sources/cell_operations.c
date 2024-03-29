#include "ant.h"

int calculate_closest_beacon(t_cell *cells, int index)
{
    if (index == -1)
        return (0);
    int *queue = malloc(sizeof(int) * MAX_CELLS);
    bool *visited = calloc(MAX_CELLS, sizeof(bool));


    for (int i = 0; i < MAX_CELLS; i++)
    {
        cells[i].tmp_distance = -1;
        cells[i].parent_index = -1;
    }

    int distance = 0;
    int front = 0;
    int rear = 0;

    queue[rear++] = index;
    visited[index] = true;
    cells[index].tmp_distance = 0;

    int index2 = -1;

    while (front < rear)
    {
        int current_index = queue[front++];
        int current_distance = cells[current_index].tmp_distance;

        if (cells[current_index].is_beacon)
        {
            int backtrack_index = current_index;
            distance = current_distance;
            index2 = current_index;
            while (backtrack_index != index)
            {
                cells[backtrack_index].is_beacon = true;
                backtrack_index = cells[backtrack_index].parent_index;
            }
            cells[index].is_beacon = true;
            break;
        }

        current_distance++;

        int neigh_0 = cells[current_index].neigh_0;
        int neigh_1 = cells[current_index].neigh_1;
        int neigh_2 = cells[current_index].neigh_2;
        int neigh_3 = cells[current_index].neigh_3;
        int neigh_4 = cells[current_index].neigh_4;
        int neigh_5 = cells[current_index].neigh_5;

        if (neigh_0 >= 0 && !visited[neigh_0])
        {
            cells[neigh_0].tmp_distance = current_distance;
            cells[neigh_0].parent_index = current_index;
            queue[rear++] = neigh_0;
            visited[neigh_0] = true;
        }
        if (neigh_1 >= 0 && !visited[neigh_1])
        {
            cells[neigh_1].tmp_distance = current_distance;
            cells[neigh_1].parent_index = current_index;
            queue[rear++] = neigh_1;
            visited[neigh_1] = true;
        }
        if (neigh_2 >= 0 && !visited[neigh_2])
        {
            cells[neigh_2].tmp_distance = current_distance;
            cells[neigh_2].parent_index = current_index;
            queue[rear++] = neigh_2;
            visited[neigh_2] = true;
        }
        if (neigh_3 >= 0 && !visited[neigh_3])
        {
            cells[neigh_3].tmp_distance = current_distance;
            cells[neigh_3].parent_index = current_index;
            queue[rear++] = neigh_3;
            visited[neigh_3] = true;
        }
        if (neigh_4 >= 0 && !visited[neigh_4])
        {
            cells[neigh_4].tmp_distance = current_distance;
            cells[neigh_4].parent_index = current_index;
            queue[rear++] = neigh_4;
            visited[neigh_4] = true;
        }
        if (neigh_5 >= 0 && !visited[neigh_5])
        {
            cells[neigh_5].tmp_distance = current_distance;
            cells[neigh_5].parent_index = current_index;
            queue[rear++] = neigh_5;
            visited[neigh_5] = true;
        }
    }
    int current_index = index2;
    int strength = 1;
    distance++;
    if (index2 != -1 && index2 != index)
    {
        if (cells[index2].opp_ants > cells[index2].my_ants)
        {
            return (0);
        }
        else
        {
            if ((FORCE / distance) <= 1)
            {
                FORCE = 0;
                return 0;
            }
            else
            {
                strength = FORCE / distance;
                if (strength >= cells[index].optimal_weigth && cells[index].optimal_weigth > cells[index].current_weigth)
                    strength = cells[index].optimal_weigth;
                FORCE -= (strength * distance);
            }
        }
        fprintf(stderr, "%d -> %d weigth: %d\n", index2, index, strength);
        while (current_index != index)
        {
            current_index = cells[current_index].parent_index;
            if (strength > cells[current_index].current_weigth)
                cells[current_index].current_weigth = strength;
        }
        if (strength > cells[index2].current_weigth)
        {
            cells[index2].current_weigth = strength;
        }
    }
    free(queue);
    free(visited);
    return (1);
}

void create_road_rss(t_cell *cells, t_target *targets)
{
    int rss = MYSCORE;
    for (int i = 0; i < MAX_RESSOURCES; i++)
    {
        for (int r = 0; r < MAX_RESSOURCES; r++)
	    {
			if (cells[targets[i].ressources[r].cell_index].initial_ressources > 0)
				rss += cells[targets[i].ressources[r].cell_index].initial_ressources;
			if (rss >= GOAL)
			{
				calculate_closest_beacon(cells, targets[i].ressources[r].cell_index);
				break;
			}
			if(!calculate_closest_beacon(cells, targets[i].ressources[r].cell_index))
            {
                fprintf(stderr, "BREAK2\n");
                break;
            }
            if (FORCE == 0)
            {
                break;
            }
        }
    }
}

void create_road_eggs(t_cell *cell, t_target *targets)
{
    int stop = 0;
    if (number_of_bases == 2)
    {
        stop = MAX_EGGS / 2;
        if (stop % 2 != 0)
            stop++;
    }
    for (int x = 0; x < MAX_EGGS; x++)
    {
        if (x == (stop - 1))
            break;
        for (int i = 0; i < number_of_bases ; i++)
        {
            if (targets[i].eggs[x].cell_index == -1)
                break;
            if (targets[i].eggs[x].distance_to_enemy_base < targets[i].eggs[x].distance_to_base)
            {
                fprintf(stderr, "BREAK1\n");
                break;
            }
            if (!calculate_closest_beacon(cell, targets[i].eggs[x].cell_index))
            {
                fprintf(stderr, "BREAK2\n");
                break;
            }
            if (FORCE == 0)
            {
                fprintf(stderr, "cell: %d BREAK3\n", cell[i].index);
                break;
            }
        }
    }
    //if (FORCE > 0)
    //    create_road_rss(cell, targets);
}

void calculate_distances(t_cell *cells, int number_of_cells, int base_index)
{
    int *queue = malloc(sizeof(int) * number_of_cells);
    bool *visited = calloc(number_of_cells, sizeof(bool));

    for (int i = 0; i < number_of_cells; i++)
    {
        cells[i].distance_to_base = INT_MAX - 1;
    }

    int front = 0;
    int rear = 0;

    queue[rear++] = base_index;
    visited[base_index] = true;
    cells[base_index].distance_to_base = 0;

    while (front < rear)
    {
        int current_index = queue[front++];
        int current_distance = cells[current_index].distance_to_base + 1;

        if (current_distance > INT_MAX - 1)
        {
            break;
        }

        int neigh_0 = cells[current_index].neigh_0;
        int neigh_1 = cells[current_index].neigh_1;
        int neigh_2 = cells[current_index].neigh_2;
        int neigh_3 = cells[current_index].neigh_3;
        int neigh_4 = cells[current_index].neigh_4;
        int neigh_5 = cells[current_index].neigh_5;

        if (neigh_0 >= 0 && !visited[neigh_0])
        {
            cells[neigh_0].distance_to_base = current_distance;
            queue[rear++] = neigh_0;
            visited[neigh_0] = true;
        }
        if (neigh_1 >= 0 && !visited[neigh_1])
        {
            cells[neigh_1].distance_to_base = current_distance;
            queue[rear++] = neigh_1;
            visited[neigh_1] = true;
        }
        if (neigh_2 >= 0 && !visited[neigh_2])
        {
            cells[neigh_2].distance_to_base = current_distance;
            queue[rear++] = neigh_2;
            visited[neigh_2] = true;
        }
        if (neigh_3 >= 0 && !visited[neigh_3])
        {
            cells[neigh_3].distance_to_base = current_distance;
            queue[rear++] = neigh_3;
            visited[neigh_3] = true;
        }
        if (neigh_4 >= 0 && !visited[neigh_4])
        {
            cells[neigh_4].distance_to_base = current_distance;
            queue[rear++] = neigh_4;
            visited[neigh_4] = true;
        }
        if (neigh_5 >= 0 && !visited[neigh_5])
        {
            cells[neigh_5].distance_to_base = current_distance;
            queue[rear++] = neigh_5;
            visited[neigh_5] = true;
        }
    }
    free(queue);
    free(visited);
}

void calculate_distances_enemy(t_cell *cells, int number_of_cells, int base_index)
{
    int *queue = malloc(sizeof(int) * number_of_cells);
    bool *visited = calloc(number_of_cells, sizeof(bool));

    for (int i = 0; i < number_of_cells; i++)
    {
        cells[i].distance_to_enemy_base = INT_MAX - 1;
    }

    int front = 0;
    int rear = 0;

    queue[rear++] = base_index;
    visited[base_index] = true;
    cells[base_index].distance_to_enemy_base = 0;

    while (front < rear)
    {
        int current_index = queue[front++];
        int current_distance = cells[current_index].distance_to_enemy_base + 1;

        if (current_distance > INT_MAX - 1)
        {
            break;
        }

        int neigh_0 = cells[current_index].neigh_0;
        int neigh_1 = cells[current_index].neigh_1;
        int neigh_2 = cells[current_index].neigh_2;
        int neigh_3 = cells[current_index].neigh_3;
        int neigh_4 = cells[current_index].neigh_4;
        int neigh_5 = cells[current_index].neigh_5;

        if (neigh_0 >= 0 && !visited[neigh_0])
        {
            cells[neigh_0].distance_to_enemy_base = current_distance;
            queue[rear++] = neigh_0;
            visited[neigh_0] = true;
        }
        if (neigh_1 >= 0 && !visited[neigh_1])
        {
            cells[neigh_1].distance_to_enemy_base = current_distance;
            queue[rear++] = neigh_1;
            visited[neigh_1] = true;
        }
        if (neigh_2 >= 0 && !visited[neigh_2])
        {
            cells[neigh_2].distance_to_enemy_base = current_distance;
            queue[rear++] = neigh_2;
            visited[neigh_2] = true;
        }
        if (neigh_3 >= 0 && !visited[neigh_3])
        {
            cells[neigh_3].distance_to_enemy_base = current_distance;
            queue[rear++] = neigh_3;
            visited[neigh_3] = true;
        }
        if (neigh_4 >= 0 && !visited[neigh_4])
        {
            cells[neigh_4].distance_to_enemy_base = current_distance;
            queue[rear++] = neigh_4;
            visited[neigh_4] = true;
        }
        if (neigh_5 >= 0 && !visited[neigh_5])
        {
            cells[neigh_5].distance_to_enemy_base = current_distance;
            queue[rear++] = neigh_5;
            visited[neigh_5] = true;
        }
    }
    free(queue);
    free(visited);
}

