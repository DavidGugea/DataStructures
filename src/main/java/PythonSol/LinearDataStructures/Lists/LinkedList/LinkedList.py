from typing import Any

class Node:
    def __init__(self, value: Any, next: 'Node' = None) -> None:
        self.value: Any = value
        self.next: 'Node' = next


class LinkedList:
    def __init__(self):
        self.head = None
        self.size = 0

    def __len__(self) -> int:
        return self.size
    
    def append(self, value: Any) -> None:
        if self.head == None:
            self.head = Node(value)
        else:
            curr: Node = self.head
            while curr.next != None:
                curr = curr.next

            new_node: Node = Node(value)
            curr.next = new_node

        self.size += 1

    def delete(self) -> None:
        if self.head == None:
            return

        if self.head.next == None:
            self.head = None
            return

        curr: Node = self.head
        while curr.next.next != None:
            curr = curr.next

        curr.next = None

        self.size -= 1

    def delete_index(self, index: int) -> None:
        if index < 0 or index >= self.size:
            raise Exception("Index out of bounds")

        if self.head == None:
            return

        if index == 0:
            next_node: Node = self.head.next
            del self.head
            self.head = next_node
            self.size -= 1
            return

        counter = 0
        prev: Node = None
        curr: Node = self.head

        while counter != index:
            prev = curr
            curr = curr.next
            counter += 1

        prev.next = curr.next
        del curr
        self.size -= 1

    def search(self, value: Any) -> Node:
        if self.head == None:
            raise Exception("The linked list is empty.")

        curr: Node = self.head
        while curr != None:
            if curr.value == value:
                return curr

            curr = curr.next

        raise Exception("Value not found.")

    def print_list(self) -> None:
        if self.head == None:
            print("Empty list.")
            return

        curr: Node = self.head
        while curr != None:
            print(curr.value, end = " ")
            curr = curr.next

        print()

if __name__ == "__main__":
    ll = LinkedList()

    for i in range(1, 6):
        ll.append(i)

    ll.print_list()
    ll.delete()
    ll.delete()
    ll.delete()
    ll.delete()
    ll.delete()
    ll.delete()
    ll.print_list()