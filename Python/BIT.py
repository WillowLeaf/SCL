class BIT:
    def __init__(self, size):
        self.data = [None] + [0] * size
        self.size = size
    
    def add(self, i, x):
        while i <= self.size:
            self.data[i] += x
            i += i & -i
    
    def sum(self, i):
        ans = 0
        while i:
            ans += self.data[i]
            i -= i & -i
        return ans
    
    def sum0(self, i):
        return self.sum(i + 1)

    def add0(self, i, x):
        return self.add(i + 1, x)
