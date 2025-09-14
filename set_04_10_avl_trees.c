#include <stdio.h>
#include <stdlib.h>

// ==================== AVL TREE IMPLEMENTATION ====================

typedef struct AVLNode {
    int key;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

AVLNode* createAVLTree() {
    return NULL;
}

int height(AVLNode *node) {
    return node ? node->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

AVLNode* createAVLNode(int key) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

AVLNode* rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode* leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(AVLNode *node) {
    return node ? height(node->left) - height(node->right) : 0;
}

AVLNode* insertAVLItem(AVLNode* node, int key) {
    if (!node) return createAVLNode(key);

    if (key < node->key)
        node->left = insertAVLItem(node->left, key);
    else if (key > node->key)
        node->right = insertAVLItem(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key) return rightRotate(node);
    if (balance < -1 && key > node->right->key) return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

AVLNode* minValueAVLNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left) current = current->left;
    return current;
}

AVLNode* deleteAVLItem(AVLNode* root, int key) {
    if (!root) return root;

    if (key < root->key)
        root->left = deleteAVLItem(root->left, key);
    else if (key > root->key)
        root->right = deleteAVLItem(root->right, key);
    else {
        if (!root->left || !root->right) {
            AVLNode* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        }
        AVLNode* temp = minValueAVLNode(root->right);
        root->key = temp->key;
        root->right = deleteAVLItem(root->right, temp->key);
    }

    if (!root) return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

AVLNode* searchAVLItem(AVLNode* root, int key) {
    if (!root || root->key == key) return root;
    return searchAVLItem(key < root->key ? root->left : root->right, key);
}

void deleteAVLTree(AVLNode* root) {
    if (root) {
        deleteAVLTree(root->left);
        deleteAVLTree(root->right);
        free(root);
    }
}

void printAVLInOrder(AVLNode* root) {
    if (root) {
        printAVLInOrder(root->left);
        printf("%d ", root->key);
        printAVLInOrder(root->right);
    }
}

void avlTreeExample() {
    printf("=== AVL Tree Example ===\n");
    AVLNode *root = createAVLTree();
    
    root = insertAVLItem(root, 10);
    root = insertAVLItem(root, 20);
    root = insertAVLItem(root, 30);
    root = insertAVLItem(root, 40);
    root = insertAVLItem(root, 50);
    root = insertAVLItem(root, 25);
    
    printf("In-order traversal: ");
    printAVLInOrder(root);
    printf("\n");
    
    AVLNode* found = searchAVLItem(root, 30);
    if (found) printf("Found 30 in the tree\n");
    
    root = deleteAVLItem(root, 30);
    printf("After deleting 30: ");
    printAVLInOrder(root);
    printf("\n");
    
    deleteAVLTree(root);
    printf("Tree deleted\n\n");
}

// ==================== RED-BLACK TREE IMPLEMENTATION ====================

typedef enum { RED, BLACK } Color;

typedef struct RBNode {
    int key;
    Color color;
    struct RBNode *left, *right, *parent;
} RBNode;

RBNode* createRBTree() {
    return NULL;
}

RBNode* createRBNode(int key) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    node->key = key;
    node->color = RED;
    node->left = node->right = node->parent = NULL;
    return node;
}

void leftRotateRB(RBNode **root, RBNode *x) {
    RBNode *y = x->right;
    x->right = y->left;
    
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    
    if (!x->parent) *root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
        
    y->left = x;
    x->parent = y;
}

void rightRotateRB(RBNode **root, RBNode *y) {
    RBNode *x = y->left;
    y->left = x->right;
    
    if (x->right) x->right->parent = y;
    x->parent = y->parent;
    
    if (!y->parent) *root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
        
    x->right = y;
    y->parent = x;
}

void fixViolation(RBNode **root, RBNode *z) {
    while (z != *root && z->parent->color == RED) {
        RBNode *grandparent = z->parent->parent;
        
        if (z->parent == grandparent->left) {
            RBNode *uncle = grandparent->right;
            
            if (uncle && uncle->color == RED) {
                grandparent->color = RED;
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z = grandparent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotateRB(root, z);
                }
                
                z->parent->color = BLACK;
                grandparent->color = RED;
                rightRotateRB(root, grandparent);
            }
        } else {
            RBNode *uncle = grandparent->left;
            
            if (uncle && uncle->color == RED) {
                grandparent->color = RED;
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z = grandparent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotateRB(root, z);
                }
                
                z->parent->color = BLACK;
                grandparent->color = RED;
                leftRotateRB(root, grandparent);
            }
        }
    }
    
    (*root)->color = BLACK;
}

RBNode* insertRBItem(RBNode *root, int key) {
    RBNode *z = createRBNode(key);
    
    if (!root) {
        z->color = BLACK;
        return z;
    }
    
    RBNode *y = NULL;
    RBNode *x = root;
    
    while (x) {
        y = x;
        if (z->key < x->key) x = x->left;
        else x = x->right;
    }
    
    z->parent = y;
    
    if (!y) root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;
        
    fixViolation(&root, z);
    return root;
}

RBNode* searchRBItem(RBNode* root, int key) {
    if (!root || root->key == key) return root;
    return searchRBItem(key < root->key ? root->left : root->right, key);
}

void deleteRBTree(RBNode* root) {
    if (root) {
        deleteRBTree(root->left);
        deleteRBTree(root->right);
        free(root);
    }
}

void printRBInOrder(RBNode* root) {
    if (root) {
        printRBInOrder(root->left);
        printf("%d(%s) ", root->key, root->color == RED ? "R" : "B");
        printRBInOrder(root->right);
    }
}

void redBlackTreeExample() {
    printf("=== Red-Black Tree Example ===\n");
    RBNode *root = createRBTree();
    
    root = insertRBItem(root, 7);
    root = insertRBItem(root, 3);
    root = insertRBItem(root, 18);
    root = insertRBItem(root, 10);
    root = insertRBItem(root, 22);
    root = insertRBItem(root, 8);
    root = insertRBItem(root, 11);
    root = insertRBItem(root, 26);
    
    printf("In-order traversal: ");
    printRBInOrder(root);
    printf("\n");
    
    RBNode* found = searchRBItem(root, 10);
    if (found) printf("Found 10 in the tree\n");
    
    deleteRBTree(root);
    printf("Tree deleted\n\n");
}

// ==================== B-TREE IMPLEMENTATION ====================

#define MIN_DEGREE 2

typedef struct BTreeNode {
    int *keys;
    struct BTreeNode **children;
    int numKeys;
    int isLeaf;
} BTreeNode;

BTreeNode* createBTree() {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->keys = (int*)malloc((2 * MIN_DEGREE - 1) * sizeof(int));
    node->children = (BTreeNode**)malloc(2 * MIN_DEGREE * sizeof(BTreeNode*));
    node->numKeys = 0;
    node->isLeaf = 1;
    return node;
}

BTreeNode* searchBItem(BTreeNode* root, int key, int *index) {
    int i = 0;
    while (i < root->numKeys && key > root->keys[i]) i++;
        
    if (i < root->numKeys && key == root->keys[i]) {
        *index = i;
        return root;
    }
    
    if (root->isLeaf) return NULL;
    return searchBItem(root->children[i], key, index);
}

void splitChild(BTreeNode *parent, int i, BTreeNode *child) {
    BTreeNode *newChild = createBTree();
    newChild->isLeaf = child->isLeaf;
    newChild->numKeys = MIN_DEGREE - 1;
    
    for (int j = 0; j < MIN_DEGREE - 1; j++)
        newChild->keys[j] = child->keys[j + MIN_DEGREE];
        
    if (!child->isLeaf) {
        for (int j = 0; j < MIN_DEGREE; j++)
            newChild->children[j] = child->children[j + MIN_DEGREE];
    }
    
    child->numKeys = MIN_DEGREE - 1;
    
    for (int j = parent->numKeys; j >= i + 1; j--)
        parent->children[j + 1] = parent->children[j];
        
    parent->children[i + 1] = newChild;
    
    for (int j = parent->numKeys - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];
        
    parent->keys[i] = child->keys[MIN_DEGREE - 1];
    parent->numKeys++;
}

void insertNonFull(BTreeNode *node, int key) {
    int i = node->numKeys - 1;
    
    if (node->isLeaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        
        node->keys[i + 1] = key;
        node->numKeys++;
    } else {
        while (i >= 0 && key < node->keys[i]) i--;
        i++;
        
        if (node->children[i]->numKeys == 2 * MIN_DEGREE - 1) {
            splitChild(node, i, node->children[i]);
            if (key > node->keys[i]) i++;
        }
        
        insertNonFull(node->children[i], key);
    }
}

BTreeNode* insertBItem(BTreeNode *root, int key) {
    if (!root) {
        root = createBTree();
        root->keys[0] = key;
        root->numKeys = 1;
        return root;
    }
    
    if (root->numKeys == 2 * MIN_DEGREE - 1) {
        BTreeNode *newRoot = createBTree();
        newRoot->isLeaf = 0;
        newRoot->children[0] = root;
        splitChild(newRoot, 0, root);
        
        int i = 0;
        if (newRoot->keys[0] < key) i++;
        insertNonFull(newRoot->children[i], key);
        
        return newRoot;
    } else {
        insertNonFull(root, key);
        return root;
    }
}

void deleteBTree(BTreeNode* root) {
    if (root) {
        if (!root->isLeaf) {
            for (int i = 0; i <= root->numKeys; i++)
                deleteBTree(root->children[i]);
        }
        free(root->keys);
        free(root->children);
        free(root);
    }
}

void printBTree(BTreeNode* root, int level) {
    if (root) {
        printf("Level %d: ", level);
        for (int i = 0; i < root->numKeys; i++)
            printf("%d ", root->keys[i]);
        printf("\n");
        
        if (!root->isLeaf) {
            for (int i = 0; i <= root->numKeys; i++)
                printBTree(root->children[i], level + 1);
        }
    }
}

void bTreeExample() {
    printf("=== B Tree Example ===\n");
    BTreeNode *root = createBTree();
    
    root = insertBItem(root, 10);
    root = insertBItem(root, 20);
    root = insertBItem(root, 5);
    root = insertBItem(root, 6);
    root = insertBItem(root, 12);
    root = insertBItem(root, 30);
    root = insertBItem(root, 7);
    root = insertBItem(root, 17);
    
    printf("B Tree structure:\n");
    printBTree(root, 0);
    
    int index;
    BTreeNode* found = searchBItem(root, 6, &index);
    if (found) printf("Found 6 in the tree at index %d\n", index);
    
    deleteBTree(root);
    printf("Tree deleted\n\n");
}

// ==================== B+ TREE IMPLEMENTATION ====================

#define MIN_DEGREE_BPLUS 2

typedef struct BPlusTreeNode {
    int *keys;
    void **pointers;
    struct BPlusTreeNode **children;
    int numKeys;
    int isLeaf;
    struct BPlusTreeNode *next;
} BPlusTreeNode;

BPlusTreeNode* createBPlusTree() {
    BPlusTreeNode* node = (BPlusTreeNode*)malloc(sizeof(BPlusTreeNode));
    node->keys = (int*)malloc((2 * MIN_DEGREE_BPLUS - 1) * sizeof(int));
    node->pointers = (void**)malloc(2 * MIN_DEGREE_BPLUS * sizeof(void*));
    node->children = (BPlusTreeNode**)malloc(2 * MIN_DEGREE_BPLUS * sizeof(BPlusTreeNode*));
    node->numKeys = 0;
    node->isLeaf = 1;
    node->next = NULL;
    return node;
}

void* searchBPlusItem(BPlusTreeNode* root, int key) {
    if (!root) return NULL;
    
    int i = 0;
    while (i < root->numKeys && key > root->keys[i]) i++;
        
    if (root->isLeaf) {
        return (i < root->numKeys && key == root->keys[i]) ? root->pointers[i] : NULL;
    } else {
        return searchBPlusItem(root->children[i], key);
    }
}

void splitChildBPlus(BPlusTreeNode *parent, int i, BPlusTreeNode *child) {
    BPlusTreeNode *newChild = createBPlusTree();
    newChild->isLeaf = child->isLeaf;
    newChild->numKeys = MIN_DEGREE_BPLUS - 1;
    
    for (int j = 0; j < MIN_DEGREE_BPLUS - 1; j++)
        newChild->keys[j] = child->keys[j + MIN_DEGREE_BPLUS];
        
    if (child->isLeaf) {
        for (int j = 0; j < MIN_DEGREE_BPLUS; j++)
            newChild->pointers[j] = child->pointers[j + MIN_DEGREE_BPLUS];
            
        newChild->next = child->next;
        child->next = newChild;
    } else {
        for (int j = 0; j < MIN_DEGREE_BPLUS; j++)
            newChild->children[j] = child->children[j + MIN_DEGREE_BPLUS];
    }
    
    child->numKeys = MIN_DEGREE_BPLUS;
    
    for (int j = parent->numKeys; j >= i + 1; j--)
        parent->children[j + 1] = parent->children[j];
        
    parent->children[i + 1] = newChild;
    
    for (int j = parent->numKeys - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];
        
    parent->keys[i] = newChild->keys[0];
    parent->numKeys++;
    
    if (!child->isLeaf) {
        for (int j = 0; j < newChild->numKeys; j++)
            newChild->keys[j] = newChild->keys[j + 1];
        newChild->numKeys--;
    }
}

void insertNonFullBPlus(BPlusTreeNode *node, int key, void *value) {
    int i = node->numKeys - 1;
    
    if (node->isLeaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            node->pointers[i + 1] = node->pointers[i];
            i--;
        }
        
        node->keys[i + 1] = key;
        node->pointers[i + 1] = value;
        node->numKeys++;
    } else {
        while (i >= 0 && key < node->keys[i]) i--;
        i++;
        
        if (node->children[i]->numKeys == 2 * MIN_DEGREE_BPLUS - 1) {
            splitChildBPlus(node, i, node->children[i]);
            if (key > node->keys[i]) i++;
        }
        
        insertNonFullBPlus(node->children[i], key, value);
    }
}

BPlusTreeNode* insertBPlusItem(BPlusTreeNode *root, int key, void *value) {
    if (!root) {
        root = createBPlusTree();
        root->keys[0] = key;
        root->pointers[0] = value;
        root->numKeys = 1;
        return root;
    }
    
    if (root->numKeys == 2 * MIN_DEGREE_BPLUS - 1) {
        BPlusTreeNode *newRoot = createBPlusTree();
        newRoot->isLeaf = 0;
        newRoot->children[0] = root;
        splitChildBPlus(newRoot, 0, root);
        
        int i = 0;
        if (newRoot->keys[0] < key) i++;
        insertNonFullBPlus(newRoot->children[i], key, value);
        
        return newRoot;
    } else {
        insertNonFullBPlus(root, key, value);
        return root;
    }
}

void deleteBPlusTree(BPlusTreeNode* root) {
    if (root) {
        if (!root->isLeaf) {
            for (int i = 0; i <= root->numKeys; i++)
                deleteBPlusTree(root->children[i]);
        }
        free(root->keys);
        free(root->pointers);
        free(root->children);
        free(root);
    }
}

void printBPlusTree(BPlusTreeNode* root, int level) {
    if (root) {
        printf("Level %d: ", level);
        for (int i = 0; i < root->numKeys; i++)
            printf("%d ", root->keys[i]);
        printf("\n");
        
        if (!root->isLeaf) {
            for (int i = 0; i <= root->numKeys; i++)
                printBPlusTree(root->children[i], level + 1);
        } else {
            printf("Leaf node values: ");
            for (int i = 0; i < root->numKeys; i++)
                printf("%d ", *(int*)root->pointers[i]);
            printf("\n");
        }
    }
}

void bPlusTreeExample() {
    printf("=== B+ Tree Example ===\n");
    BPlusTreeNode *root = createBPlusTree();
    
    int values[] = {100, 200, 300, 400, 500, 600, 700, 800};
    
    root = insertBPlusItem(root, 10, &values[0]);
    root = insertBPlusItem(root, 20, &values[1]);
    root = insertBPlusItem(root, 5, &values[2]);
    root = insertBPlusItem(root, 6, &values[3]);
    root = insertBPlusItem(root, 12, &values[4]);
    root = insertBPlusItem(root, 30, &values[5]);
    root = insertBPlusItem(root, 7, &values[6]);
    root = insertBPlusItem(root, 17, &values[7]);
    
    printf("B+ Tree structure:\n");
    printBPlusTree(root, 0);
    
    int* found = (int*)searchBPlusItem(root, 6);
    if (found) printf("Found value %d for key 6\n", *found);
    
    deleteBPlusTree(root);
    printf("Tree deleted\n\n");
}

// ==================== MAIN FUNCTION ====================

int main() {
    printf("Tree Implementations in C\n\n");
    
    // AVL Tree Example
    avlTreeExample();
    
    // Red-Black Tree Example
    redBlackTreeExample();
    
    // B Tree Example
    bTreeExample();
    
    // B+ Tree Example
    bPlusTreeExample();
    
    return 0;
}