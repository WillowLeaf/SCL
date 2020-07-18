class TreeNode:
    def __init__(self, start, end):
        self.left = None
        self.right = None
        self.lazy = 0
        self.ans = 0
        self.start = start
        self.end = end

    def eval(self):
        self.ans += self.lazy
        if self.start < self.end:
            if self.left is None and self.right is None:
                mid = (self.start + self.end) // 2
                self.left = TreeNode(self.start, mid)
                self.right = TreeNode(mid + 1, self.end)

            self.left.lazy += self.lazy
            self.right.lazy += self.lazy
        self.lazy = 0
            
    def increment(self, start, end):
        if self.start > end or self.end < start:
            self.eval()
            return 
            
        if start <= self.start and self.end <= end:
            self.lazy += 1
            self.eval()
        else:
            self.eval()
            self.left.increment(start, end)
            self.right.increment(start, end)
            self.ans = max(self.left.ans, self.right.ans)