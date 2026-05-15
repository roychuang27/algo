/*
 * Submission ID: 334834521
 * Problem: The Secret Number
 * Link: https://codeforces.com/contest/2132/problem/B
 */

#pragma GCC optimize("Ofast")
#include <algorithm>
#include <iostream>
#include <vector>
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
    lli N; cin >> N;
    vector<lli> nums;
    int cnt = 0;
    for (lli k = 10; k < 1e18; k*=10) {
        lli temp = k + 1;
        if (N % temp) continue;
        cnt++;
        nums.eb(N / temp);
    }
    cout << cnt << '\n';
    sort(ALL(nums));
    if (cnt > 0)
        printv(nums);
}
 
int main() {
    fastio;
    int t; cin >> t;
    while (t--) solve();
    return 0;
}