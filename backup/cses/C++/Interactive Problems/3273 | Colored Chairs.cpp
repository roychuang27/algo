/*
 * Submission ID: 14774055
 * Problem: Colored Chairs
 * Link: https://cses.fi/problemset/task/3273
 */

#include <iostream>
#include <vector>
using namespace std;

int q(int k) {
    cout << "? " << k << endl;
    char q; cin >> q;
    return (q == 'R');
}

void find(int ql, int qr, int N) {
    int l = 1, r = N-1;
    while (l < r) {
        int m = (l + r + 1) / 2;
        int qm = q(m) ^ (m%2);
        if (qm != ql) {
            r = m - 1;
        } else {
            l = m;
        }
    }
    cout << "! " << l << '\n';
}

// R = 0, B = 1

void solve() {
    int N; cin >> N;
    int ql, qr;
    ql = q(1);
    qr = q(N);
    if (ql == qr) {
        cout << "! " << N << endl;
        return;
    }
    find(!ql, (qr)^(N%2), N);
}

int main() {
    solve();
    return 0;
}


