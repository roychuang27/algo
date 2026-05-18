#include <bits/stdc++.h>
using namespace std;
 
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n, t;
    cin >> n >> t;
    
    vector<int> k(n);
    for (int i = 0; i < n; i++) cin >> k[i];
 
    long long L = 0, R = 1e18;
 
    while (L < R) {
        long long M = (L + R) / 2;
        unsigned long long sum = 0;
        for (int i : k) {
            sum += M / i;
            if (sum >= t) break;
        }
        if (sum >= t) R = M;
        else L = M + 1;
    }
 
    cout << L;
 
    return 0;
}