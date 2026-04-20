#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> next(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> next[i];
    }
    
    vector<int> ans(n + 1, 0);
    vector<int> state(n + 1, 0);
    
    for (int i = 1; i <= n; ++i) {
        if (state[i] == 0) {
            vector<int> path;
            int curr = i;
            while (true) {
                if (state[curr] == 1) {
                    int cycle_start = 0;
                    while (path[cycle_start] != curr) {
                        cycle_start++;
                    }
                    int cycle_len = path.size() - cycle_start;
                    for (int j = cycle_start; j < path.size(); ++j) {
                        ans[path[j]] = cycle_len;
                        state[path[j]] = 2;
                    }
                    for (int j = cycle_start - 1; j >= 0; --j) {
                        ans[path[j]] = ans[path[j + 1]] + 1;
                        state[path[j]] = 2;
                    }
                    break;
                }
                if (state[curr] == 2) {
                    for (int j = path.size() - 1; j >= 0; --j) {
                        ans[path[j]] = ans[next[path[j]]] + 1;
                        state[path[j]] = 2;
                    }
                    break;
                }
                state[curr] = 1;
                path.push_back(curr);
                curr = next[curr];
            }
        }
    }
    
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << '\n';
    }
    
    return 0;
}
