/*
 * Submission ID: 13128359
 * Problem: Hidden Integer
 * Link: https://cses.fi/problemset/task/3112
 */

#pragma GCC optimize("Ofast")
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

bool is_smaller(int y) {
    string s;
    cout << "? " << y << endl;
    cin >> s;
    return s == "YES";
}

void solve() {
    int l = 0, r = 1e9;
    while (l < r) {
        int mid = (l + r) / 2;
        if (is_smaller(mid)) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    cout << "! " << l << endl;
}

int main() {
    fastio;
    solve();
    return 0;
}