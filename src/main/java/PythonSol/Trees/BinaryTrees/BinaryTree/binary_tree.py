class Node:
    def __init__(self, value: int, left: 'Node' = None, right: 'Node' = None) -> None:
        self.left: 'Node' = left
        self.right: 'Node' = right

        self.value = value


    def traversePreorder(self) -> None:
        print(self.value, end = " - ")

        if self.left:
            self.left.traversePreorder()

        if self.right:
            self.right.traversePreorder()


    def traverseInorder(self) -> None:
        if self.left:
            self.left.traverseInorder()
        
        print(self.value, end = " - ")

        if self.right:
            self.right.traverseInorder()


    def traversePostorder(self) -> None:
        if self.left:
            self.left.traversePostorder()
        
        if self.right:
            self.right.traversePostorder()

        print(self.value, end = " - ")


if __name__ == "__main__":
    root = Node(1)
    root.left = Node(2)
    root.right = Node(3)
    root.left.left = Node(4)

    print("Preorder traversal: ", end = "")
    root.traversePreorder()
    print()

    print("Inorder traversal: ", end = "")
    root.traverseInorder()
    print()

    print("Postorder traversal: ", end = "")
    root.traversePostorder()
    print()