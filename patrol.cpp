#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<pair<int, int>>> adj;

pair<int, int> bfs(int start, vector<int>& parent) {
    int n = parent.size() - 1;
    vector<int> dist(n + 1, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    parent[start] = -1;
    int max_dist = 0;
    int far_node = start;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[v] == -1) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                q.push(v);
                if (dist[v] > max_dist) {
                    max_dist = dist[v];
                    far_node = v;
                }
            }
        }
    }
    return {far_node, max_dist};
}

void dfs(int u, int parent, int& max_len, int& current_max) {
    int first = 0, second = 0;
    for (auto& edge : adj[u]) {
        int v = edge.first;
        int w = edge.second;
        if (v == parent) continue;
        int child_max = 0;
        dfs(v, u, max_len, child_max);
        int len = child_max + w;
        if (len > first) {
            second = first;
            first = len;
        } else if (len > second) {
            second = len;
        }
    }
    max_len = max(max_len, first + second);
    current_max = first;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, K;
    cin >> n >> K;
    adj.resize(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].emplace_back(b, 1);
        adj[b].emplace_back(a, 1);
    }
    
    vector<int> parent1(n + 1);
    auto [u, _] = bfs(1, parent1);
    
    vector<int> parent2(n + 1);
    auto [v, d1] = bfs(u, parent2);
    
    if (K == 1) {
        cout << 2 * (n - 1) - (d1 - 1) << endl;
        return 0;
    }
    
    // 找到u到v的路径，将路径上的边权改为-1
    vector<int> path;
    int current = v;
    while (current != u) {
        path.push_back(current);
        current = parent2[current];
    }
    path.push_back(u);
    
    for (size_t i = 0; i < path.size() - 1; ++i) {
        int a = path[i];
        int b = path[i + 1];
        for (auto& edge : adj[a]) {
            if (edge.first == b) {
                edge.second = -1;
                break;
            }
        }
        for (auto& edge : adj[b]) {
            if (edge.first == a) {
                edge.second = -1;
                break;
            }
        }
    }
    
    // 计算修改后的最长路径
    int d2 = 0, current_max = 0;
    dfs(1, -1, d2, current_max);
    
    cout << 2 * (n - 1) - (d1 - 1) - (d2 - 1) << endl;
    
    return 0;
}