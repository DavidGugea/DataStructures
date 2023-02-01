#include <iostream>

using namespace std;


class Node {
public:
    int value;
    Node* next;
    Node* prev;

    Node(int value) {
        this->value = value;
    }

    Node(int value, Node* next) {
        this->value = value;
        this->next = next;
    }

    Node(int value, Node* next, Node* prev) {
        this->value = value;
        this->next = next;
        this->prev = prev;
    }
};


class DoublyLinkedList {
private:
    int size = 0;
public:
    Node* head;
    Node* last;

    int getSize() {
        return this->size;
    }

    void append(int value) {
        if(this->head == nullptr) {
            this->head = this->last = new Node(value);
        } else if (this->size == 1) {
            this->last = new Node(value);
            
            this->last->prev = this->head;
            this->head->next = this->last;
        } else {
            Node* new_node = new Node(value);

            new_node->prev = this->last;
            this->last->next = new_node;
            this->last = new_node;
        }

        this->size += 1;
    }

    void delete_last() {
        if(this->size == 1) {
            this->head = nullptr;
            this->last = nullptr;
        } else if (this->size == 2) {
            this->head->next = nullptr;
            this->last = this->head;
        } else {
            Node* prev = this->last->prev;
            prev->next = nullptr;
            this->last = prev;
        }

        this->size -= 1;
    }

    void delete_index(int index) {
        if (index == 0) {
            if (this->size == 1) {
                this->head = nullptr;
                this->last = nullptr;
            } else if (this->size == 2) {
                this->last->prev = nullptr;
                this->head = this->last;
            } else {
                this->head->next->prev = nullptr;
                this->head = this->head->next;
            }
        } else if (index == this->size - 1) {
            if (this->size == 2) {
                this->head->next = nullptr;
                this->last = this->head;
            } else {
                this->last->prev->next = nullptr;
                this->last = this->last->prev;
            }
        } else {
            int counter = 0;
            Node* previous_node = nullptr;
            Node* current_node = this->head;

            while(counter != index) {
                previous_node = current_node;
                current_node = current_node->next;
                counter += 1;
            }

            current_node->next->prev = previous_node;
            previous_node->next = current_node->next;
        }

        this->size -= 1;
    }

    Node* search(int value) {
        if (this->head == nullptr) {
            cout << "The doubly linked list is empty." << endl;
            return NULL;
        }

        Node* current = this->head;
        while (current != NULL) {
            if (current->value == value) {
                return current;
            }

            current = current->next;
        }

        cout << "No node with the value " << value << " could be found in the doubly linked list" << endl;
        return NULL;
    }

    void print_list() {
        if(this->head == nullptr) {
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


int main() {
    DoublyLinkedList* dll = new DoublyLinkedList();

    for(int i = 1; i <= 5; ++i) {
        dll->append(i);
    }

    for(int i = 1; i <= 5; ++i) {
        cout << dll->search(i)->value << endl;
    }

    return 0;
}