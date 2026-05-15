/*
 * Submission ID: 15079691
 * Problem: Next Prime
 * Link: https://cses.fi/problemset/task/3396
 */

#include <iostream>
#include <cmath>
using namespace std;

bool isprime(long long int p) {
        if (p == 1 || p == 2) return 1;
        if (p % 2 == 0) return 0;
        for (long long int k = 3; k * k <= p; k+=2) {
                if (p % k == 0)
                        return 0;
        }
        
        return 1;
}

void solve() {
        long long int N; cin >> N;
        
        long long int res = N + 1;
        while (!isprime(res))
                res++;

        cout << res << '\n';
}

int main() {
        int T; cin >> T;
        while (T--)
                solve();
        return 0;
}