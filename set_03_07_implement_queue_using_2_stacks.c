#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int arr[MAX];
    int top;
} Stack;

void init(Stack *s) { s->top = -1; }
int isEmpty(Stack *s) { return s->top == -1; }
int isFull(Stack *s) { return s->top == MAX - 1; }

void push(Stack *s, int val) {
    if (isFull(s)) { printf("Stack Overflow\n"); return; }
    s->arr[++s->top] = val;
}
int pop(Stack *s) {
    if (isEmpty(s)) { printf("Stack Underflow\n"); return -1; }
    return s->arr[s->top--];
}
int peek(Stack *s) {
    if (isEmpty(s)) return -1;
    return s->arr[s->top];
}

// Queue with costly push
typedef struct {
    Stack s1, s2;
} Queue1;

void initQ1(Queue1 *q) {
    init(&q->s1);
    init(&q->s2);
}

void enqueue1(Queue1 *q, int val) {
    while (!isEmpty(&q->s1)) push(&q->s2, pop(&q->s1));
    push(&q->s1, val);
    while (!isEmpty(&q->s2)) push(&q->s1, pop(&q->s2));
}

int dequeue1(Queue1 *q) {
    if (isEmpty(&q->s1)) { printf("Queue Empty\n"); return -1; }
    return pop(&q->s1);
}

// Queue with costly pop
typedef struct {
    Stack s1, s2;
} Queue2;

void initQ2(Queue2 *q) {
    init(&q->s1);
    init(&q->s2);
}

void enqueue2(Queue2 *q, int val) {
    push(&q->s1, val);
}

int dequeue2(Queue2 *q) {
    if (isEmpty(&q->s1)) { printf("Queue Empty\n"); return -1; }
    while (!isEmpty(&q->s1)) push(&q->s2, pop(&q->s1));
    int val = pop(&q->s2);
    while (!isEmpty(&q->s2)) push(&q->s1, pop(&q->s2));
    return val;
}

int main() {
    Queue1 q1;
    Queue2 q2;
    initQ1(&q1);
    initQ2(&q2);

    // Method-1: Costly push
    printf("--- Method 1: Costly Enqueue ---\n");
    enqueue1(&q1, 50);
    enqueue1(&q1, 60);
    enqueue1(&q1, 70);
    printf("Dequeue: %d\n", dequeue1(&q1));
    printf("Dequeue: %d\n", dequeue1(&q1));

    // Method-2: Costly pop
    printf("\n--- Method 2: Costly Dequeue ---\n");
    enqueue2(&q2, 30);
    enqueue2(&q2, 40);
    enqueue2(&q2, 50);
    printf("Dequeue: %d\n", dequeue2(&q2));
    printf("Dequeue: %d\n", dequeue2(&q2));

    return 0;
}
