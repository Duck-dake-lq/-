#include <bits/stdc++.h>
using namespace std;

int main() {
    const int n = 200000;
    auto start = chrono::high_resolution_clock::now();
    
    int count = 0;
    for (int d = 1; d <= n; d++) {
        for (int k = 1; d * (k + 1) <= n; k++) {
            count++;
        }
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    cout << "循环次数: " << count << endl;
    cout << "运行时间: " << duration.count() << "ms" << endl;
    
    return 0;
}
