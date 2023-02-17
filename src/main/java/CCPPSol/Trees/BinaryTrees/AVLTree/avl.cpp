#include <iostream>

using namespace std;


class Node {
public:
    int key;
    int height = 1;

    Node* left;
    Node* right;

    Node(int key) {
        this->key = key;
    }

};

int max(int a, int b) {
    return a > b ? a : b;
}

int getNodeHeight(Node* node) {
    if(node == nullptr)
        return 0;

    return node->height;
}

int balanceFactor(Node* node) {
    return getNodeHeight(node->left) - getNodeHeight(node->right);
}

Node* getMinValueNode(Node* subtreeRootNode) {
    if (subtreeRootNode == nullptr) {
        return nullptr;
    }

    while (subtreeRootNode->left != nullptr)
        subtreeRootNode = subtreeRootNode->left;

    return subtreeRootNode;
}

class AVL {
public:
    Node* root;

    Node* search(int key);

    Node* insert(Node* node, int key); 
    Node* deleteNode(Node* node, int key);

    Node* leftRotation(Node* subtreeRootNode);
    Node* rightRotation(Node* subtreeRootNode);

    void preorder(Node* root);
    void inorder(Node* root);
    void postorder(Node* root);
};

Node* AVL::search(int key) {
    if (this->root == nullptr) {
        return nullptr;
    }

    Node* current = this->root;

    while (current != nullptr) {
        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        } else {
            return current;
        }
    }

    return current;
}

Node* AVL::rightRotation(Node* subtreeRootNode) {
    Node* y = subtreeRootNode->left;
    Node* T3 = y->right;

    y->right = subtreeRootNode;
    subtreeRootNode->left = T3;

    y->height = max(getNodeHeight(y->left), getNodeHeight(y->right)) + 1;
    subtreeRootNode->height = max(getNodeHeight(subtreeRootNode->left), getNodeHeight(subtreeRootNode->right)) + 1;

    return y;
}

Node* AVL::leftRotation(Node* subtreeRootNode) {
    Node* y = subtreeRootNode->right;
    Node* T3 = y->left;

    y->left = subtreeRootNode;
    subtreeRootNode->right = T3;

    y->height = max(getNodeHeight(y->left), getNodeHeight(y->right)) + 1;
    subtreeRootNode->height = max(getNodeHeight(subtreeRootNode->left), getNodeHeight(subtreeRootNode->right)) + 1;

    return y;
}

void AVL::preorder(Node* root) {
    if (root == nullptr)
        return;

    cout << root->key << " - ";
    this->preorder(root->left);
    this->preorder(root->right);
}

void AVL::inorder(Node* root) {
    if (root == nullptr)
        return;

    this->inorder(root->left);
    cout << root->key << " - ";
    this->inorder(root->right);
}

void AVL::postorder(Node* root) {
    if (root == nullptr)
        return;

    this->postorder(root->left);
    this->postorder(root->right);
    cout << root->key << " - ";
}

Node* AVL::insert(Node* node, int key) {
    if (this->root == nullptr) {
        this->root = new Node(key);
        return this->root;
    }
    
    if (node == nullptr) {
        return new Node(key);
    }

    if(key < node->key) {
        node->left = this->insert(node->left, key);
    } else if (key > node->key) {
        node->right = this->insert(node->right, key);
    } else {
        return node;
    }

    node->height = max(getNodeHeight(node->left), getNodeHeight(node->right)) + 1;

    int balance = balanceFactor(node);

    // LL CASE
    if (balance > 1 && key < node->left->key) {
        if(node->key == this->root->key) {
            this->root = rightRotation(node);
            return this->root;
        }

        return rightRotation(node);
    }

    // LR CASE
    if (balance > 1 && key > node->left->key) {
        if (node->key == this->root->key) {
            this->root->left = leftRotation(this->root->left);
            this->root = rightRotation(node);
            return this->root;
        }

        node->left = leftRotation(node->left);
        return rightRotation(node);
    }

    // RR CASE
    if (balance < -1 && key > node->right->key) {
        if (node->key == this->root->key) {
            this->root = leftRotation(this->root);
            return this->root;
        }

        return leftRotation(node);
    }

    // RL CASE
    if (balance < -1 && key < node->right->key) {
        if (node->key == this->root->key) {
            this->root->right = rightRotation(this->root->right);
            this->root = leftRotation(this->root);
            return this->root;
        }

        node->right = rightRotation(node->right);
        return leftRotation(node);
    }

    return node;
}

Node* AVL::deleteNode(Node* node, int key) {
    if (node == nullptr) {
        return nullptr;
    }

    // BST DEFAULT NODE DELETION ALGORITHM
    if(key < node->key) {
        node->left = deleteNode(node->left, key);
    } else if (key > node->key) {
        node->right = deleteNode(node->right, key);
    } else {
        if (node->left == nullptr || node->right == nullptr) {
            Node* temp = node->left ? node->left : node->right;

            if (temp == nullptr) {
                // No child case
                /*
                temp = node; // node->left = node;
                *node = NULL;
                */
                node = NULL;
            } else {
                *node = *temp;
            }

            free(temp);
        } else {
            Node* temp = getMinValueNode(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right, temp->key);
        }
    }

    if(node == nullptr) {
        return nullptr;
    }

    node->height = max(getNodeHeight(node->left), getNodeHeight(node->right)) + 1;

    int balance = balanceFactor(node);

    // LL CASE
    if (balance > 1 && key < node->left->key) {
        if(node->key == this->root->key) {
            this->root = rightRotation(node);
            return this->root;
        }

        return rightRotation(node);
    }

    // LR CASE
    if (balance > 1 && key > node->left->key) {
        if (node->key == this->root->key) {
            this->root->left = leftRotation(this->root->left);
            this->root = rightRotation(node);
            return this->root;
        }

        node->left = leftRotation(node->left);
        return rightRotation(node);
    }

    // RR CASE
    if (balance < -1 && key > node->right->key) {
        if (node->key == this->root->key) {
            this->root = leftRotation(this->root);
            return this->root;
        }

        return leftRotation(node);
    }

    // RL CASE
    if (balance < -1 && key < node->right->key) {
        if (node->key == this->root->key) {
            this->root->right = rightRotation(this->root->right);
            this->root = leftRotation(this->root);
            return this->root;
        }

        node->right = rightRotation(node->right);
        return leftRotation(node);
    }

    return node;
}

int main() {
    AVL* avl = new AVL();
    int values[] = {10, 20, 30, 40, 50, 25};

    for (int value : values) {
        avl->insert(avl->root, value);
    }

    avl->deleteNode(avl->root, 20);

    avl->preorder(avl->root);
    cout << "\n";


    return 0;
}