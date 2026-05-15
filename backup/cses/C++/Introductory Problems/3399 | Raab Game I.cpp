/*
 * Submission ID: 14419668
 * Problem: Raab Game I
 * Link: https://cses.fi/problemset/task/3399
 */

#pragma GCC optimize("Ofast")
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
    int n, a, b;
    cin >> n >> a >> b;
    if ((n-a-b) < 0 or (a == 0 and b > 0) or (a > 0 and b == 0)) {
        cout << "NO\n";
        return;
    }
    int tie = (n - a - b);
    cout << "YES\n";
    vector<int> play_a, play_b;
    for (int k = n; k > n - tie; k--) {
        play_a.eb(k);
        play_b.eb(k);
    }
    // play_a.eb(-1);
    // play_b.eb(-1);
    int a_cur = b + 1;
    int b_cur = 1;
    for (int k = n - tie; k > 0; k--) {
        play_a.eb(a_cur);
        play_b.eb(b_cur);
        a_cur++;
        if (a_cur > (n - tie)) a_cur = 1;
        b_cur++;
        if (b_cur > (n - tie)) b_cur = 1;
    }
    printv(play_a);
    printv(play_b);
}

int main() {
    fastio;
    int t; cin >> t;
    while(t--) solve();
    return 0;
}