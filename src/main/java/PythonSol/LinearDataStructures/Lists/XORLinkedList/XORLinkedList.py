ids: dict[int, 'Node'] = {}


class Node:
    def __init__(self, value: int) -> None:
        self.value = value

        # self.store_address = address_prev_node XOR address_next_node
        self.prev_node_address: int = None
        self.next_node_address: int = None
        self.store_address: int = None

    def set_near_Nodes(self, prev_node: 'Node', next_node: 'Node') -> None:
        if prev_node == None:
            self.prev_node_address = 0
        else:
            self.prev_node_address = id(prev_node)

        if next_node == None:
            self.next_node_address = 0
        else:
            self.next_node_address = id(prev_node)

        self.store_address = self.prev_node_address ^ self.next_node_address

    def get_next_node(self) -> 'Node':
        next_node_address = self.store_address ^ self.prev_node_address
        return ids[next_node_address]

    def get_previous_node(self) -> 'Node':
        prev_node_address = self.store_address ^ self.next_node_address
        return ids[prev_node_address]


## ...