/*
 * Submission ID: 14732238
 * Problem: Grundy's Game
 * Link: https://cses.fi/problemset/task/2207
 */

#pragma GCC optimize("Ofast")
#include <iostream>
#include <map>
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

vector<lli> G(1000006, -1);

constexpr int INF = 1e9 + 7;

int get_mex(vector<int> &nums) {
    map<int, bool> mp;
    for (const auto &x : nums) mp[x] = 1;
    lli res = 0;
    while (mp[res]) res++;
    return res;
}

int get_G(int x) {
    if (x >= 3000) return INF;
    if (G[x] != -1) return G[x];
    vector<int> nums;
    for (int i = 1; i < (x+1) / 2; i++) {
        nums.eb(get_G(i)^get_G(x-i));
    }
    G[x] = get_mex(nums);
    return G[x];
}

void solve() {
    int N; cin >> N;
    if (get_G(N) > 0) {
        cout << "first\n";
    } else {
        cout << "second\n";
    }
}

int main() {
    fastio;
    G[1] = G[2] = 0;
    // cerr << get_G(4) << endl;
    int T; cin >> T;
    while (T--) solve();
    return 0;
}