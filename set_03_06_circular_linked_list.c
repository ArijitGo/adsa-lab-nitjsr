#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

typedef struct {
    int items[SIZE];
    int front, rear;
} ArrayQueue;

void initArrayQueue(ArrayQueue *q) {
    q->front = q->rear = -1;
}

int isEmptyArray(ArrayQueue *q) {
    return (q->front == -1);
}

int isFullArray(ArrayQueue *q) {
    return (q->front == (q->rear + 1) % SIZE);
}

void enqueueArray(ArrayQueue *q, int val) {
    if (isFullArray(q)) {
        printf("Array Queue FULL\n");
        return;
    }
    if (isEmptyArray(q)) q->front = 0;
    q->rear = (q->rear + 1) % SIZE;
    q->items[q->rear] = val;
}

int dequeueArray(ArrayQueue *q) {
    if (isEmptyArray(q)) {
        printf("Array Queue EMPTY\n");
        return -1;
    }
    int val = q->items[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front = (q->front + 1) % SIZE;
    return val;
}

void displayArray(ArrayQueue *q) {
    if (isEmptyArray(q)) {
        printf("Array Queue EMPTY\n");
        return;
    }
    int i = q->front;
    printf("Array Queue: ");
    while (1) {
        printf("%d ", q->items[i]);
        if (i == q->rear) break;
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *front, *rear;
} ListQueue;

void initListQueue(ListQueue *q) {
    q->front = q->rear = NULL;
}

int isEmptyList(ListQueue *q) {
    return (q->front == NULL);
}

void enqueueList(ListQueue *q, int val) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;
    if (isEmptyList(q)) {
        q->front = q->rear = newNode;
        newNode->next = newNode;
    } else {
        newNode->next = q->front;
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

int dequeueList(ListQueue *q) {
    if (isEmptyList(q)) {
        printf("List Queue EMPTY\n");
        return -1;
    }
    int val = q->front->data;
    if (q->front == q->rear) {
        free(q->front);
        q->front = q->rear = NULL;
    } else {
        Node *temp = q->front;
        q->front = q->front->next;
        q->rear->next = q->front;
        free(temp);
    }
    return val;
}

void displayList(ListQueue *q) {
    if (isEmptyList(q)) {
        printf("List Queue EMPTY\n");
        return;
    }
    Node *temp = q->front;
    printf("List Queue: ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != q->front);
    printf("\n");
}

int main() {
    ArrayQueue aq;
    initArrayQueue(&aq);
    enqueueArray(&aq, 5);
    enqueueArray(&aq, 10);
    enqueueArray(&aq, 15);
    displayArray(&aq);
    printf("Dequeued (Array): %d\n", dequeueArray(&aq));
    displayArray(&aq);
    enqueueArray(&aq, 2);
    displayArray(&aq);

    ListQueue lq;
    initListQueue(&lq);
    enqueueList(&lq, 10);
    enqueueList(&lq, 20);
    enqueueList(&lq, 30);
    displayList(&lq);
    printf("Dequeued (List): %d\n", dequeueList(&lq));
    displayList(&lq);
    enqueueList(&lq, 10);
    displayList(&lq);

    return 0;
}


