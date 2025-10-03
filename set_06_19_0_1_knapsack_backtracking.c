#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int weight;
    int value;
    double ratio;
} Item;

int compare(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;
    if (itemA->ratio < itemB->ratio) return 1;
    if (itemA->ratio > itemB->ratio) return -1;
    return 0;
}

double bound(int i, int n, int capacity, int current_weight, int current_value, Item items[]) {
    if (current_weight >= capacity) return 0;
    
    double bound_value = current_value;
    int total_weight = current_weight;
    int j = i;
    
    while (j < n && total_weight + items[j].weight <= capacity) {
        total_weight += items[j].weight;
        bound_value += items[j].value;
        j++;
    }
    
    if (j < n) {
        bound_value += (capacity - total_weight) * items[j].ratio;
    }
    
    return bound_value;
}

void knapsack_backtracking(int i, int n, int capacity, int current_weight, int current_value, 
                          int *best_value, Item items[], bool *include, bool *best_solution) {
    if (current_weight <= capacity && current_value > *best_value) {
        *best_value = current_value;
        for (int j = 0; j < n; j++) {
            best_solution[j] = include[j];
        }
    }
    
    if (i == n) return;
    
    if (current_weight + items[i].weight <= capacity) {
        include[i] = true;
        knapsack_backtracking(i + 1, n, capacity, current_weight + items[i].weight, 
                             current_value + items[i].value, best_value, items, include, best_solution);
        include[i] = false;
    }
    
    if (bound(i + 1, n, capacity, current_weight, current_value, items) > *best_value) {
        knapsack_backtracking(i + 1, n, capacity, current_weight, current_value, 
                             best_value, items, include, best_solution);
    }
}

int main() {
    int values[] = {60, 100, 120};
    int weights[] = {10, 20, 30};
    int capacity = 50;
    int n = sizeof(values) / sizeof(values[0]);
    
    Item items[n];
    for (int i = 0; i < n; i++) {
        items[i].value = values[i];
        items[i].weight = weights[i];
        items[i].ratio = (double)values[i] / weights[i];
    }
    
    qsort(items, n, sizeof(Item), compare);
    
    bool include[n];
    bool best_solution[n];
    for (int i = 0; i < n; i++) {
        include[i] = false;
        best_solution[i] = false;
    }
    
    int best_value = 0;
    
    knapsack_backtracking(0, n, capacity, 0, 0, &best_value, items, include, best_solution);
    
    printf("Maximum value: %d\n", best_value);
    printf("Selected items: ");
    for (int i = 0; i < n; i++) {
        if (best_solution[i]) {
            printf("Item with weight %d and value %d, ", items[i].weight, items[i].value);
        }
    }
    printf("\n");    
    return 0;
}