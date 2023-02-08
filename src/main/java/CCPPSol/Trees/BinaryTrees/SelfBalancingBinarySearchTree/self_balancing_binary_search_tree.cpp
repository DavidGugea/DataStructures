#include <iostream>

using namespace std;

class Node {
public:
    int data;

    Node* left;
    Node* right;
    Node* parent;

    Node(int data) {
        this->data = data;

        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
    }
};

class SelfBalancingBinarySearchTree {
public:
    int size = 0;
    Node* root;

    void insert(int data);
    void left_rotation();
    void right_rotation();

    Node* search(int data);

    Node* delete_root_node();

    void delete_leaf_node(Node* leaf_node);
    void delete_node_with_child_left(Node* delete_node);
    void delete_node_with_child_right(Node* delete_node);
    void delete_node_with_two_children(Node* delete_node);

    Node* delete_node_with_data(int data);

    Node* find_max_in_subtree(Node* subtree_root_node);
    Node* find_min_in_subtree(Node* subtree_root_node);

    int get_height_in_subtree(Node* subtree_root_node);

    void print_preorder(Node* node);
    void print_inorder(Node* node);
    void print_postorder(Node* node);
};

void SelfBalancingBinarySearchTree::right_rotation() {
    cout << "RIGHT ROTATION" << endl;
    Node* current_root = this->root; // y
    Node* replace_root = this->root->left; // x
    Node* left_subtree_root_left = this->root->left->left; // alpha
    Node* left_subtree_root_right = this->root->left->right; // beta
    Node* replace_root_right = this->root->right; // gamma

    this->root = replace_root;
    this->root->left = left_subtree_root_left;
    this->root->right = current_root;
    this->root->right->left = left_subtree_root_right;
    this->root->right->right = replace_root_right;
}

void SelfBalancingBinarySearchTree::left_rotation() {
    cout << "LEFT ROTATION" << endl;
    Node* current_root = this->root;
    Node* replace_root = this->root->right;
    Node* left_subtree_root = this->root->left;
    Node* left_replace_root = this->root->right->left;
    Node* right_replace_root = this->root->right->right;

    this->root = replace_root;
    this->root->left = current_root;
    this->root->left->left = left_subtree_root;
    this->root->left->right = left_replace_root;
    this->root->right = right_replace_root;
}

Node* SelfBalancingBinarySearchTree::delete_root_node() {
    Node* replace_node;
    if(this->root->right != nullptr) {
        replace_node = this->find_max_in_subtree(this->root->right);
    } else if(this->root->left != nullptr) {
        replace_node = this->find_max_in_subtree(this->root->left);
    }

    this->delete_node_with_data(replace_node->data);

    replace_node->left = this->root->left;
    replace_node->right = this->root->right;

    if(this->root->left != nullptr) {
        this->root->left->parent = replace_node;
    }
    if(this->root->right != nullptr) {
        this->root->right->parent = replace_node;
    }

    this->size -= 1;
    this->root = replace_node;
    return this->root;
}

void SelfBalancingBinarySearchTree::delete_leaf_node(Node* leaf_node) {
    if(leaf_node->parent->left != nullptr && leaf_node->parent->left->data == leaf_node->data) {
        leaf_node->parent->left = nullptr;
    } else if (leaf_node->parent->right != nullptr && leaf_node->parent->right->data == leaf_node->data) {
        leaf_node->parent->right = nullptr;
    }
}

void SelfBalancingBinarySearchTree::delete_node_with_child_left(Node* delete_node) {
    if(delete_node->parent->left != nullptr && delete_node->parent->left->data == delete_node->data) {
        delete_node->parent->left = delete_node->left;
    } else if(delete_node->parent->right != nullptr && delete_node->parent->right->data == delete_node->data) {
        delete_node->parent->right = delete_node->left;
    }

    delete_node->left->parent = delete_node->parent;
}

void SelfBalancingBinarySearchTree::delete_node_with_child_right(Node* delete_node) {
    if(delete_node->parent->left != nullptr && delete_node->parent->left->data == delete_node->data) {
        delete_node->parent->left = delete_node->right;
    } else if(delete_node->right != nullptr && delete_node->parent->right->data == delete_node->data) {
        delete_node->parent->right = delete_node->right;
    }

    delete_node->right->parent = delete_node->parent;
}

void SelfBalancingBinarySearchTree::delete_node_with_two_children(Node* delete_node) {
    Node* replace_node = this->find_max_in_subtree(delete_node->right);
    this->delete_node_with_data(replace_node->data);

    if(delete_node->parent->left != nullptr && delete_node->parent->left->data == delete_node->data) {
        delete_node->parent->left = replace_node;
    } else if(delete_node->parent->right != nullptr && delete_node->parent->right->data == delete_node->data) {
        delete_node->parent->right = replace_node;
    }

    replace_node->left = delete_node->left;
    replace_node->right = delete_node->right;

    if(delete_node->left != nullptr) {
        delete_node->left->parent = replace_node;
    }

    if(delete_node->right != nullptr) {
        delete_node->right->parent = replace_node;
    }
}

Node* SelfBalancingBinarySearchTree::delete_node_with_data(int data) {
    if(this->root->data == data) {
        return this->delete_root_node();
    }

    Node* delete_node = this->search(data);

    if(delete_node->left == nullptr && delete_node->right == nullptr) {
        this->delete_leaf_node(delete_node);
    } else if(delete_node->left != nullptr && delete_node->right == nullptr) {
        this->delete_node_with_child_left(delete_node);
    } else if(delete_node->left == nullptr && delete_node->right != nullptr) {
        this->delete_node_with_child_right(delete_node);
    } else if(delete_node->left != nullptr && delete_node->right != nullptr) {
        this->delete_node_with_two_children(delete_node);
    }

    this->size -= 1;
    return delete_node;
}

Node* SelfBalancingBinarySearchTree::search(int data) {
    Node* current_node = this->root;

    while(current_node != nullptr) {
        if(data < current_node->data) {
            current_node = current_node->left;
        } else if (data > current_node->data) {
            current_node = current_node->right;
        } else if(data == current_node->data) {
            return current_node;
        }
    }

    cout << "We couldn't find any node with the data property of " << data << " inside the binary search tree" << endl;
    return nullptr;
}

int SelfBalancingBinarySearchTree::get_height_in_subtree(Node* subtree_root_node) {
    if(subtree_root_node == nullptr) {
        return 0;
    }

    int left_subtree_height = this->get_height_in_subtree(subtree_root_node->left);
    int right_subtree_height = this->get_height_in_subtree(subtree_root_node->right);

    return max(left_subtree_height, right_subtree_height) + 1;
}

Node* SelfBalancingBinarySearchTree::find_max_in_subtree(Node* subtree_root_node) {
    while (subtree_root_node->right != nullptr) {
        subtree_root_node = subtree_root_node->right;
    }

    return subtree_root_node;
}

Node* SelfBalancingBinarySearchTree::find_min_in_subtree(Node* subtree_root_node) {
    while (subtree_root_node->left != nullptr) {
        subtree_root_node = subtree_root_node->left;
    }

    return subtree_root_node;
}

void SelfBalancingBinarySearchTree::insert(int data) {
    /*left for specific implementation (e.g. AVL tree, Red/Black tree)*/
}

void SelfBalancingBinarySearchTree::print_preorder(Node* node) {
    if(node == nullptr) {
        return;
    }

    cout << node->data << " - ";
    this->print_preorder(node->left);
    this->print_preorder(node->right);
}

void SelfBalancingBinarySearchTree::print_inorder(Node* node) {
    if(node == nullptr) {
        return;
    }

    this->print_inorder(node->left);
    cout << node->data << "-";
    this->print_inorder(node->right);
}

void SelfBalancingBinarySearchTree::print_postorder(Node* node) {
    if(node == nullptr) {
        return;
    }

    this->print_postorder(node->left);
    this->print_postorder(node->right);
    cout << node->data << "-";
}

int main() {
    return 1;
}