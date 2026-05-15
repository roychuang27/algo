/*
 * Submission ID: 334885978
 * Problem: The Cunning Seller (easy version)
 * Link: https://codeforces.com/contest/2132/problem/C1
 */

#pragma GCC optimize("Ofast")
#include <cmath>
#include <iostream>
#define fastio cin.tie(0)->sync_with_stdio(false)
#define eb emplace_back
#define test(x) cerr << "Line(" << __LINE__ << ") " #x << ' ' << x << endl
#define printv(x) { \
    for (auto i : x) cout << i << ' '; \
    cout << endl; \
}
#define pii pair<int, int>
#define pll pair<lli, lli>
#define ALL(x) x.begin(), x.end()
#define rALL(x) x.rbegin(), x.rend()
#define MP(x, y) make_pair((x), (y))
#define SQ(x) ((x)*(x))
#define SZ(x) ((int) x.size())
 
using namespace std;
typedef long long int lli;
 
template <typename A, typename B>
ostream& operator << (ostream& o, pair<A, B> a) {
    return o << a.first << ' ' << a.second;
}
template <typename A, typename B>
istream& operator >> (istream& o, pair<A, B> &a) {
    return o >> a.first >> a.second;
}
 
lli fpow (lli a, int b) {
    if (b < 0) return 0;
    lli res = 1;
    while (b) {
        if (b & 1) res *= a;
        b >>= 1;
        a *= a;
    }
    return res;
}
 
void solve() {
    int N; cin >> N;
    lli ans = 0;
    for (int x = 18; x >= 0; x--) {
        lli d = fpow(3, x+1) + x * fpow(3, x-1);
        lli cnt = fpow(3, x);
        while (N >= cnt) {
            N -= cnt;
            ans += d;
        }
    }
    cout << ans << '\n';
}
 
int main() {
    fastio;
    int t; cin >> t;
    while(t--) solve();
    return 0;
}