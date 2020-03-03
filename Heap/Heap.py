class Heap:
    def __init__(self, elements, key):
        self.data = [None]
        self.data += [(key(e), e) for e in elements]
        self.key = key
        self.heapify()

    def heapify(self):
        n = len(self.data) - 1
        for i in range(n >> 1, 0, -1):
            self.siftDown(i)

    def siftDown(self, i):
        cur = i
        n = len(self.data) - 1
        while cur <= n >> 1:
            winner = cur
            left = cur * 2
            right = cur * 2 + 1
            if left <= n and self._getKey(left) < self._getKey(winner):
                winner = left

            if right <= n and self._getKey(right) < self._getKey(winner):
                winner = right 
            
            if winner == cur:
                break

            self.data[cur], self.data[winner] = self.data[winner], self.data[cur]
            cur = winner
        
        return cur

    def siftUp(self, i):
        cur = i
        while cur > 1:
            parent = cur >> 1
            if self._getKey(cur) >= self._getKey(parent):
                break
            self.data[cur], self.data[parent] = self.data[parent], self.data[cur]
            cur = parent

        return cur

    def top(self):
        return self._getValue(1)

    def pop(self):
        top = self.top()
        self.data[1], self.data[-1] = self.data[-1], self.data[1] 
        self.data.pop()
        self.siftDown(1)
        return top

    def push(self, value):
        self.data.append((self.key(value), value))
        self.siftUp(len(self.data) - 1)

    def _getKey(self, i):
        return self.data[i][0]

    def _getValue(self, i):
        return self.data[i][1]

data = [3, 2, 5,1, 1, 1000, 3, 10, 200, 8, -1900, -1, -1, 0, -4, 4, 4, -100]
print("Expected: ", sorted(data))
heap1 = Heap(data, key=lambda x: x)
result1 = [heap1.pop() for i in range(len(data))]
print("Actual1:", result1)

heap2 = Heap([], key=lambda x: x)
for d in data:
    heap2.push(d)
result2 = [heap2.pop() for i in range(len(data))]
print("Actual2:", result2)