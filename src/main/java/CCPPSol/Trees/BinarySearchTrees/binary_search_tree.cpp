#include <iostream>

using namespace std;

class Node {
public:
    int value;
    Node* left;
    Node* right;
    Node* parent;
    
    Node(int value) {
        this->value = value;
    }
};


class BinarySearchTree {
public:
    int size;
    Node* root;

    void insert(int value);
    Node* search(int value);
    Node* delete_node_with_value(int value);

    Node* find_min_in_subtree(Node* root);
    Node* find_max_in_subtree(Node* root);

    void print_preorder(Node* node);
    void print_inorder(Node* node);
    void print_postorder(Node* node);
};


void BinarySearchTree::insert(int value) {
    if(this->root == nullptr) {
        this->root = new Node(value);
        return;
    }

    Node* backtracking_node = nullptr;
    Node* root_node = this->root;

    while (root_node != nullptr) {
        backtracking_node = root_node;

        if(value < root_node->value) {
            root_node = root_node->left;
        } else if(value > root_node->value) {
            root_node = root_node->right;
        }
    }

    Node* new_node = new Node(value);
    new_node->parent = backtracking_node;

    if(value < backtracking_node->value) {
        backtracking_node->left = new_node;
    } else if(value > backtracking_node->value) {
        backtracking_node->right = new_node;
    }
}

void BinarySearchTree::print_preorder(Node* node) {
    // nlr
    if(node == nullptr) {
        return;
    }

    cout << node->value << " - ";
    this->print_preorder(node->left);
    this->print_preorder(node->right);
}

void BinarySearchTree::print_inorder(Node* node) {
    // lnr
    if (node == nullptr) {
        return;
    }

    this->print_inorder(node->left);
    cout << node->value << " - ";
    this->print_inorder(node->right);
}

void BinarySearchTree::print_postorder(Node* node) {
    // lrn
    if (node == nullptr) {
        return;
    }

    this->print_postorder(node->left);
    this->print_postorder(node->right);
    cout << node->value << " - ";
}

Node* BinarySearchTree::search(int value) {
    Node* node = this->root;

    while(node != nullptr && node->value != value) {
        if (value < node->value) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    return node;
}

Node* BinarySearchTree::find_min_in_subtree(Node* root) {
    Node* backtracking_node = nullptr;

    while (root != nullptr) {
        backtracking_node = root;
        root = root->left;
    }

    return backtracking_node;
}

Node* BinarySearchTree::find_max_in_subtree(Node* root) {
    Node* backtracking_node = nullptr;

    while (root != nullptr) {
        backtracking_node = root;
        root = root->right;
    }

    return backtracking_node;
}

Node* BinarySearchTree::delete_node_with_value(int value) {
    Node* delete_node = this->search(value);

    if(delete_node->left == nullptr && delete_node->right == nullptr) {
        if(delete_node->parent->left != nullptr && delete_node->parent->left->value == delete_node->value) {
            delete_node->parent->left = nullptr;
        } else if(delete_node->parent->right != nullptr && delete_node->parent->right->value == delete_node->value) {
            delete_node->parent->right = nullptr;
        }
    } else if(delete_node->left != nullptr && delete_node->right == nullptr) {
        delete_node->parent->left = delete_node->left;
        delete_node->left->parent = delete_node->parent;
    } else if(delete_node->left == nullptr && delete_node->right != nullptr) {
        delete_node->parent->right = delete_node->right;
        delete_node->right->parent = delete_node->parent;
    } else if(delete_node->left != nullptr && delete_node->right != nullptr) {
        Node* max_node_in_subtree = this->find_max_in_subtree(delete_node->right);
        this->delete_node_with_value(max_node_in_subtree->value);
        
        max_node_in_subtree->parent=delete_node->parent;

        delete_node->left->parent = max_node_in_subtree;
        delete_node->right->parent = max_node_in_subtree;

        max_node_in_subtree->left = delete_node->left;
        max_node_in_subtree->right = delete_node->right;

        if(this->root->value == delete_node->value) {
            this->root = max_node_in_subtree;
            return delete_node;
        }

        if(delete_node->parent->right != nullptr && delete_node->parent->right->value == delete_node->value) {
            delete_node->parent->right = max_node_in_subtree;
        } else if(delete_node->parent->left != nullptr && delete_node->parent->left->value == delete_node->value) {
            delete_node->parent->left = max_node_in_subtree;
        }
    }

    return delete_node;
}

int main() {
    BinarySearchTree* bst = new BinarySearchTree();
    int bst_values[] = {12, 5, 3, 7, 15, 13, 20, 19, 27};

    for(int i : bst_values) {
        bst->insert(i);
    }

    bst->print_preorder(bst->root);
    cout << " " << endl;
    bst->delete_node_with_value(12);
    bst->print_preorder(bst->root);
    cout << " " << endl;

    return 1;
}