#include <iostream>
#include <stdlib.h>

using namespace std;


struct node {
    int data;
    struct node* left;
    struct node* right;
};

// New node creation
struct node* newNode(int data) {
    struct node *node = (struct node*)malloc(sizeof(struct node));

    node->data = data;
    node->left = nullptr;
    node->right= nullptr;

    return (node);
}

void traversePreorder(struct node* tree_node) {
    // nlr
    if (tree_node == nullptr) return;

    cout << tree_node->data << " - " << endl;
    traversePreorder(tree_node->left);
    traversePreorder(tree_node->right);
}

void traverseInorder(struct node* tree_node) {
    // lnr
    if (tree_node == nullptr) return;


    traverseInorder(tree_node->left);
    cout << tree_node->data << " - " << endl;
    traverseInorder(tree_node->right);
}

void traversePostorder(struct node* tree_node) {
    // lrn
    if (tree_node == nullptr) return;


    traversePostorder(tree_node->left);
    traversePostorder(tree_node->right);
    cout << tree_node->data << " - " << endl;
}

int main() {
    struct node* root = newNode(1);

    root->left = newNode(2);
    root->left->left = newNode(4);
    root->right = newNode(3);

    cout << "preorder traversal: " << endl;
    traversePreorder(root);

    cout << " " << endl;

    cout << "inorder traversal: " << endl;
    traverseInorder(root);

    cout << " " << endl;

    cout << "postorder traversal: " << endl;
    traversePostorder(root);

    return 1;
}