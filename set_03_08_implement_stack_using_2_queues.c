#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int arr[MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

int isEmptyQueue(Queue *q) {
    return q->front == -1;
}

int isFullQueue(Queue *q) {
    return (q->rear + 1) % MAX == q->front;
}

void enqueue(Queue *q, int val) {
    if (isFullQueue(q)) {
        printf("Queue Overflow\n");
        return;
    }
    if (isEmptyQueue(q)) q->front = 0;
    q->rear = (q->rear + 1) % MAX;
    q->arr[q->rear] = val;
}

int dequeue(Queue *q) {
    if (isEmptyQueue(q)) {
        printf("Queue Underflow\n");
        return -1;
    }
    int val = q->arr[q->front];
    if (q->front == q->rear) q->front = q->rear = -1;
    else q->front = (q->front + 1) % MAX;
    return val;
}

int front(Queue *q) {
    if (isEmptyQueue(q)) return -1;
    return q->arr[q->front];
}

// Method 1 – Costly Push
typedef struct {
    Queue q1, q2;
} Stack1;

void initStack1(Stack1 *s) {
    initQueue(&s->q1);
    initQueue(&s->q2);
}

void push1(Stack1 *s, int val) {
    while (!isEmptyQueue(&s->q1)) enqueue(&s->q2, dequeue(&s->q1));
    enqueue(&s->q1, val);
    while (!isEmptyQueue(&s->q2)) enqueue(&s->q1, dequeue(&s->q2));
}

int pop1(Stack1 *s) {
    if (isEmptyQueue(&s->q1)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return dequeue(&s->q1);
}

//Method 2 – Costly Pop
typedef struct {
    Queue q1, q2;
} Stack2;

void initStack2(Stack2 *s) {
    initQueue(&s->q1);
    initQueue(&s->q2);
}

void push2(Stack2 *s, int val) {
    enqueue(&s->q1, val);
}

int pop2(Stack2 *s) {
    if (isEmptyQueue(&s->q1)) {
        printf("Stack Underflow\n");
        return -1;
    }

    while (s->q1.front != s->q1.rear) {
        enqueue(&s->q2, dequeue(&s->q1));
    }
    int val = dequeue(&s->q1);

    Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;

    return val;
}

int main() {
    Stack1 s1;
    Stack2 s2;
    initStack1(&s1);
    initStack2(&s2);

    printf("--- Method 1: Costly Push ---\n");
    push1(&s1, 155);
    push1(&s1, 195);
    push1(&s1, 23);
    printf("Pop: %d\n", pop1(&s1));
    printf("Pop: %d\n", pop1(&s1));

    printf("\n--- Method 2: Costly Pop ---\n");
    push2(&s2, 55);
    push2(&s2, 68);
    push2(&s2, 79);
    printf("Pop: %d\n", pop2(&s2));
    printf("Pop: %d\n", pop2(&s2));

    return 0;
}
