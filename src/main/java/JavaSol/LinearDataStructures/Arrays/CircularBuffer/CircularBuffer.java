package JavaSol.LinearDataStructures.Arrays.CircularBuffer;

public class CircularBuffer {
    private final int size;

    private int insert_pointer = 0;
    private int delete_pointer = 0;

    private int cycles = 0;

    private int[] internal_array;

    public CircularBuffer(int size) {
        this.size = size;

        this.internal_array = new int[size];
    }

    boolean index_in_bounds(int index) {
        return (index >= 0) && (index <= (this.size-1));
    }

    void add(int value) {
        if(value == 0) {
            return;
        }

        if(!index_in_bounds(this.insert_pointer)) {
            this.insert_pointer = 0;
            this.cycles += 1;
        }

        this.internal_array[this.insert_pointer] = value;
        this.insert_pointer += 1;
    }

    void delete() {
        if(!index_in_bounds(this.delete_pointer)) {
            this.delete_pointer = 0;
        }

        if(this.cycles > 0 && this.delete_pointer < this.insert_pointer) {
            // Override the pointer
            this.delete_pointer = this.insert_pointer;
        }

        this.internal_array[this.delete_pointer] = 0;
        this.delete_pointer += 1;
    }

    void print() {
        for(int i = 0 ; i < size; ++i) {
            System.out.println(this.internal_array[i]);
        }
    }

    public static void main(String[] args) {
        CircularBuffer cb = new CircularBuffer(5);

        cb.print();

        for(int i = 1; i <= 7; ++i) {
            cb.add(i);
        }

        System.out.println("-------------");

        cb.print();
    }
}
