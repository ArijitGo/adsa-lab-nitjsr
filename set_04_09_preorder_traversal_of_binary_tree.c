#include <stdio.h>
#include <stdlib.h>

struct Node{
    int val;
    struct Node *right;
    struct Node *left;
};

struct Node* newNode(int data){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->val = data;
    node->left = node->right = NULL;
    return node;
}

struct Stack {
    int top;
    int capacity;
    struct Node** array;
};

struct Stack* createStack(int capacity){
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (struct Node**)malloc(capacity * sizeof(struct Node*));
    return stack;
}

int isEmpty(struct Stack* stack){
    return stack->top == -1;
}

void push(struct Stack* stack, struct Node* node){
    stack->array[++stack->top] = node;
}

struct Node* pop(struct Stack* stack){
    return stack->array[stack->top--];
}

void preorder(struct Node* root){
    if(root == NULL){
        return;
    }
    struct Stack* stack = createStack(100);
    push(stack, root);

    while(!isEmpty(stack)){
        struct Node* current = pop(stack);
        printf("%d ",current->val);
        if(current->right){
            push(stack, current->right);
        }
        if(current->left){
            push(stack, current->left);
        }
    }
    free(stack->array);
    free(stack);
}

int main(){
    struct Node* root = newNode(1);
    root->left = newNode(5);
    root->right = newNode(10);
    root->left->left = newNode(15);
    root->left->right = newNode(20);
    root->right->left = newNode(25);
    root->right->right = newNode(30);

    preorder(root);
    
    return 0;
}