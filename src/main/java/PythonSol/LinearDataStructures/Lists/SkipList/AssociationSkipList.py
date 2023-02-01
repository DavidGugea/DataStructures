"""Implementing a self-organizing integer-key-based association skip list"""


import random
from typing import Any, Tuple

class Container:
    def __init__(self, value: int) -> None:
        self.value = value
        self.second_value = self.value + 7


class Node:
    def __init__(self, key: int, value: Any, next: 'Node' = None) -> None:
        self.key: int = key
        self.value: Any = value
        self.next: 'Node' = next


class AssociationSkipListLinkedList:
    def __init__(self) -> None:
        self.size: int = 0
        self.head: Node = None

    def append(self, key: int, value: Any) -> None:
        if not self.head:
            self.head = Node(key, value)
        else:
            previous_node: Node = None
            current_node: Node = self.head
            new_node: Node = Node(key, value)


            while current_node != None:
                if current_node.key == key:
                    print("Value is already in the linked list. Duplicates are not allowed")
                    return

                if current_node.key > key:
                    if previous_node == None:
                        new_node.next = self.head
                        self.head = new_node
                    else:
                        previous_node.next = new_node
                        new_node.next = current_node

                    break

                previous_node = current_node
                current_node = current_node.next
            else:
                previous_node.next = new_node


        self.size += 1


    def search(self, key: int) -> Tuple[Node, Node]:
        """Returns (previous_node, current_node) where current_node is the node with the value the user is searching for."""

        if not self.head:
            return None

        previous_node: Node = None
        current_node: Node = self.head

        while current_node != None:
            if current_node.key == key:
                return (previous_node, current_node)


            previous_node = current_node
            current_node = current_node.next

        raise Exception("Couldn't find a node with the given value inside the linked list.")


    def delete(self, key: int) -> Node:
        if self.head.key == key:
            self.head = self.head.next
        else:
            previous_node, current_node = self.search(key)
            previous_node.next = current_node.next
            del current_node

        self.size -= 1


    def print_list(self) -> None:
        if not self.head:
            print("The linked list is empty")
            return

        current_node: Node = self.head
        while current_node != None:
            print("({0} < - > {1})".format(current_node.key, current_node.value), end = " ")
            current_node = current_node.next

        print()



class AssociationSkipList:
    def __init__(self, number_of_levels: int = 3):
        if number_of_levels < 2:
            raise Exception("You need to have at least 2 levels.")

        self.number_of_levels: int = number_of_levels
        self.levels: dict[int, AssociationSkipList] = {i: AssociationSkipListLinkedList() for i in range(0, number_of_levels+1)}

    def append(self, key: int, value: Any) -> None:
        self.levels[0].append(key, value)

        for i in range(1, self.number_of_levels+1):
            random_number: int = random.randint(1, 2)

            if random_number == 1:
                break
            else:
                self.levels[i].append(key, value)

    def search(self, key: int) -> None:
        for i in range(self.number_of_levels, -1, -1):
            try:
                _, search_node = self.levels[i].search(key)

                return search_node
            except Exception:
                continue

    def delete(self, key: int) -> None:
        for i in range(self.number_of_levels, -1, -1):
            try:
                self.levels[i].delete(key)
            except Exception:
                continue

    def print_skip_list(self) -> None:
        if not self.levels[0].head:
            print("The skip list is empty.")
            return

        for key in range(self.number_of_levels, -1, -1):
            print("Level {0}".format(key), end = " -- > ")
            self.levels[key].print_list()


if __name__ == "__main__":
    sl = AssociationSkipList(5)

    for i in range(1, 18):
        sl.append(i, Container(i))

    sl.print_skip_list()