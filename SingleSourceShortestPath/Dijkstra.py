def dijkstra(self, vertices, edges, source, target):
    visited = set()
    distances = {v: float('inf') if v != source else 0 for v in vertices}
    heap = Heap([source], key=lambda v: distances[v])

    while target not in visited:
        u = heap.pop()
        if u in visited:
            continue
        visited.add(u)
        for v, weight in edges[u]:
            if distances[v] > distances[u] + weight:
                distances[v] = distances[u] + weight
                heap.push(v)
    
    return distances[target]