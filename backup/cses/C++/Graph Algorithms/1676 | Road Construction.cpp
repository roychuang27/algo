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

struct DSU {
    vector<int> root;
    vector<int> component_sz;
    int N, maxSZ;
    int cnt;
 
    void init (int n) {
        N = n;
        cnt = N;
        root.resize(n+1);
        component_sz.resize(n+1);
        for (int i = 1; i <= n; i++) root[i] = i;
        for (int i = 1; i <= n; i++) component_sz[i] = 1;
    }
 
    void unite (int a, int b) {
        // find roots
        a = find_root(a);
        b = find_root(b);
        if (a == b) return;
        root[b] = a; // merge root
        component_sz[a] += component_sz[b];
        maxSZ = max(maxSZ, component_sz[a]);
        cnt -= 1;
    }
 
    int find_root (int x) {
        if (root[x] == x) return x;
        root[x] = find_root(root[x]); // pre save the roots
        return root[x];
    }
 
};

void solve() {
    int N, M;
    cin >> N >> M;
    DSU dsu;
    dsu.init(N);
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        dsu.unite(a, b);
        cout << dsu.cnt << ' ' << dsu.maxSZ << '\n';
    }
}

int main() {
    fastio;
    solve();
    return 0;
}