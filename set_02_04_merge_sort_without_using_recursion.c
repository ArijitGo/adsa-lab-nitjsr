#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) 
        L[i] = arr[l + i];

    for (int i = 0; i < n2; i++) 
        R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) 
        arr[k++] = L[i++];
    while (j < n2) 
        arr[k++] = R[j++];

    free(L);
    free(R);
}

typedef struct {
    int l, r, stage;
} Frame;

void mergeSortIterative(int arr[], int n) {
    Frame *stack = (Frame*)malloc(n * 4 * sizeof(Frame)); 
    int top = -1;

    stack[++top] = (Frame){0, n - 1, 0};

    while (top >= 0) {
        Frame cur = stack[top--];
        int l = cur.l, r = cur.r;
        if (l >= r) continue;

        int m = l + (r - l) / 2;

        if (cur.stage == 0) {
            stack[++top] = (Frame){l, r, 1};     
            stack[++top] = (Frame){m + 1, r, 0}; 
            stack[++top] = (Frame){l, m, 0};    
        } else {
            merge(arr, l, m, r);
        }
    }

    free(stack);
}

int main() {
    int arr[] = {8, 2, 3, 1, 7, 5, 0};
    int n = sizeof(arr) / sizeof(arr[0]);

    mergeSortIterative(arr, n);

    printf("Sorted array:   ");
    for (int i = 0; i < n; i++) 
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}