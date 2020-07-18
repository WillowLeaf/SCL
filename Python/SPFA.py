from collections import deque
def spfa(self, vertices, edges, source, target):
    distances = {v: float('inf') if v != source else 0 for v in vertices}
    inQueue = set()
    queue = deque()
    queue.append(source)
    inQueue.add(source)
    while len(queue) > 0:
        u = queue.popleft()
        inQueue.remove(u)
        for v, w in edges[u]:
            if distances[v] > distances[u] + w:
                distances[v] = distances[u] + w
                if v not in inQueue:
                    inQueue.add(v)
                    queue.append(v)
    
    return distances[target]