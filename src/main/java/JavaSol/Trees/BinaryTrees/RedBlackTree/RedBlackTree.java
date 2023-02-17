package JavaSol.Trees.BinaryTrees.RedBlackTree;

public class RedBlackTree {
    /*
        1. Each node is either red or black.
        2. (The root is black.)
        3. All NIL leaves are black.
        4. A red node must not have red children.
        5. All paths from a node to the leaves below contain the same number of black nodes.
    */
    protected Node root;

    static final boolean RED = false;
    static final boolean BLACK = true;

    public void preorder(Node node) {
        if (node == null) {
            return;
        }

        System.out.println(node.data);
        this.preorder(node.left);
        this.preorder(node.right);
    }

    public void inorder(Node node) {
        if (node == null) {
            return;
        }

        this.inorder(node.left);
        System.out.println(node.data);
        this.inorder(node.right);
    }

    public void postorder(Node node) {
        if (node == null) {
            return;
        }

        this.postorder(node.left);
        this.postorder(node.right);
        System.out.println(node.data);
    }

    private void rotateRight(Node node) {
        Node parent = node.parent;
        Node leftChild = node.left;

        node.left = leftChild.right;

        if (leftChild.right != null) {
            leftChild.right.parent = node;
        }

        leftChild.right = node;
        node.parent = leftChild;

        replaceParentsChild(parent, node, leftChild);
    }

    private void rotateLeft(Node node) {
        Node parent = node.parent;
        Node rightChild = node.right;

        node.right = rightChild.left;

        if (rightChild.left != null) {
            rightChild.left.parent = node;
        }

        rightChild.left = node;
        node.parent = rightChild;

        replaceParentsChild(parent, node, rightChild);
    }

    public Node search(int data) {
        if (this.root == null) {
            return null;
        }

        Node current = this.root;

        while (current != null) {
            if (data < current.data) {
                current = current.left;
            } else if (data > current.data) {
                current = current.right;
            } else {
                return current;
            }
        }

        return null;
    }

    private void replaceParentsChild(Node parent, Node oldChild, Node newChild) {
        if (parent == null) {
            this.root = newChild;
        } else if (parent.left == oldChild) {
            parent.left = newChild;
        } else if (parent.right == oldChild) {
            parent.right = newChild;
        } else {
            throw new IllegalStateException("Node is not a child of its parent");
        }

        if (newChild != null) {
            newChild.parent = parent;
        }
    }

    public void insertNode(int key) {
        Node node = root;
        Node parent = null;

        // Traverse the tree to the left or right depending on the key
        while (node != null) {
            parent = node;

            if (key < node.data) {
                node = node.left;
            } else if (key > node.data) {
                node = node.right;
            } else {
                throw new IllegalArgumentException("BST already contains a node with the given key");
            }
        }

        // Insert new node
        Node newNode = new Node(key);
        newNode.color = RED;
        if (parent == null) {
            root = newNode;
        } else if (key < parent.data) {
            parent.left = newNode;
        } else {
            parent.right = newNode;
        }

        newNode.parent = parent;

        fixRedBlackPropertiesAfterInsert(newNode);
    }

    private Node getUncle(Node parent) {
        Node grandparent = parent.parent;

        if (grandparent.left == parent) {
            return grandparent.right;
        } else if (grandparent.right == parent) {
            return grandparent.left;
        } else {
            throw new IllegalArgumentException("The given parent is not a child of its grandparent");
        }
    }

    private void fixRedBlackPropertiesAfterInsert(Node node) {
        Node parent = node.parent;

        // Case 1: Parent is null, we've reached the root, the ned of the recursion
        if (parent == null) {
            return;
        }

        // Parent is black -> there's nothing to do
        if (parent.color == BLACK) {
            return;
        }

        // From here hon, parent is red
        Node grandparent = parent.parent;

        // Case 2: Not having a grandparent means that parent is the root.
        if (grandparent == null) {
            parent.color = BLACK;
            return;
        }

        // Get the uncle (it may be null/nil, in which case its color is BLACK)
        Node uncle = getUncle(parent);

        if (uncle != null && uncle.color == RED) {
            parent.color = BLACK;
            uncle.color = BLACK;
            grandparent.color = RED;

            // Call recursively for grandparent, which is now red.
            // It might be root or have a red parent, in which case we need to fix it.
            fixRedBlackPropertiesAfterInsert(grandparent);
        } else if (parent == grandparent.left) {
            if (node == parent.right) {
                rotateLeft(parent);
                parent = node;
            }

            rotateRight(grandparent);
            parent.color = BLACK;
            grandparent.color = RED;
        } else {
            if (node == parent.left) {
                rotateRight(parent);
                parent = node;
            }

            rotateLeft(grandparent);

            parent.color = BLACK;
            grandparent.color = RED;
        }
    }

    public void deleteNode(int key) {
        Node node = root;

        while (node != null && node.data != key) {
            if (key < node.data) {
                node = node.left;
            } else {
                node = node.right;
            }
        }

        if (node == null) {
            return;
        }

        Node movedUpNode;
        boolean deletedNodeColor;

        // Node has zero or one child
        if (node.left == null || node.right == null) {
            movedUpNode = deleteNodeWithZeroOrOneChild(node);
            deletedNodeColor = node.color;
        } else {
            // Node has two children
            Node inOrderSuccessor = findMinimum(node.right);

            node.data = inOrderSuccessor.data;

            movedUpNode = deleteNodeWithZeroOrOneChild(inOrderSuccessor);
            deletedNodeColor = inOrderSuccessor.color;
        }

        if(deletedNodeColor == BLACK) {
            fixRedBlackPropertiesAfterInsert(movedUpNode);

            // Remove the temporary NIL NODE
            if (movedUpNode.getClass() == NilNode.class) {
                replaceParentsChild(movedUpNode.parent, movedUpNode, null);
            }
        }
    }

    private void fixRedBlackPropertiesAfterDelete(Node node) {
        // Case 1. Examined node is root, end of recursion
        if(node == root) {
            return;
        }

        Node sibling = getSibling(node);

        // Case 2: Red sibling
        if (sibling.color == RED) {
            handleRedSibling(node, sibling);
            sibling = getSibling(node); // Get new sibling for fall-through to case 3-6
        }

        // Case 3+4: Black sibling with two black children
        if (isBlack(sibling.left) && isBlack(sibling.right)) {
            sibling.color = RED;

            // Case 3: Black sibling with two black children + red parent
            if (node.parent.color == RED) {
                node.parent.color = BLACK;
            }

            // Case 4: Black sibling with two black children + black parent
            else {
                fixRedBlackPropertiesAfterDelete(node.parent);
            }
        } else {
            // Case 5+6: Black sibling with at least one red child
            handleBlackSiblingWithAtLeastOneRedChild(node, sibling);
        }
    }

    private Node getSibling(Node node) {
        Node parent = node.parent;

        if (node == parent.left) {
            return parent.right;
        } else if (node == parent.right) {
            return parent.left;
        } else {
            throw new IllegalStateException("Parent is not a child of its grandparent.");
        }
    }

    private boolean isBlack(Node node) {
        return node == null || node.color == BLACK;
    }

    private void handleRedSibling(Node node, Node sibling) {
        sibling.color = BLACK;
        node.parent.color = RED;

        if (node == node.parent.left) {
            rotateLeft(node.parent);
        } else {
            rotateRight(node.parent);
        }
    }

    private void handleBlackSiblingWithAtLeastOneRedChild(Node node, Node sibling) {
        boolean nodeIsLeftChild = node == node.parent.left;

        if (nodeIsLeftChild && isBlack(sibling.right)) {
            sibling.left.color = BLACK;
            sibling.color = RED;
            rotateRight(sibling);
            sibling = node.parent.right;
        } else if (!nodeIsLeftChild && isBlack(sibling.left)) {
            sibling.right.color = BLACK;
            sibling.color = RED;
            rotateLeft(sibling);
            sibling = node.parent.left;
        }

        sibling.color = node.parent.color;
        node.parent.color = BLACK;
        if (nodeIsLeftChild) {
            sibling.right.color = BLACK;
            rotateLeft(node.parent);
        } else {
            sibling.left.color = BLACK;
            rotateRight(node.parent);
        }
    }

    private Node deleteNodeWithZeroOrOneChild(Node node) {
        if (node.left != null) {
            replaceParentsChild(node.parent, node, node.left);
            return node.left;
        } else if (node.right != null) {
            replaceParentsChild(node.parent, node, node.right);
            return node.right;
        } else {
            Node newChild = node.color == BLACK ? new NilNode(0) : null;
            replaceParentsChild(node.parent, node, newChild);
            return newChild;
        }
    }

    private Node findMinimum(Node node) {
        while(node.left != null) {
            node = node.left;
        }

        return node;
    }

    public static void main(String[] args) {
        RedBlackTree rbt = new RedBlackTree();

        rbt.insertNode(17);
        rbt.insertNode(9);
        rbt.insertNode(19);
        rbt.insertNode(18);
        rbt.insertNode(75);
        rbt.insertNode(81);

        rbt.preorder(rbt.root);
    }
}
