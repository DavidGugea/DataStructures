package JavaSol.LinearDataStructures.Lists.LinkedList;

public class LinkedList {
    public Node head;
    private int size = 0;

    public int getSize() {
        return this.size;
    }

    public void append(int value) {
        if (this.head == null) {
            this.head = new Node(value);
        } else {
            Node current = this.head;

            while (current.next != null) {
                current = current.next;
            }

            current.next = new Node(value);
        }

        this.size += 1;
    }

    public void delete() {
        if(this.head == null) {
            return;
        }

        if(this.head.next == null) {
            this.head = null;
            return;
        }

        Node current = this.head;

        while (current.next.next != null) {
            current = current.next;
        }

        current.next = null;
        this.size -= 1;
    }

    public void delete_index(int index) {
        if (index < 0 || index >= this.size) {
            throw new IndexOutOfBoundsException("index out of bounds");
        }

        if(index == 0) {
            Node next = this.head.next;
            this.head = next;
            this.size -= 1;
            return;
        }

        int counter = 0;
        Node previous = null;
        Node current = this.head;

        while (counter != index) {
            previous = current;
            current = current.next;
            counter += 1;
        }

        previous.next = current.next;
        this.size -= 1;
    }

    public Node search(int value) {
        Node current = this.head;
        while (current != null) {
            if(current.value == value) {
                return current;
            }

            current = current.next;
        }

        throw new RuntimeException("Couldn't find a node with the given value inside the linked list.");
    }

    public void printList() {
        if (this.head == null) {
            System.out.println("The linked list is empty");
            return;
        }

        Node current = this.head;
        while (current != null) {
            System.out.print(current.value + " ");
            current = current.next;
        }

        System.out.println();
    }

    public static void main(String[] args) {
        LinkedList ll = new LinkedList();

        for (int i = 1; i <= 5; ++i) {
            ll.append(i);
        }

        for (int i = 1; i <= 5; ++i) {
            System.out.println(ll.search(i).value);
        }
    }
}
