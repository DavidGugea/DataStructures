#include <stdio.h>


const char* messages[] = {
    "Message 1",
    "Message 2",
    "Message 3",
    "Message 4",
    "Message 4",
    "Message 5",
}

const int NUM_MESSAGES = (sizeof(messages)/sizeof(char*));

void print_party_size_info(size_t people) {
    if (people > NUM_MESSAGES - 1) {
        printf("Wrong");
    } else {
        printf("%s\n", messages[people]);
    }
}


int main() {
    print_party_size_info(0);
    print_party_size_info(1);
    print_party_size_info(2);
    print_party_size_info(3);
    print_party_size_info(4);
    print_party_size_info(5);
    print_party_size_info(6);
    print_party_size_info(7);
}