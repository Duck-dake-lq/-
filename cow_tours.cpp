#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

const int MAXN = 155;
const double INF = 1e18;

struct Point {
    int x, y;
} points[MAXN];

double dist[MAXN][MAXN];
double max_dist[MAXN]; // 每个点到同一牧场内其他点的最大距离
double diameter[MAXN]; // 每个牧场的直径
int group[MAXN]; // 记录每个点属于哪个牧场

// 计算两点之间的欧几里得距离
double euclidean(int i, int j) {
    int dx = points[i].x - points[j].x;
    int dy = points[i].y - points[j].y;
    return sqrt(dx * dx + dy * dy);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(6);

    int n;
    cin >> n;

    // 读取坐标
    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    // 初始化距离矩阵
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                dist[i][j] = 0;
            } else {
                dist[i][j] = INF;
            }
        }
    }

    // 读取邻接矩阵并初始化直接连接的距离
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < n; ++j) {
            if (s[j] == '1') {
                dist[i][j] = euclidean(i, j);
            }
        }
    }

    // Floyd-Warshall算法计算所有点对的最短距离
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // 确定每个点所属的牧场（使用并查集思想）
    for (int i = 0; i < n; ++i) {
        group[i] = i;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] < INF) {
                // 找到i和j的根
                int root_i = i, root_j = j;
                while (group[root_i] != root_i) root_i = group[root_i];
                while (group[root_j] != root_j) root_j = group[root_j];
                if (root_i != root_j) {
                    group[root_j] = root_i;
                }
            }
        }
    }

    // 计算每个点的最大距离（到同一牧场内其他点的最远距离）
    for (int i = 0; i < n; ++i) {
        max_dist[i] = 0;
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] < INF) {
                max_dist[i] = max(max_dist[i], dist[i][j]);
            }
        }
    }

    // 计算每个牧场的直径
    for (int i = 0; i < n; ++i) {
        diameter[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] < INF) {
                int root = i;
                while (group[root] != root) root = group[root];
                diameter[root] = max(diameter[root], dist[i][j]);
            }
        }
    }

    // 找到所有可能的跨牧场连接，计算最小的新直径
    double min_new_diameter = INF;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // 检查i和j是否属于不同的牧场
            int root_i = i, root_j = j;
            while (group[root_i] != root_i) root_i = group[root_i];
            while (group[root_j] != root_j) root_j = group[root_j];
            if (root_i != root_j) {
                // 计算连接后的新直径
                double candidate = max(max(diameter[root_i], diameter[root_j]), 
                                     max_dist[i] + max_dist[j] + euclidean(i, j));
                if (candidate < min_new_diameter) {
                    min_new_diameter = candidate;
                }
            }
        }
    }

    cout << min_new_diameter << endl;

    return 0;
}