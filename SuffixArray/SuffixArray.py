from functools import partial, cmp_to_key
class SuffixArray:
    def __init__(self, s):
        self.s = s
        self.size = len(s)
        self.sa = None
        self.rank = None
        self.height = None

    def buildSA(self):
        self.sa = list(range(self.size))
        self.rank = [ord(c) - ord('a') for c in self.s]
        buffer = [0] * self.size

        k = 1
        while k < self.size:
            self.sa = sorted(self.sa, key = cmp_to_key(partial(self.compare, k)))
            buffer[self.sa[0]] = 0
            for i in range(1, self.size):
                buffer[self.sa[i]] = buffer[self.sa[i - 1]] + (0 if self.compare(k, self.sa[i - 1], self.sa[i]) == 0 else 1)
            self.rank, buffer = buffer, self.rank
            k *= 2
        
        for i in range(self.size):
            self.rank[self.sa[i]] = i
    
    def buildHeight(self):
        h = 0
        self.height = [0] * (self.size - 1)
        for i in range(self.size):
            if self.rank[i] == 0:
                continue
            if h > 0:
                h -= 1

            j = self.sa[self.rank[i] - 1]
            while i + h < self.size and j + h < self.size and self.s[i + h] == self.s[j + h]:
                h += 1

            self.height[self.rank[i] - 1] = h
    
    def compare(self, k, i, j):
        if self.rank[i] != self.rank[j]:
            return self.rank[i] - self.rank[j]
        else:
            vi = self.rank[i + k] if i + k < self.size else -1
            vj = self.rank[j + k] if j + k < self.size else -1
            return vi - vj

# unit tests
data = [
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
    "aaa",
    "aaaaaaaaabbbbbbbbbbbbabababababbabbbbbbbb",
    "abcdefghijklmnopqrstuvwxyz",
    "ab" * 1000,
    "a" * 1000 + "b"
]

for i, datum in enumerate(data):
    print("Case", i, ":")

    sa = SuffixArray(datum)
    sa.buildSA()
    sa.buildHeight()

    suffices = sorted([datum[i:] for i in range(len(datum))])
    print("Check sa[]")
    for i in range(sa.size):
        if datum[sa.sa[i]:] != suffices[i]:
            print(i, datum[sa.sa[i]:], suffices[i], sep='\t')
    else:
        print("Pass!")

    print("Check height[]")
    for i in range(sa.size - 1):
        h = sa.height[i]
        s1 = datum[sa.sa[i]:]
        s2 = datum[sa.sa[i + 1]:]
        if not (s1[:h] == s2[:h] and (h >= len(s1) or h >= len(s2) or s1[h] != s2[h])):
            print(i, h, s1, s2, sep='\t')
    else:
        print("Pass!")