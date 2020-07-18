from heapq import heappush, heappop
def dijkstra(self, vertices, edges, source, target):
    d = {v: float('inf') if v != source else 0 for v in vertices}
    heap = [(0, source)]
    visited = set()

    while heap and target not in visited:
        key, u = heappop(heap)
        if d[u] < key or u in visited:
            continue
        visited.add(u)
        for v, weight in edges[u]:
            if d[v] > d[u] + weight:
                d[v] = d[u] + weight
                heappush(heap, (d[v], v))
    
    return d[target]