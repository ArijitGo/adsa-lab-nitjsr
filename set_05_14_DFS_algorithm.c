#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int numVertices;
    struct Node** adjLists;
    int* color;
    int* discoveryTime;
    int* finishTime;
    int* parent;
};

struct Node* createNode(int v) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int n) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = n;
    graph->adjLists = malloc(n * sizeof(struct Node*));
    graph->color = malloc(n * sizeof(int));
    graph->discoveryTime = malloc(n * sizeof(int));
    graph->finishTime = malloc(n * sizeof(int));
    graph->parent = malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        graph->adjLists[i] = NULL;
        graph->color[i] = WHITE;
        graph->discoveryTime[i] = 0;
        graph->finishTime[i] = 0;
        graph->parent[i] = -1;
    }
    
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

void DFSVisit(struct Graph* graph, int u, int* time) {
    (*time)++;
    graph->discoveryTime[u] = *time;
    graph->color[u] = GRAY;
    
    struct Node* temp = graph->adjLists[u];
    while (temp != NULL) {
        int v = temp->vertex;
        
        if (graph->color[v] == WHITE) {
            graph->parent[v] = u;
            printf("Edge (%d, %d) is a Tree edge\n", u, v);
            DFSVisit(graph, v, time);
        } else if (graph->color[v] == GRAY) {
            printf("Edge (%d, %d) is a Back edge\n", u, v);
        } else {
            if (graph->discoveryTime[u] < graph->discoveryTime[v]) {
                printf("Edge (%d, %d) is a Forward edge\n", u, v);
            } else {
                printf("Edge (%d, %d) is a Cross edge\n", u, v);
            }
        }
        
        temp = temp->next;
    }
    
    graph->color[u] = BLACK;
    (*time)++;
    graph->finishTime[u] = *time;
}

void DFS(struct Graph* graph) {
    int time = 0;
    
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->color[i] == WHITE) {
            DFSVisit(graph, i, &time);
        }
    }
}

void printTimes(struct Graph* graph) {
    printf("\nVertex\tDiscovery\tFinish\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%d\t%d\t\t%d\n", i, graph->discoveryTime[i], graph->finishTime[i]);
    }
}

int main() {
    struct Graph* graph = createGraph(6);
    
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 3);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 1);
    addEdge(graph, 3, 1);
    addEdge(graph, 4, 2);
    addEdge(graph, 4, 5);
    addEdge(graph, 5, 5);
    addEdge(graph, 5, 4);
    
    printf("DFS Traversal with Edge Classification:\n");
    DFS(graph);
    
    printTimes(graph);

    for (int i = 0; i < graph->numVertices; i++) {
        struct Node* temp = graph->adjLists[i];
        while (temp != NULL) {
            struct Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(graph->adjLists);
    free(graph->color);
    free(graph->discoveryTime);
    free(graph->finishTime);
    free(graph->parent);
    free(graph);
    
    return 0;
}