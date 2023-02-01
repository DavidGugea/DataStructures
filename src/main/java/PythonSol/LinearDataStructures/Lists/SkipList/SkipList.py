"""Implementing a self-organizing integer skip list"""


import random
from typing import Tuple


class Node:
    def __init__(self, value: int, next: 'Node' = None) -> None:
        self.value: int = value
        self.next: 'Node' = next


class SkipListLinkedList:
    def __init__(self) -> None:
        self.size: int = 0
        self.head: Node = None

    def append(self, value: int) -> None:
        if not self.head:
            self.head = Node(value)
        else:
            previous_node: Node = None
            current_node: Node = self.head
            new_node: Node = Node(value)


            while current_node != None:
                if current_node.value == value:
                    print("Value is already in the linked list. Duplicates are not allowed")
                    return

                if current_node.value > value:
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


    def search(self, value: int) -> Tuple[Node, Node]:
        """Returns (previous_node, current_node) where current_node is the node with the value the user is searching for."""

        if not self.head:
            return None

        previous_node: Node = None
        current_node: Node = self.head

        while current_node != None:
            if current_node.value == value:
                return (previous_node, current_node)


            previous_node = current_node
            current_node = current_node.next

        raise Exception("Couldn't find a node with the given value inside the linked list.")


    def delete(self, value: int) -> Node:
        if self.head.value == value:
            self.head = self.head.next
        else:
            previous_node, current_node = self.search(value)
            previous_node.next = current_node.next
            del current_node

        self.size -= 1


    def print_list(self) -> None:
        if not self.head:
            print("The linked list is empty")
            return

        current_node: Node = self.head
        while current_node != None:
            print(current_node.value, end = " ")
            current_node = current_node.next

        print()



class SkipList:
    def __init__(self, number_of_levels: int = 3):
        if number_of_levels < 2:
            raise Exception("You need to have at least 2 levels.")

        self.number_of_levels: int = number_of_levels
        self.levels: dict[int, SkipListLinkedList] = {i: SkipListLinkedList() for i in range(0, number_of_levels+1)}

    def append(self, value: int) -> None:
        self.levels[0].append(value)

        for i in range(1, self.number_of_levels+1):
            random_number: int = random.randint(1, 2)

            if random_number == 1:
                break
            else:
                self.levels[i].append(value)

    def search(self, value: int) -> None:
        for i in range(self.number_of_levels, -1, -1):
            try:
                _, search_node = self.levels[i].search(value)

                return search_node
            except Exception:
                continue

    def delete(self, value: int) -> None:
        for i in range(self.number_of_levels, -1, -1):
            try:
                self.levels[i].delete(value)
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
    sl = SkipList(5)

    for i in range(1, 18):
        sl.append(i)

    sl.print_skip_list()
    sl.delete(1)
    print('----------------------------')
    sl.print_skip_list()