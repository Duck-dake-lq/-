import sys
from collections import deque

def main():
    n, s = map(int, sys.stdin.readline().split())
    
    adj = [[] for _ in range(n+1)]
    for _ in range(n-1):
        u, v, w = map(int, sys.stdin.readline().split())
        adj[u].append((v, w))
        adj[v].append((u, w))
    
    def bfs(start):
        dist = [-1] * (n+1)
        parent = [0] * (n+1)
        q = deque([start])
        dist[start] = 0
        while q:
            u = q.popleft()
            for v, w in adj[u]:
                if dist[v] == -1:
                    dist[v] = dist[u] + w
                    parent[v] = u
                    q.append(v)
        max_dist = max(dist)
        far_node = dist.index(max_dist)
        return far_node, dist, parent
    
    u, _, _ = bfs(1)
    v, dist_u, parent_v = bfs(u)
    _, dist_v, _ = bfs(v)
    
    diameter = []
    cur = v
    while cur != u:
        diameter.append(cur)
        cur = parent_v[cur]
    diameter.append(u)
    diameter = diameter[::-1]
    
    m = len(diameter)
    pos = [0] * m
    pos[0] = 0
    for i in range(1, m):
        for neighbor, w in adj[diameter[i]]:
            if neighbor == diameter[i-1]:
                pos[i] = pos[i-1] + w
                break
    
    ecc = [0] * m
    visited = [False] * (n+1)
    for i in range(m):
        visited[diameter[i]] = True
    
    for i in range(m):
        node = diameter[i]
        q = deque([(node, 0)])
        while q:
            u_curr, d = q.popleft()
            ecc[i] = max(ecc[i], d)
            for v_curr, w in adj[u_curr]:
                if not visited[v_curr]:
                    visited[v_curr] = True
                    q.append((v_curr, d + w))
    
    min_ecc = float('inf')
    j = 0
    for i in range(m):
        while j < m and pos[j] - pos[i] <= s:
            j += 1
        current_max = max(ecc[i], ecc[j-1])
        if i > 0:
            current_max = max(current_max, pos[i])
        if j <= m-1:
            current_max = max(current_max, pos[-1] - pos[j-1])
        min_ecc = min(min_ecc, current_max)
    
    print(min_ecc)

if __name__ == "__main__":
    main()