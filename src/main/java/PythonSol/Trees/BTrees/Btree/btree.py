class Node:
    def __init__(self, leaf=False):
        self.keys = []
        self.children = []
        self.leaf = leaf

class BTree():
    def __init__(self, t):
        self.root = Node(True)
        self.t = t

    def search(self, key, node=None):
        node = self.root if node == None else node

        i = 0

        while i < len(node.keys) and key > node.keys[i]:
            i += 1

        if i < len(node.keys) and key == node.keys[i]:
            return (node, i)
        elif node.leaf:
            return None
        else:
            return self.search(key, node.children[i])

    def split_child(self, x, i):
        t = self.t

        # i -> index of a full child
        y = x.children[i]

        z = Node(y.leaf)
        x.children.insert(i+1, z)

        x.keys.insert(i, y.keys[t-1])

        z.keys = y.keys[t: (2*t)-1]
        y.keys = y.keys[0: t-1]

        if not y.leaf:
            z.children = y.children[t: 2*t]
            y.children = y.children[0: t-1]

    def insert(self, k):
        t = self.t
        root = self.root

        if len(root.keys) == (2 * t) - 1:
            new_root = Node()
            self.root = new_root
            new_root.children.insert(0, root)
            self.split_child(new_root, 0)
            self.insert_non_full(new_root, k)
        else:
            self.insert_non_full(root, k)

    def insert_non_full(self, x, k):
        t = self.t
        i = len(x.keys) - 1

        if x.leaf:
            x.keys.append(None)

            while i >= 0 and k < x.keys[i]:
                x.keys[i+1] = x.keys[i]
                i -= 1
                
            x.keys[i+1] = k
        else:
            while i >= 0 and k < x.keys[i]:
                i -= 1

            i += 1

            if len(x.children[i].keys) == (2 * t) - 1:
                self.split_child(x, i)

                if k > x.keys[i]:
                    i += 1

            self.insert_non_full(x.children[i], k)