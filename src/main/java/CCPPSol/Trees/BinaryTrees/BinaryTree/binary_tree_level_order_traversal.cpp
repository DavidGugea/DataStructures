#include <iostream>
#include <queue>

using namespace std;


struct Node {
    char data;
    Node* left;
    Node* right;
};


void levelOrder(Node *root) {
    if (root == NULL) return;

    queue<Node*> Q;
    Q.push(root);

    // while there is at least one discovered node
    while(!Q.empty()) {
        Node* current = Q.front();
        cout << current-> data << " ";

        if (current->left != NULL) Q.push(current->left);
        if (current->right != NULL) Q.push(current->right);

        Q.pop(); // removing the element at front
    }
}


int main() {

    return 1;
}