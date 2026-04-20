import bisect

class SegmentTree:
    def __init__(self, sorted_ys):
        self.n = len(sorted_ys) - 1
        self.size = 1
        while self.size < self.n:
            self.size <<= 1
        self.count = [0] * (2 * self.size)
        self.length = [0] * (2 * self.size)
        self.total_length = [0] * (2 * self.size)
        for i in range(self.n):
            self.total_length[self.size + i] = sorted_ys[i+1] - sorted_ys[i]
        for i in range(self.size - 1, 0, -1):
            self.total_length[i] = self.total_length[2*i] + self.total_length[2*i+1]
    
    def update_range(self, l, r, delta, node=1, node_l=0, node_r=None):
        if node_r is None:
            node_r = self.size - 1
        if r < node_l or node_r < l:
            return
        if l <= node_l and node_r <= r:
            self.count[node] += delta
            if self.count[node] > 0:
                self.length[node] = self.total_length[node]
            else:
                if node >= self.size:
                    self.length[node] = 0
                else:
                    self.length[node] = self.length[2*node] + self.length[2*node+1]
            return
        mid = (node_l + node_r) // 2
        self.update_range(l, r, delta, 2*node, node_l, mid)
        self.update_range(l, r, delta, 2*node+1, mid+1, node_r)
        if self.count[node] > 0:
            self.length[node] = self.total_length[node]
        else:
            self.length[node] = self.length[2*node] + self.length[2*node+1]
    
    def get_length(self):
        return self.length[1]

def main():
    import sys
    input = sys.stdin.read().split()
    idx = 0
    n = int(input[idx])
    idx += 1
    ys = []
    events = []
    for _ in range(n):
        x1 = int(input[idx])
        y1 = int(input[idx+1])
        x2 = int(input[idx+2])
        y2 = int(input[idx+3])
        idx +=4
        ys.append(y1)
        ys.append(y2)
        events.append( (x1, y1, y2, 1) )
        events.append( (x2, y1, y2, -1) )
    sorted_ys = sorted( list( set(ys) ) )
    events.sort( key=lambda e: (e[0], e[3]) )
    st = SegmentTree(sorted_ys)
    prev_x = None
    area = 0
    for event in events:
        x, y1, y2, delta = event
        if prev_x is not None and x > prev_x:
            area += (x - prev_x) * st.get_length()
        l = bisect.bisect_left(sorted_ys, y1)
        r = bisect.bisect_left(sorted_ys, y2) - 1
        if l <= r:
            st.update_range(l, r, delta)
        prev_x = x
    print(area)

if __name__ == '__main__':
    main()
