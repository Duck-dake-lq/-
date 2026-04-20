#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Event {
    int x, y1, y2, delta;
    Event(int x, int y1, int y2, int delta) : x(x), y1(y1), y2(y2), delta(delta) {}
    bool operator<(const Event& other) const {
        if (x != other.x) return x < other.x;
        return delta < other.delta;
    }
};

class SegmentTree {
private:
    vector<int> count;
    vector<long long> length;
    vector<long long> total_length;
    int n;
    int size;

public:
    SegmentTree(const vector<int>& sorted_ys) {
        n = sorted_ys.size() - 1;
        size = 1;
        while (size < n) size <<= 1;
        count.resize(2 * size, 0);
        length.resize(2 * size, 0);
        total_length.resize(2 * size, 0);
        for (int i = 0; i < n; ++i) {
            total_length[size + i] = sorted_ys[i + 1] - sorted_ys[i];
        }
        for (int i = size - 1; i > 0; --i) {
            total_length[i] = total_length[2 * i] + total_length[2 * i + 1];
        }
    }

    void update_range(int l, int r, int delta, int node = 1, int node_l = 0, int node_r = -1) {
        if (node_r == -1) node_r = size - 1;
        if (r < node_l || node_r < l) return;
        if (l <= node_l && node_r <= r) {
            count[node] += delta;
            if (count[node] > 0) {
                length[node] = total_length[node];
            } else {
                if (node >= size) {
                    length[node] = 0;
                } else {
                    length[node] = length[2 * node] + length[2 * node + 1];
                }
            }
            return;
        }
        int mid = (node_l + node_r) / 2;
        update_range(l, r, delta, 2 * node, node_l, mid);
        update_range(l, r, delta, 2 * node + 1, mid + 1, node_r);
        if (count[node] > 0) {
            length[node] = total_length[node];
        } else {
            length[node] = length[2 * node] + length[2 * node + 1];
        }
    }

    long long get_length() const {
        return length[1];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> ys;
    vector<Event> events;
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        ys.push_back(y1);
        ys.push_back(y2);
        events.emplace_back(x1, y1, y2, 1);
        events.emplace_back(x2, y1, y2, -1);
    }
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    sort(events.begin(), events.end());
    SegmentTree st(ys);
    long long area = 0;
    int prev_x = -1;
    for (const auto& event : events) {
        int x = event.x;
        if (prev_x != -1 && x > prev_x) {
            area += (long long)(x - prev_x) * st.get_length();
        }
        int l = lower_bound(ys.begin(), ys.end(), event.y1) - ys.begin();
        int r = lower_bound(ys.begin(), ys.end(), event.y2) - ys.begin() - 1;
        if (l <= r) {
            st.update_range(l, r, event.delta);
        }
        prev_x = x;
    }
    cout << area << endl;
    return 0;
}
