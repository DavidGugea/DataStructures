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

class BinarySearchTree {
public:
    int size = 0;
    Node* root;

    void insert(int data);
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

Node* BinarySearchTree::delete_root_node() {
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

void BinarySearchTree::delete_leaf_node(Node* leaf_node) {
    if(leaf_node->parent->left != nullptr && leaf_node->parent->left->data == leaf_node->data) {
        leaf_node->parent->left = nullptr;
    } else if (leaf_node->parent->right != nullptr && leaf_node->parent->right->data == leaf_node->data) {
        leaf_node->parent->right = nullptr;
    }
}

void BinarySearchTree::delete_node_with_child_left(Node* delete_node) {
    if(delete_node->parent->left != nullptr && delete_node->parent->left->data == delete_node->data) {
        delete_node->parent->left = delete_node->left;
    } else if(delete_node->parent->right != nullptr && delete_node->parent->right->data == delete_node->data) {
        delete_node->parent->right = delete_node->left;
    }

    delete_node->left->parent = delete_node->parent;
}

void BinarySearchTree::delete_node_with_child_right(Node* delete_node) {
    if(delete_node->parent->left != nullptr && delete_node->parent->left->data == delete_node->data) {
        delete_node->parent->left = delete_node->right;
    } else if(delete_node->right != nullptr && delete_node->parent->right->data == delete_node->data) {
        delete_node->parent->right = delete_node->right;
    }

    delete_node->right->parent = delete_node->parent;
}

void BinarySearchTree::delete_node_with_two_children(Node* delete_node) {
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

Node* BinarySearchTree::delete_node_with_data(int data) {
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

Node* BinarySearchTree::search(int data) {
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

int BinarySearchTree::get_height_in_subtree(Node* subtree_root_node) {
    if(subtree_root_node == nullptr) {
        return 0;
    }

    int left_subtree_height = this->get_height_in_subtree(subtree_root_node->left);
    int right_subtree_height = this->get_height_in_subtree(subtree_root_node->right);

    return max(left_subtree_height, right_subtree_height) + 1;
}

Node* BinarySearchTree::find_max_in_subtree(Node* subtree_root_node) {
    while (subtree_root_node->right != nullptr) {
        subtree_root_node = subtree_root_node->right;
    }

    return subtree_root_node;
}

Node* BinarySearchTree::find_min_in_subtree(Node* subtree_root_node) {
    while (subtree_root_node->left != nullptr) {
        subtree_root_node = subtree_root_node->left;
    }

    return subtree_root_node;
}

void BinarySearchTree::insert(int data) {
    if(this->root == nullptr) {
        this->root = new Node(data);
        return;
    }

    Node* backtracking_node = nullptr;
    Node* current_node = this->root;

    while(current_node != nullptr) {
        backtracking_node = current_node;

        if(data < current_node->data) {
            current_node = current_node->left;
        } else if (data > current_node->data) {
            current_node = current_node->right;
        }
    }

    Node* new_node = new Node(data);

    if(data < backtracking_node->data) {
        backtracking_node->left = new_node;
    } else if(data > backtracking_node->data) {
        backtracking_node->right = new_node;
    }

    new_node->parent = backtracking_node;
    this->size += 1;
}

void BinarySearchTree::print_preorder(Node* node) {
    if(node == nullptr) {
        return;
    }

    cout << node->data << " - ";
    this->print_preorder(node->left);
    this->print_preorder(node->right);
}

void BinarySearchTree::print_inorder(Node* node) {
    if(node == nullptr) {
        return;
    }

    this->print_inorder(node->left);
    cout << node->data << "-";
    this->print_inorder(node->right);
}

void BinarySearchTree::print_postorder(Node* node) {
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