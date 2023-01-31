from typing import Any


class CircularBuffer:
    def __init__(self, size: int = 5) -> None:
        self.size = size

        self.insert_pointer = 0
        self.delete_pointer = 0 
        self.cycles = 0

        self.internal_array = [None]*size

    def index_in_bounds(self, index: int) -> bool:
        return index >= 0 and index <= (self.size-1)

    def append(self, value: Any) -> None:
        if not self.index_in_bounds(self.insert_pointer):
            self.cycles += 1
            self.insert_pointer = 0

        self.internal_array[self.insert_pointer] = value
        self.insert_pointer += 1

    def delete(self) -> None:
        if not self.index_in_bounds(self.delete_pointer):
            self.delete_pointer = 0

        if self.cycles > 0 and self.delete_pointer < self.insert_pointer:
            self.delete_pointer = self.insert_pointer

        self.internal_array[self.delete_pointer] = None
        self.delete_pointer += 1

    def __str__(self) -> str:
        return str(self.internal_array)

if __name__ == "__main__":
    cb = CircularBuffer(5)

    print(cb)
    
    for i in range(7):
        cb.append(i)

    print(cb)

    cb.delete()
    print(cb)
