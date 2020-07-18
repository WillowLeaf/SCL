class KMP:
    def __init__(self, pattern):
        if not pattern:
            raise Exception("Cannot set empty string as pattern!")
        self.next = [0, 0]
        self.pattern = pattern
        k = 0
        for i in range(2, len(self.pattern) + 1):
            while k > 0 and self.pattern[k] != self.pattern[i - 1]:
                k = self.next[k]
            if self.pattern[k] == self.pattern[i - 1]:
                k += 1
            self.next.append(k)
    def match(self, string):
        ans = []
        k = 0
        for i, ch in enumerate(string):
            while k > 0 and self.pattern[k] != ch:
                k = self.next[k]
            if self.pattern[k] == ch:
                k += 1
                if k == len(self.pattern):
                    ans.append(i - len(self.pattern) + 1)
                    k = self.next[k]
        return ans

if __name__ == '__main__':
    while True:
        string = input("Please input the string:")
        pattern = input("Please input the pattern:")
        kmp = KMP(pattern)
        result = kmp.match(string)
        print(len(result), "result(s):", *result)