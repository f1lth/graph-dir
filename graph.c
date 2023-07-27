#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NODES 10
#define MAX_CONNECTIONS 5

struct Node {
    int value;
    struct Node **connections;
};

struct Node **make_graph() {
    struct Node **graph = malloc(sizeof(struct Node *) * NODES);
    for (int i = 0; i < NODES; i++) {
        graph[i] = malloc(sizeof(struct Node));
        graph[i]->value = i;
        graph[i]->connections = malloc(sizeof(struct Node *) * MAX_CONNECTIONS);
        for (int j = 0; j < MAX_CONNECTIONS; j++) {
            // pick a random node to connect to or none
            int con = rand() % (i + 2);
            if (con > i) {
                graph[i]->connections[j] = NULL;
            } else {
                graph[i]->connections[j] = graph[con];
            }
        }
    }
    return graph;
}

void print_graph(struct Node **graph) {
    for (int i = 0; i < NODES; i++) {
        printf("Node %d: ", graph[i]->value);
        for (int j = 0; j < MAX_CONNECTIONS; j++) {
            if (graph[i]->connections[j] != NULL) {
                printf("%d ", graph[i]->connections[j]->value);
            }
        }
        printf("\n");
    }
}

void cleanup_graph(struct Node **graph) {
    for (int i = 0; i < NODES; i++) {
        free(graph[i]->connections);
        free(graph[i]);
    }
    free(graph);
}


/**
 * @brief  - Make a zero matrix of size NODE x NODE
 * 
 * 
 * @return int** 
 */
int** make_zero_matrix() {
    int** matrix = malloc(sizeof(int*) * NODES);
    for (int i=0; i < NODES; i++) {
        matrix[i] = malloc(sizeof(int) * NODES);
        for (int j=0; j < NODES; j++) {
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

int** fill_matrix_from_graph(int** matrix, struct Node** graph) {
    for (int i=0; i < NODES; i++) {
        for (int j=0; j < MAX_CONNECTIONS; j++) {
            if (graph[i]->connections[j] != NULL) {
                matrix[i][graph[i]->connections[j]->value] = 1;
            }
        }
    }
    return matrix;
}

void print_matrix(int** matrix) {
    for (int i=0; i < NODES; i++) {
        for (int j=0; j < NODES; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void cleanup_matrix(int** matrix) {
    for (int i=0; i < NODES; i++) {
        free(matrix[i]);
    }
    free(matrix);
}


int main() {
    struct Node **graph = make_graph();
    print_graph(graph);

    int** matrix = make_zero_matrix();
    print_matrix(matrix);

    puts("--------------------------");
    matrix = fill_matrix_from_graph(matrix, graph);
    print_matrix(matrix);

    cleanup_matrix(matrix);
    cleanup_graph(graph);

    return 0;
}
