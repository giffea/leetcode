class Node:
    def __init__(self, key=None, value=None):
        self.pre = None
        self.next = None
        self.key = key
        self.value = value


class LRUCache:
    def __init__(self, capacity: int):
        self.capacity = capacity
        self.cache = {}
        self.his_size = 0

        # history double link-list
        self.head = Node()
        self.tail = Node()
        self.head.next = self.tail
        self.tail.pre = self.head

    def get(self, key: int) -> int:
        node = self.find(key)
        if node:
            return node.value
        return -1

    def put(self, key: int, value: int) -> None:
        node = self.find(key)
        if node:
            node.value = value
            return

        node = Node(key, value)
        self.cache[key] = node
        self.add_tail(node)

        self.his_size += 1
        if self.his_size > self.capacity:
            to_del = self.head.next
            self.head.next = to_del.next
            to_del.next.pre = self.head
            del self.cache[to_del.key]
            self.his_size = self.capacity

    def find(self, key: int) -> Node:
        if key in self.cache:
            node = self.cache[key]
            if self.tail.pre is not node:
                node.pre.next = node.next
                node.next.pre = node.pre
                self.add_tail(node)
            return node
        return None

    def add_tail(self, node: Node) -> None:
        last = self.tail.pre
        last.next = node
        node.pre = last
        self.tail.pre = node


# Your LRUCache object will be instantiated and called as such:
# obj = LRUCache(capacity)
# param_1 = obj.get(key)
# obj.put(key,value)


if __name__ == '__main__':
    # cmd = ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
    # para = [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
    res = []
    # """
    cache = LRUCache(2)
    res.append(cache.put(1, 1))
    res.append(cache.put(2, 2))
    res.append(cache.get(1))
    res.append(cache.put(3, 3))
    res.append(cache.get(2))
    res.append(cache.put(4, 4))
    res.append(cache.get(1))
    res.append(cache.get(3))
    res.append(cache.get(4))
    """
    cache = LRUCache(1)
    res.append(cache.put(1, 1))
    res.append(cache.put(2, 2))
    res.append(cache.get(1))
    res.append(cache.get(2))
    # """

    for val in res:
        print(val)
