#include <iostream>

using namespace std;


class CircularBuffer {
public:
    int size;

    int insert_pointer = 0;
    int delete_pointer = 0;
    int cycles = 0;

    int internal_array[5];

    bool index_in_bounds(int index) {
        return index >= 0 && index <= 4;
    }

    void append(int value) {
        if (value == 0) {
            return;
        }

        if (!this->index_in_bounds(this->insert_pointer)) {
            this->insert_pointer = 0;
            this->cycles += 1;
        }

        this->internal_array[this->insert_pointer] = value;
        this->insert_pointer++;
    }

    void del() {
        if (!this->index_in_bounds(this->delete_pointer)) {
            this->delete_pointer = 0;
        }

        if (this->cycles > 0 && this->delete_pointer<this->insert_pointer) {
            this->delete_pointer = this->insert_pointer;
        }

        this->internal_array[this->delete_pointer] = 0;
        this->delete_pointer++;
    }

    void print_array() {
        for(int i = 0 ; i < 5; ++i) {
            cout << this->internal_array[i] << " - ";
        }

        cout << " " << endl;
    }
};


int main() {
    CircularBuffer* cb = new CircularBuffer();

    cb->print_array();

    for(int i = 1 ; i <= 5 ; ++i) {
        cb->append(i);
    }

    (*cb).print_array();

    return 1;
}