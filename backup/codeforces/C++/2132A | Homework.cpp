/*
 * Submission ID: 334815557
 * Problem: Homework
 * Link: https://codeforces.com/contest/2132/problem/A
 */

#pragma GCC optimize("Ofast")
#include <iostream>
#include <string>
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
 
void solve() {
    int N; cin >> N;
    string a; cin >> a;
    int M; cin >> M;
    string b; cin >> b;
    string c; cin >> c;
    for (int i = 0; i < M; i++) {
        if (c[i] == 'V') a = b[i] + a;
        else a = a + b[i];
    }
    cout << a << '\n';
}
 
int main() {
    fastio;
    int t; cin >> t;
    while (t--)
        solve();
    return 0;
}