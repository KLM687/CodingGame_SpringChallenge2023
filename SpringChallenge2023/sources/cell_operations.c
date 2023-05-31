#include "ant.h"

int calculate_distance(t_cell* cells, int index1, int index2) {
    int* queue = malloc(sizeof(int) * MAX_CELLS);
    bool* visited = calloc(MAX_CELLS, sizeof(bool));
    if (index1 == index2)
        return 0;

    for (int i = 0; i < MAX_CELLS; i++) {
        cells[i].tmp_distance = -1;
    }

    int front = 0;
    int rear = 0;

    queue[rear++] = index1;
    visited[index1] = true;
    cells[index1].tmp_distance = 0;

    while (front < rear) {
        int current_index = queue[front++];
        int current_distance = cells[current_index].tmp_distance;

        if (current_index == index2) {
            free(queue);
            free(visited);
            return current_distance;
        }

        current_distance++; // Augmenter la distance ici

        int neigh_0 = cells[current_index].neigh_0;
        int neigh_1 = cells[current_index].neigh_1;
        int neigh_2 = cells[current_index].neigh_2;
        int neigh_3 = cells[current_index].neigh_3;
        int neigh_4 = cells[current_index].neigh_4;
        int neigh_5 = cells[current_index].neigh_5;

        if (neigh_0 >= 0 && !visited[neigh_0]) {
            cells[neigh_0].tmp_distance = current_distance;
            queue[rear++] = neigh_0;
            visited[neigh_0] = true;
        }
        if (neigh_1 >= 0 && !visited[neigh_1]) {
            cells[neigh_1].tmp_distance = current_distance;
            queue[rear++] = neigh_1;
            visited[neigh_1] = true;
        }
        if (neigh_2 >= 0 && !visited[neigh_2]) {
            cells[neigh_2].tmp_distance = current_distance;
            queue[rear++] = neigh_2;
            visited[neigh_2] = true;
        }
        if (neigh_3 >= 0 && !visited[neigh_3]) {
            cells[neigh_3].tmp_distance = current_distance;
            queue[rear++] = neigh_3;
            visited[neigh_3] = true;
        }
        if (neigh_4 >= 0 && !visited[neigh_4]) {
            cells[neigh_4].tmp_distance = current_distance;
            queue[rear++] = neigh_4;
            visited[neigh_4] = true;
        }
        if (neigh_5 >= 0 && !visited[neigh_5]) {
            cells[neigh_5].tmp_distance = current_distance;
            queue[rear++] = neigh_5;
            visited[neigh_5] = true;
        }
    }
    free(queue);
    free(visited);
    return -1;
}

void calculate_distances(t_cell* cells, int number_of_cells, int base_index) {
    int* queue = malloc(sizeof(int) * number_of_cells);
    bool* visited = calloc(number_of_cells, sizeof(bool));

    for (int i = 0; i < number_of_cells; i++) {
        cells[i].distance_to_base = INT_MAX;
    }

    int front = 0;
    int rear = 0;

    queue[rear++] = base_index;
    visited[base_index] = true;
    cells[base_index].distance_to_base = 0;

    while (front < rear) {
        int current_index = queue[front++];
        int current_distance = cells[current_index].distance_to_base + 1;

        if (current_distance > INT_MAX - 1) {
            break;
        }

        int neigh_0 = cells[current_index].neigh_0;
        int neigh_1 = cells[current_index].neigh_1;
        int neigh_2 = cells[current_index].neigh_2;
        int neigh_3 = cells[current_index].neigh_3;
        int neigh_4 = cells[current_index].neigh_4;
        int neigh_5 = cells[current_index].neigh_5;

        if (neigh_0 >= 0 && !visited[neigh_0]) {
            cells[neigh_0].distance_to_base = current_distance;
            queue[rear++] = neigh_0;
            visited[neigh_0] = true;
        }
        if (neigh_1 >= 0 && !visited[neigh_1]) {
            cells[neigh_1].distance_to_base = current_distance;
            queue[rear++] = neigh_1;
            visited[neigh_1] = true;
        }
        if (neigh_2 >= 0 && !visited[neigh_2]) {
            cells[neigh_2].distance_to_base = current_distance;
            queue[rear++] = neigh_2;
            visited[neigh_2] = true;
        }
        if (neigh_3 >= 0 && !visited[neigh_3]) {
            cells[neigh_3].distance_to_base = current_distance;
            queue[rear++] = neigh_3;
            visited[neigh_3] = true;
        }
        if (neigh_4 >= 0 && !visited[neigh_4]) {
            cells[neigh_4].distance_to_base = current_distance;
            queue[rear++] = neigh_4;
            visited[neigh_4] = true;
        }
        if (neigh_5 >= 0 && !visited[neigh_5]) {
            cells[neigh_5].distance_to_base = current_distance;
            queue[rear++] = neigh_5;
            visited[neigh_5] = true;
        }
    }
    free(queue);
    free(visited);
}