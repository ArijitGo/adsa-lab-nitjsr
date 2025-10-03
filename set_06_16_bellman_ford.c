#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Edge {
    int u, v, weight;
};

int* bellmanFord(int V, int E, struct Edge* edges, int src) {
    int* dist = (int*)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    for (int i = 1; i < V; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
    for (int j = 0; j < E; j++) {
        int u = edges[j].u;
        int v = edges[j].v;
        int w = edges[j].weight;
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            free(dist);
            return NULL;
        }
    }

    return dist;
}

int main() {
    int V = 5;
    int E = 8;
    struct Edge edges[] = {
        {0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2},
        {1, 4, 2}, {3, 2, 5}, {3, 1, 1}, {4, 3, -3}
    };

    int src = 0;
    int* distances = bellmanFord(V, E, edges, src);

    if (distances == NULL) {
        printf("Graph contains a negative-weight cycle.\n");
    } else {
        printf("Vertex\tDistance from Source\n");
        for (int i = 0; i < V; i++) {
            printf("%d\t%d\n", i, distances[i]);
        }
        free(distances);
    }

    return 0;
}