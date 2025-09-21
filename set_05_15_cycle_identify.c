#include <stdio.h>
#include <stdlib.h>

enum GraphType { DIRECTED, UNDIRECTED };

void DFS_undirected(int u, int parent, int depth, int n, int **adj, int *deg, int *visited, int *dep, int *largestCycle, int *smallestCycle) {
    visited[u] = 1;
    dep[u] = depth;
    for (int i = 0; i < deg[u]; i++) {
        int v = adj[u][i];
        if (v == parent) continue;
        if (visited[v]) {
            int cycle_len = dep[u] - dep[v] + 1;
            if (cycle_len < 2) continue;
            if (*largestCycle == -1 || cycle_len > *largestCycle) {
                *largestCycle = cycle_len;
            }
            if (*smallestCycle == -1 || cycle_len < *smallestCycle) {
                *smallestCycle = cycle_len;
            }
        } else {
            DFS_undirected(v, u, depth + 1, n, adj, deg, visited, dep, largestCycle, smallestCycle);
        }
    }
}

void DFS_directed(int u, int depth, int n, int **adj, int *deg, int *state, int *dep, int *largestCycle, int *smallestCycle) {
    state[u] = 1;
    dep[u] = depth;
    for (int i = 0; i < deg[u]; i++) {
        int v = adj[u][i];
        if (state[v] == 0) {
            DFS_directed(v, depth + 1, n, adj, deg, state, dep, largestCycle, smallestCycle);
        } else if (state[v] == 1) {
            int cycle_len = depth - dep[v] + 1;
            if (cycle_len < 1) continue;
            if (*largestCycle == -1 || cycle_len > *largestCycle) {
                *largestCycle = cycle_len;
            }
            if (*smallestCycle == -1 || cycle_len < *smallestCycle) {
                *smallestCycle = cycle_len;
            }
        }
    }
    state[u] = 2;
}

void findCycles(int n, int **adj, int *deg, enum GraphType type, int *largestCycle, int *smallestCycle) {
    *largestCycle = -1;
    *smallestCycle = -1;

    if (type == UNDIRECTED) {
        int *visited = (int *)calloc(n, sizeof(int));
        int *dep = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            visited[i] = 0;
            dep[i] = -1;
        }
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                DFS_undirected(i, -1, 0, n, adj, deg, visited, dep, largestCycle, smallestCycle);
            }
        }
        free(visited);
        free(dep);
    } else {
        int *state = (int *)calloc(n, sizeof(int));
        int *dep = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            state[i] = 0;
            dep[i] = -1;
        }
        for (int i = 0; i < n; i++) {
            if (state[i] == 0) {
                DFS_directed(i, 0, n, adj, deg, state, dep, largestCycle, smallestCycle);
            }
        }
        free(state);
        free(dep);
    }
}

int main() {
    int n = 4;
    int *adj[n];
    int deg[] = {2, 1, 1, 1};
    int adj0[] = {1, 3};
    int adj1[] = {2};
    int adj2[] = {0};
    int adj3[] = {0};
    adj[0] = adj0;
    adj[1] = adj1;
    adj[2] = adj2;
    adj[3] = adj3;
    
    int largest, smallest;
    findCycles(n, adj, deg, DIRECTED, &largest, &smallest);
    printf("Largest cycle: %d, Smallest cycle: %d\n", largest, smallest);
    return 0;
}