#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NODES 5
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

void cleanup(struct Node **graph) {
    for (int i = 0; i < NODES; i++) {
        free(graph[i]->connections);
        free(graph[i]);
    }
    free(graph);
}

int main() {
    struct Node **graph = make_graph();
    print_graph(graph);
    cleanup(graph);
    return 0;
}
