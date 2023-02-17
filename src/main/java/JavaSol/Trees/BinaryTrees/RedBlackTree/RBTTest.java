package JavaSol.Trees.BinaryTrees.RedBlackTree;

import org.jetbrains.annotations.NotNull;

public class RBTTest {
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
        if (this.root == null) {
            fixRBT(new Node(key));
            return;
        }

        Node parent = null;
        Node current = this.root;

        while (current != null) {
            parent = current;

            if (key < current.data) {
                current = current.left;
            } else if (key > current.data) {
                current = current.right;
            } else {
                throw new IllegalArgumentException("The given data already exists in the node");
            }
        }

        Node newNode = new Node(key);
        newNode.color = RED;
        newNode.parent = parent;

        if (key < parent.data) {
            parent.left = newNode;
        } else {
            parent.right = newNode;
        }

        fixRBT(newNode);
    }

    private void fixRBT(Node node) {
        Node parent = node.parent;
        Node grandparent = null;
        Node uncle = null;

        if (parent != null) {
            grandparent = parent.parent;
        }

        if (grandparent != null) {
            uncle = getUncle(parent);
        }

        // Case 1. New node is the root
        if (this.root == null) {
            this.root = node;
            return;
        }

        // Case 2. Parent node is root node
        if (grandparent == null) {
            this.root.color = BLACK;
            node.color = RED;
            return;
        }

        // Case 3. Parent and uncle nodes are red

        if (parent.color == RED && uncle.color == RED) {
            parent.color = BLACK;
            uncle.color = BLACK;
            grandparent.color = RED;
            node.color = RED;

            fixRBT(grandparent);
            return;
        }

        // Case 4. Parent node is red, Uncle node is black (or null) and the newNode is on the left of the parent.
        if (parent.color == RED && (uncle == null || uncle.color == BLACK) && parent.left == node) {
            rotateRight(parent);
            rotateLeft(grandparent);

            node.color = BLACK;
            grandparent.color = RED;
            parent.color = RED;
        }

        // Case 5. Parent node is red, Uncle node is black (or null) and the newNode is on the right of the parent.
        if (parent.color == RED && (uncle == null || uncle.color == BLACK) && parent.right == node) {
            rotateLeft(grandparent);


            node.color = BLACK;
            grandparent.color = RED;
            parent.color = RED;
        }
    }

    private Node getUncle(Node parent) {
        Node grandparent = parent.parent;

        if (parent.data == grandparent.left.data) {
            return grandparent.right;
        } else if (parent.data == grandparent.right.data) {
            return grandparent.left;
        } else {
            throw new IllegalArgumentException("Something went wrong when trying to search for the parent of the given node.");
        }
    }

    public static void main(String[] args) {
        RBTTest rbt = new RBTTest();

        rbt.insertNode(17);
        rbt.insertNode(9);
        rbt.insertNode(19);
        rbt.insertNode(18);
        rbt.insertNode(75);
        rbt.insertNode(81);

        rbt.preorder(rbt.root);
    }
}
