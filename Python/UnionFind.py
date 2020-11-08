class UnionFind:
    def __init__(self, size):
        self.p = list(range(size))
    
    def find(self, idx):
        if self.p[idx] != idx:
            self.p[idx] = self.find(self.p[idx])
        return self.p[idx]

    def union(self, s1, s2):
        p1 = self.find(s1)
        self.p[p1] = self.find(s2)