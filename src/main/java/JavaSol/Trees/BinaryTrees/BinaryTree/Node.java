package JavaSol.Trees.BinaryTrees.BinaryTree;

public class Node {
    public int key;
    public Node left;
    public Node right;

    public Node(int key) {
        this.key = key;
        this.left = null;
        this.right = null;
    }

    @Override
    public String toString() {
        return "Node{" +
                "key=" + key +
                ", left=" + left +
                ", right=" + right +
                '}';
    }
}
