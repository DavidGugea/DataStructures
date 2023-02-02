from typing import List, Any


class Node:
    def __init__(self, capacity: int, next: 'Node' = None) -> None:
        self.capacity: int = capacity
        self.elements: List[Any] = []
        self.next: 'Node' = None

    def __len__(self) -> int:
        return len(self.elements)


class UnrolledLinkedList:
    def __init__(self, node_capacity: int) -> None:
        self.size = 0
        self.node_capacity: int = node_capacity
        self.head: Node = None

    def append(self, value: int) -> None:
        if not self.head:
            self.head = Node(self.node_capacity)
            self.head.elements.append(value)
        else:
            prev: Node = None
            current: Node = self.head

            while current != None:
                if len(current) < self.node_capacity:
                    current.elements.append(value)
                    break
                    
                prev = current
                current = current.next
            else:
                new_node: Node = Node(self.node_capacity)
                new_node.elements.append(value)

                prev.next = new_node


        self.size += 1

    def delete_value(self, value: int, node_index: int) -> None:
        if not self.head:
            raise Exception("The unrolled linked list is empty.")

        if node_index < 0 or node_index >= self.size:
            raise IndexError("The given index is out of bounds.")

        current: Node = self.head
        counter = 0

        while counter != node_index:
            counter += 1
            current = current.next

        # Propagate thrown exception from built-in remove method
        current.elements.remove(value)

        self.size -= 1


    def delete_node(self, node_index: int) -> None:
        if node_index < 0 or node_index >= self.size:
            raise IndexError("The given index is out of bounds.")

        prev: Node = None
        current: Node = self.head
        counter: int = 0

        while counter != node_index:
            counter += 1
            prev = current
            current = current.next

        prev.next = current.next
        del current
        
        self.size -= 1


    def print_list(self) -> None:
        if not self.head:
            print("The unrolled linekd list is empty")
            return

        current: Node = self.head
        while current != None:
            for node_element in current.elements:
                print(node_element, end=' - ')

            print()

            current = current.next


if __name__ == "__main__":
    ll = UnrolledLinkedList(4)

    for i in range(1, 19):
        ll.append(i)