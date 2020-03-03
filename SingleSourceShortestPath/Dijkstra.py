def dijkstra(self, vertices, edges, source, target):
    done = set()
    distances = [float('inf') if v != source else 0 for v in vertices]
    heap = Heap([source], key=lambda v: distances[v])

    while target not in done:
        u = heap.pop()
        if u in done:
            continue
        for v, length in edges[u]:
            if distances[v] > distances[u] + length:
                distances[v] = distances[u] + length
                heap.push(v)
        done.add(u)
    
    return distances[target]