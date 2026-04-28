import sys
from math import gcd

def solve():
    input = sys.stdin.read
    data = input().split()
    idx = 0
    t = int(data[idx])
    idx += 1
    results = []
    for _ in range(t):
        n = int(data[idx])
        idx += 1
        p = list(map(int, data[idx:idx+n]))
        idx += n
        
        pos = [0] * (n + 1)
        for i in range(n):
            pos[p[i]] = i
        
        count = 0
        for d in range(1, n + 1):
            k = 1
            while d * (k + 1) <= n:
                a = d * k
                b = d * (k + 1)
                if gcd(a, b) == b - a:
                    if abs(pos[a] - pos[b]) == 1:
                        count += 1
                k += 1
        
        results.append(count)
    
    print('\n'.join(map(str, results)))

if __name__ == "__main__":
    solve()
