#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
using namespace std;

vector<long long> get_divisors(long long n) {
    vector<long long> res;
    for (long long i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            res.push_back(i);
            if (i != n / i) {
                res.push_back(n / i);
            }
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        long long n;
        cin >> n;
        long long m = static_cast<long long>(sqrtl(n));
        if (m * m == n) {
            cout << 0 << '\n';
            continue;
        }
        unordered_set<long long> used;
        vector<long long> steps;
        for (int i = 0; i < 100; ++i) {
            m = static_cast<long long>(sqrtl(n));
            if (m * m < n) m++;
            long long d = m * m - n;
            if (d == 0) break;
            vector<long long> divs = get_divisors(n);
            bool found = false;
            for (long long x : divs) {
                if (x == d && used.find(x) == used.end()) {
                    steps.push_back(x);
                    used.insert(x);
                    n += x;
                    found = true;
                    break;
                }
            }
            if (found) continue;
            steps.push_back(n);
            used.insert(n);
            n += n;
        }
        cout << steps.size() << '\n';
        for (int i = 0; i < steps.size(); ++i) {
            if (i > 0) cout << ' ';
            cout << steps[i];
        }
        if (!steps.empty()) cout << '\n';
    }
    return 0;
}
