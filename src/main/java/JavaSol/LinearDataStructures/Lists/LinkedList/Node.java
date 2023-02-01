package JavaSol.LinearDataStructures.Lists.LinkedList;

public class Node {
    public int value;
    public Node next;

    public Node(int value) {
        this.value = value;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    public Node getNext() {
        return next;
    }

    public void setNext(Node next) {
        this.next = next;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Node node = (Node) o;

        if (getValue() != node.getValue()) return false;
        return getNext() != null ? getNext().equals(node.getNext()) : node.getNext() == null;
    }

    @Override
    public int hashCode() {
        int result = getValue();
        result = 31 * result + (getNext() != null ? getNext().hashCode() : 0);
        return result;
    }

    @Override
    public String toString() {
        return "Node{" +
                "value=" + value +
                ", next=" + next +
                '}';
    }
}
