#pragma GCC optimize("Ofast")
#include <iostream>
#include <vector>
#include <map>
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

constexpr lli mod = 1e9 +7;

void solve() {
    map<int, int> freq;
    int N; cin >> N;
    vector<int> xs(N);
    for (int i = 0; i < N; i++) {
        cin >> xs[i];
        freq[xs[i]]++;
    }
    lli ans = 1;
    for (auto p : freq) {
        ans *= (p.second + 1);
        if (ans >= mod) ans %= mod;
    }
    ans -= 1;
    if (ans < 0) ans += mod;
    cout << ans << '\n';
}

int main() {
    fastio;
    solve();
    return 0;
}