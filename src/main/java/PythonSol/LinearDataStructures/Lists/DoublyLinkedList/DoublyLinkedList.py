from typing import Any


class Node:
    def __init__(self, value: Any, prev: 'Node' = None, next: 'Node' = None) -> None:
        self.value: Any = value
        self.prev: 'Node' = prev
        self.next: 'Node' = next

class DoublyLinkedList():
    def __init__(self) -> None:
        self.size:int = 0

        self.head: Node = None
        self.last: Node = None

    def __len__(self) -> int:
        return self.size

    def append(self, value: Any) -> None:
        if self.head == None and self.last == None:
            self.head = self.last = Node(value)
        else:
            if self.size == 1:
                self.last = Node(value)

                self.last.prev = self.head
                self.head.next = self.last
            else:
                new_node: Node = Node(value)

                new_node.prev = self.last

                self.last.next = new_node
                self.last = new_node

        self.size += 1

    def delete(self) -> None:
        if self.head == None:
            raise Exception("The doubly linked list is empty")
        elif self.size == 1:
            self.head = self.last = None
        elif self.size == 2:
            self.head.next = None
            self.last = self.head
        else:
            prev: Node = self.last.prev
            prev.next = None
            self.last = prev

        self.size -= 1

    def delete_index(self, index: int) -> None:
        if index < 0 or index >= self.size:
            raise IndexError("The given index {0} is out of bounds or the doubly linked list is empty (size: {1})".format(index, self.size))

        if index == 0:
            if self.size == 1:
                self.head = self.last = None
            elif self.size == 2:
                self.last.prev = None
                self.head = self.last
            else:
                self.head.next.prev = None
                self.head = self.head.next
        elif index == self.size - 1:
            if self.size == 2:
                self.head.next = None
                self.last = self.head
            else:
                self.last.prev.next = None
                self.last = self.last.prev
        else:
            counter:int = 0
            previous_node: Node = None
            current_node: Node = self.head

            while counter != index:
                previous_node = current_node
                current_node = current_node.next

                counter += 1

            current_node.next.prev = previous_node
            previous_node.next = current_node.next

        self.size -= 1

    def search(self, value: Any) -> Node:
        if self.head == None:
            raise Exception("The doubly linked list is empty.")

        current: Node = self.head
        while current != None:
            if current.value == value:
                return current

            current = current.next 

        raise Exception("No node found in the doubly linked list that has the given value : {0}".format(value))

    def print_list(self) -> None:
        if self.head == None:
            print("The doubly linked list is empty.")
            return

        current: Node = self.head
        while current != None:
            print(current.value, end = " ")
            current = current.next

        print()



if __name__ == "__main__":
    dll = DoublyLinkedList()
    
    for i in range(1, 6):
        dll.append(i)

    for i in range(1, 6):
        print(dll.search(i).value)