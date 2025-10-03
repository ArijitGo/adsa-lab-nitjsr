#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#define SIZE 4
#define TOTAL_TILES (SIZE * SIZE)
#define MAX_HEAP_SIZE 10000000
#define MAX_VISITED_SIZE 10000000

typedef struct {
    uint64_t state;
    int g;
    int h;
    int blank_pos;
} Node;

typedef struct {
    Node* nodes;
    int size;
    int capacity;
} MinHeap;

typedef struct {
    uint64_t* states;
    int* g_values;
    int capacity;
    int size;
} VisitedSet;

int goal_state[TOTAL_TILES] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};

void print_board(int state[TOTAL_TILES]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int value = state[i * SIZE + j];
            if (value == 0) {
                printf("   ");
            } else {
                printf("%2d ", value);
            }
        }
        printf("\n");
    }
    printf("\n");
}

uint64_t compress_state(int state[TOTAL_TILES]) {
    uint64_t compressed = 0;
    for (int i = 0; i < TOTAL_TILES; i++) {
        compressed = (compressed << 4) | state[i];
    }
    return compressed;
}

void decompress_state(uint64_t compressed, int state[TOTAL_TILES]) {
    for (int i = TOTAL_TILES - 1; i >= 0; i--) {
        state[i] = compressed & 0xF;
        compressed >>= 4;
    }
}

int manhattan_distance(uint64_t state) {
    int distance = 0;
    int grid[TOTAL_TILES];
    decompress_state(state, grid);
    for (int i = 0; i < TOTAL_TILES; i++) {
        int value = grid[i];
        if (value != 0) {
            int goal_row = (value - 1) / SIZE;
            int goal_col = (value - 1) % SIZE;
            int current_row = i / SIZE;
            int current_col = i % SIZE;
            distance += abs(current_row - goal_row) + abs(current_col - goal_col);
        }
    }
    return distance;
}

MinHeap* create_heap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->nodes = (Node*)malloc(capacity * sizeof(Node));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap_nodes(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(MinHeap* heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->nodes[index].g + heap->nodes[index].h < heap->nodes[parent].g + heap->nodes[parent].h) {
            swap_nodes(&heap->nodes[index], &heap->nodes[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

void heapify_down(MinHeap* heap, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < heap->size && heap->nodes[left].g + heap->nodes[left].h < heap->nodes[smallest].g + heap->nodes[smallest].h) {
        smallest = left;
    }
    if (right < heap->size && heap->nodes[right].g + heap->nodes[right].h < heap->nodes[smallest].g + heap->nodes[smallest].h) {
        smallest = right;
    }
    if (smallest != index) {
        swap_nodes(&heap->nodes[index], &heap->nodes[smallest]);
        heapify_down(heap, smallest);
    }
}

void push(MinHeap* heap, Node node) {
    if (heap->size >= heap->capacity) {
        return;
    }
    heap->nodes[heap->size] = node;
    heapify_up(heap, heap->size);
    heap->size++;
}

Node pop(MinHeap* heap) {
    Node node = heap->nodes[0];
    heap->nodes[0] = heap->nodes[--heap->size];
    heapify_down(heap, 0);
    return node;
}

int is_empty(MinHeap* heap) {
    return heap->size == 0;
}

VisitedSet* create_visited_set(int capacity) {
    VisitedSet* set = (VisitedSet*)malloc(sizeof(VisitedSet));
    set->states = (uint64_t*)malloc(capacity * sizeof(uint64_t));
    set->g_values = (int*)malloc(capacity * sizeof(int));
    for (int i = 0; i < capacity; i++) {
        set->states[i] = 0;
        set->g_values[i] = -1;
    }
    set->capacity = capacity;
    set->size = 0;
    return set;
}

int find_index(VisitedSet* set, uint64_t state) {
    int index = state % set->capacity;
    while (set->states[index] != 0 && set->states[index] != state) {
        index = (index + 1) % set->capacity;
    }
    return index;
}

void add_to_visited_set(VisitedSet* set, uint64_t state, int g) {
    int index = find_index(set, state);
    if (set->states[index] == 0) {
        set->states[index] = state;
        set->g_values[index] = g;
        set->size++;
    } else if (g < set->g_values[index]) {
        set->g_values[index] = g;
    }
}

int get_g_value(VisitedSet* set, uint64_t state) {
    int index = find_index(set, state);
    if (set->states[index] == state) {
        return set->g_values[index];
    }
    return -1;
}

int is_solvable(int state[TOTAL_TILES]) {
    int inversions = 0;
    int blank_row = 0;
    for (int i = 0; i < TOTAL_TILES; i++) {
        if (state[i] == 0) {
            blank_row = i / SIZE;
            continue;
        }
        for (int j = i + 1; j < TOTAL_TILES; j++) {
            if (state[j] != 0 && state[i] > state[j]) {
                inversions++;
            }
        }
    }
    return (inversions + blank_row) % 2 != 0;
}

int main() {
    int initial_state[TOTAL_TILES] = {2, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0, 12, 13, 14, 15};

    printf("Initial Board:\n");
    print_board(initial_state);

    printf("Goal Board:\n");
    print_board(goal_state);

    if (!is_solvable(initial_state)) {
        printf("Unsolvable puzzle.\n");
        return 0;
    }
    MinHeap* heap = create_heap(MAX_HEAP_SIZE);
    VisitedSet* visited = create_visited_set(MAX_VISITED_SIZE);

    uint64_t goal_compressed = compress_state(goal_state);
    uint64_t initial_compressed = compress_state(initial_state);

    Node start_node;
    start_node.state = initial_compressed;
    start_node.g = 0;
    start_node.h = manhattan_distance(initial_compressed);
    start_node.blank_pos = 0;
    for (int i = 0; i < TOTAL_TILES; i++) {
        if (initial_state[i] == 0) {
            start_node.blank_pos = i;
            break;
        }
    }

    push(heap, start_node);
    add_to_visited_set(visited, initial_compressed, 0);

    int moves = -1;
    while (!is_empty(heap)) {
        Node current = pop(heap);
        if (current.state == goal_compressed) {
            moves = current.g;
            break;
        }

        int current_g = current.g;
        int blank_pos = current.blank_pos;
        int row = blank_pos / SIZE;
        int col = blank_pos % SIZE;

        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int d = 0; d < 4; d++) {
            int new_row = row + directions[d][0];
            int new_col = col + directions[d][1];
            if (new_row >= 0 && new_row < SIZE && new_col >= 0 && new_col < SIZE) {
                int new_blank_pos = new_row * SIZE + new_col;
                int state_array[TOTAL_TILES];
                decompress_state(current.state, state_array);

                state_array[blank_pos] = state_array[new_blank_pos];
                state_array[new_blank_pos] = 0;

                uint64_t new_state = compress_state(state_array);
                int new_g = current_g + 1;

                int visited_g = get_g_value(visited, new_state);
                if (visited_g == -1 || new_g < visited_g) {
                    add_to_visited_set(visited, new_state, new_g);
                    Node new_node;
                    new_node.state = new_state;
                    new_node.g = new_g;
                    new_node.h = manhattan_distance(new_state);
                    new_node.blank_pos = new_blank_pos;
                    push(heap, new_node);
                }
            }
        }
    }

    if (moves != -1) {
        printf("Solved in %d moves.\n", moves);
    } else {
        printf("No solution found.\n");
    }

    free(heap->nodes);
    free(heap);
    free(visited->states);
    free(visited->g_values);
    free(visited);

    return 0;
}