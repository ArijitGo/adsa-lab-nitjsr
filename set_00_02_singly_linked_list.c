#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* head = NULL;

// Insert
void insert(int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        return;
    }
    struct Node* temp = head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newNode;
}

// Delete by value
void deleteByValue(int val) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    if (head->data == val) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
        printf("Deleted %d\n", val);
        return;
    }
    struct Node* temp = head;
    while (temp->next != NULL && temp->next->data != val) {
        temp = temp->next;
    }
    if (temp->next != NULL) {
        struct Node* del = temp->next;
        temp->next = del->next;
        free(del);
        printf("Deleted %d\n", val);
    } else {
        printf("Value not found.\n");
    }
}

// Delete from last
void deleteLast(){
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    if(head->next == NULL){
        struct Node* temp = head;
        head = head->next;
        free(temp);
        printf("Deleted. \n");
        return;
    }
    if(head->next->next == NULL){
        struct Node* temp = head->next;
        head->next = NULL;
        free(temp);
        printf("Deleted. \n");
        return;
    }
    struct Node* temp = head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    struct Node* del = temp->next;
    temp->next = NULL;
    free(del);
}

// Search
void search(int val) {
    struct Node* temp = head;
    int pos = 0;
    while (temp != NULL) {
        if (temp->data == val) {
            printf("Found %d at position %d\n", val, pos);
            return;
        }
        temp = temp->next;
        pos++;
    }
    printf("Value not found.\n");
}

// Display
void display() {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node* temp = head;
    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    int choice, val;

    do {
        printf("\n--- Singly Linked List Menu ---\n");
        printf(" 1. Insert\n 2. Delete By Value \n 3. Delete Last \n 4. Search\n 5. Display\n 6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                insert(val);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &val);
                deleteByValue(val);
                break;
            case 3:
                deleteLast();
                printf("Last node deleted. ");
                break;
            case 4:
                printf("Enter value to search: ");
                scanf("%d", &val);
                search(val);
                break;
            case 5:
                display();
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 6);

    return 0;
}