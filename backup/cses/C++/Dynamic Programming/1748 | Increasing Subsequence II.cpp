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

constexpr int mod = 1e9 + 7;

int lowbit(int k) {
    return k & -k;
}

void update(vector<lli> &fenwick, int N, int pos, int val) {
    while (pos <= N) {
        fenwick[pos] = (fenwick[pos] +  val) % mod;
        pos += lowbit(pos);
    }
}

lli query(vector<lli> &fenwick, int pos) {
    lli res = 0;
    while (pos >= 1) {
        res = (res + fenwick[pos]) % mod;
        pos -= lowbit(pos);
    }
    return res;
}

lli ans = 0;

void solve() {
    int N; cin >> N;
    map<int, int> mp;
    vector<int> xs(N);
    for (int i = 0; i < N; i++) {
        cin >> xs[i];
        mp[xs[i]];
    }
    int order = 0;
    for (auto &p : mp) {
        p.second = ++order;
    }
    for (int i = 0; i < N; i++) {
        xs[i] = mp[xs[i]];
    }
    // printv(xs);
    vector<lli> fenwick(N + 5, 0);
    // dp
    for (int i = 0; i < N; i++) {
        lli pre = query(fenwick, xs[i] - 1);
        ans += (pre + 1);
        update(fenwick, N, xs[i], pre + 1);
    }
    cout << ans % mod << '\n';
}

int main() {
    fastio;
    solve();
    return 0;
}