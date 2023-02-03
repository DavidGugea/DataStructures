package JavaSol.Trees.BinaryTrees.BinarySearchTree.HackerRank;

public class Node {
    Node left, right;
    int data;

    public Node(int data) {
        this.data = data;
    }

    public void insert(int value) {
        if(value <= data) {
            if(left == null) {
                left = new Node(value);
            } else {
                left.insert(value);
            }
        } else {
            if (right == null) {
                right = new Node(value);
            } else {
                right.insert(value);
            }
        }
    }

    public boolean contains(int value) {
        // Check if the tree contains the given value
        if (value == data) {
            return true;
        } else if(value < data) {
            if (left == null) {
                return false;
            } else {
                return left.contains(value);
            }
        } else {
            if (right == null) {
                return false;
            } else {
                return right.contains(value);
            }
        }
    }

    public void printInOrder() {
        if (left != null) {
            left.printInOrder();
        }

        System.out.println(this.data);

        if (right != null) {
            right.printInOrder();
        }
    }
}
