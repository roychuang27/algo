/*
 * Submission ID: 331126325
 * Problem: Recycling Center
 * Link: https://codeforces.com/contest/2128/problem/A
 */

#pragma GCC optimize("Ofast")
#include <iostream>
#include <vector>
#include <algorithm>
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
    int N, c;
    cin >> N >> c;
    vector<lli> as(N);
    for (auto &x : as) cin >> x;
    int r = N;
    int ans = 0;
    while (r > 0) {
        int i = 0;
        while (i < N && as[i] > c) i++;
        if (i == N) {
            ans += r;
            r = 0;
        } else {
            int curmax = as[i];
            int maxi = i;
            while (i < N) {
                if (as[i] <= c) {
                    if (as[i] > curmax) {
                        maxi = i;
                        curmax = as[maxi];
                    }
                }
                i++;
            }
            // cout << maxi << endl;
            r -= 1;
            as[maxi] = 1e9 + 7;
            for (auto &x : as) if (x != 1e9 + 7) x *= 2;
        }
    }
    cout << ans << '\n';
}
 
int main() {
    fastio;
    int T; cin >> T;
    while(T--) solve();
    return 0;
}