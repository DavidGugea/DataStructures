package JavaSol.Trees.BinaryTrees.BinaryTree;

public class BinaryTree {
    public Node root;

    public BinaryTree(int key) {
        root = new Node(key);
    }

    public BinaryTree() {
        root = null;
    }

    public void traversePreorder(Node node) {
        if (node == null) return;

        System.out.println(node.key);
        traversePreorder(node.left);
        traversePreorder(node.right);
    }

    public void traverseInorder(Node node) {
        if (node == null) return;

        traverseInorder(node.left);
        System.out.println(node.key);
        traverseInorder(node.right);
    }

    public void traversePostorder(Node node) {
        if (node == null) return;

        traversePostorder(node.left);
        traversePostorder(node.right);
        System.out.println(node.key);
    }

    public static void main(String[] args) {
        BinaryTree tree = new BinaryTree();

        tree.root = new Node(1);
        tree.root.left = new Node(2);
        tree.root.right = new Node(3);
        tree.root.left.left = new Node(4);

        System.out.println("Preorder traversing");
        tree.traversePreorder(tree.root);
        System.out.println();

        System.out.println("Inorder traversing");
        tree.traverseInorder(tree.root);
        System.out.println();

        System.out.println("Postorder traversing");
        tree.traversePostorder(tree.root);
        System.out.println();
    }
}
