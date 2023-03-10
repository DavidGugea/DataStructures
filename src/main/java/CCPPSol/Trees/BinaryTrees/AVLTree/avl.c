#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;

    struct Node* left;
    struct Node* right;

    int height;
};

int height(struct Node* N) {
    if (N == NULL)
        return 0;

    return N->height;
}

int max(int a, int b) {
    return a > b ? a : b;
}

struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;  // new node is initially added at leaf.
    
    return node;
}

struct Node* rightRotate(struct Node* y) {
    // rotate a subtree rooted at y to the right
    struct Node* x = y->left;
    struct Node* T1 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T1;

    // Update heights
    y->height = max(
        height(y->left),
        height(y->right)
    ) + 1;

    x->height = max(
        height(x->left),
        height(x->right)
    ) + 1;

    // Return new root
    return x;
}

struct Node* leftRotate(struct Node* y) {
    // Rotate a subtree rooted at y to the left
    struct Node* x = y->right;
    struct Node* T1 = x->left;

    x->left = y;
    y->right = T1;

    y->height = max(
        height(y->left),
        height(y->right)
    ) + 1;

    x->height = max(
        height(x->left),
        height(x->right)
    ) + 1;

    return x;
}

int getBalance(struct Node* N) {
    if (N == NULL)
        return 0;

    return height(N->left) - height(N->right);
}

/*
* node -> root
* key -> key of the new node
* returns: new root of the subtree
*/
struct Node* insert(struct Node* node, int key) {
    // default BST insertion
    if (node == NULL)
        return (newNode(key));

    if(key < node->key)
        node->left = insert(node->left, key);
    else if(key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    // Update height of the ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // Get the bf of this ancestor node to check wheter this node became unbalanced
    int balance = getBalance(node);

    // LL CASE
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // RR CASE
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // LR CASE
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL CASE
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    
    while (current->left != NULL)
        current = current->left;

    return current;
}

struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Node with only one child
        if ( root->left == NULL || root->right == NULL ) {
            struct Node* temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }

            free(temp);
        } else {
            struct Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // In case that the tree only had one node
    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    // LL CASE
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    // RR CASE
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    // LR CASE
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL CASE
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void preorder(struct Node* root) {
    if (root == NULL)
        return;

    printf("%d - ", root -> key);
    preorder(root->left);
    preorder(root->right);
}

int main() {
    struct Node* root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    preorder(root);
    printf("\n");


    preorder(root);
    printf("\n");

    return 0;
}