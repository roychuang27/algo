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

int lowbit(int k) {
    return k & -k;
}

void update(vector<int> &fenwick, int N, int pos, int val) {
    while (pos <= N) {
        fenwick[pos] = (fenwick[pos] +  val);
        pos += lowbit(pos);
    }
}

int query(vector<int> &fenwick, int pos) {
    int res = 0;
    while (pos >= 1) {
        res = (res + fenwick[pos]);
        pos -= lowbit(pos);
    }
    return res;
}

int find_idx(vector<int> &fenwick, int k, int N) {
    int l = 1, r = N;
    while (l < r) {
        int m = (l + r) / 2;
        if (query(fenwick, m) < k) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return l;
}

void solve() {
    int N; cin >> N;
    vector<int> xs(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> xs[i];
    }
    vector<int> alive_prefix(2e5 + 10, 0);
    for (int i = 1; i <= N; i++) update(alive_prefix, N, i, 1);

    for (int q = 0; q < N; q++) {
        int k; cin >> k;
        // cerr << query(alive_prefix, N) << ' ';
        int idx = find_idx(alive_prefix, k, N);
        // cerr << query(alive_prefix, idx) << endl;
        cout << xs[idx] << ' ';
        update(alive_prefix, N, idx, -1);
        // for (int i = 1; i <= N; i++) cerr << query(alive_prefix, i) << ' ';
        // cerr << endl;
    }
}

int main() {
    fastio;
    solve();
    return 0;
}