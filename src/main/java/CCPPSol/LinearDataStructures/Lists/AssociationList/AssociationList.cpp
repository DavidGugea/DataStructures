#include <iostream>

using namespace std;

class Node {
public:
    int key;
    int value;
    Node* next;

    Node(int key, int value) {
        this->key = key;
        this->value = value;
    }
};

class AssociationList {
private:
    int size = 0;
public:
    Node* head;

    int get_size() {
        return this->size;
    }

    void append(int kye, int value) {
        if(this->head == NULL) {
            this->head = new Node(key, value);
        } else {
            Node* current = this->head;

            while(current->next != NULL) {
                current = current->next;
            }
            
            current->next = new Node(key, value);
        }

        this->size += 1;
    }

    void delete_last() {
        if (this->head == NULL) {
            cout << "The linked list is empty." << endl;
            return;
        }

        if (this->head->next == NULL) {
            this->head = NULL;
            return;
        }

        Node* current = this->head;
        while (current->next->next != NULL) {
            current = current->next;
        }

        current->next = NULL;
        this->size -= 1;
    }

    void delete_index(int index) {
        if (index < 0 || index >= this->size) {
            return;
        }

        if(index == 0) {
            Node* current_head = this->head;
            Node* next = this->head->next;

            this->head = next;
            this->size -= 1;
            return;
        }

        int counter = 0;
        Node* previous = NULL;
        Node* current = this->head;

        while (counter != index) {
            previous = current;
            current = current->next;
            counter += 1;
        }

        previous->next = current->next;
        this->size -= 1;
    }

    int search(int key) {
        if (this->head == NULL) {
            cout << "The linked list is empty." << endl;
            return NULL;
        }

        Node* current = this->head;

        while (current != NULL) {
            if(current->key == key) {
                return current->value;
            }

            current = current->next;
        }


        cout << "No node found that contains the given value inside of the linked list." << endl;
        return NULL;
    }

    void print_list() {
        if(this->head == NULL) {
            cout << "The linked list is empty." << endl;
            return;
        }

        Node* current = this->head;
        while (current != NULL) {
            cout << current->value << " ";
            current = current->next;
        }

        cout << " " << endl;
    }
};