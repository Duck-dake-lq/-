#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<int> pos(n + 1);
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            pos[x] = i;
        }
        
        int count = 0;
        for (int d = 1; d <= n; d++) {
            for (int k = 1; d * (k + 1) <= n; k++) {
                int a = d * k;
                int b = d * (k + 1);
                if (__gcd(a, b) == b - a) {
                    if (abs(pos[a] - pos[b]) == 1) {
                        count++;
                    }
                }
            }
        }
        
        cout << count << '\n';
    }
    
    return 0;
}
