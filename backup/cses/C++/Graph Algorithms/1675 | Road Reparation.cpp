#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#define fastio cin.tie(0)->sync_with_stdio(false)
#define eb emplace_back
#define test(x) cerr << "Line(" << __LINE__ << ") " #x << ' ' << x << endl
#define printv(x)                                  \
        {                                          \
                for (auto i : x) cout << i << ' '; \
                cout << endl;                      \
        }
#define pii pair<int, int>
#define pll pair<lli, lli>
#define ALL(x) x.begin(), x.end()
#define rALL(x) x.rbegin(), x.rend()
#define MP(x, y) make_pair((x), (y))
#define SQ(x) ((x) * (x))
#define SZ(x) ((int)x.size())
 
using namespace std;
typedef long long int lli;
 
template <typename A, typename B>
ostream& operator<<(ostream& o, pair<A, B> a) {
        return o << a.first << ' ' << a.second;
}
template <typename A, typename B>
istream& operator>>(istream& o, pair<A, B>& a) {
        return o >> a.first >> a.second;
}
 
class DSU {
        public:
        int N;
        vector<int> root;
 
        DSU(int n): N(n) {
                root.resize(N+1);
                for (int i = 1; i <= N; i++) {
                        root[i] = i;
                }
        }
 
        bool same_component(int a, int b) {
                return find_root(a) == find_root(b);
        }
 
        int find_root(int x) {
                if (root[x] == x)
                        return x;
                root[x] = find_root(root[x]);
                return root[x];
        }
 
        void unite(int a, int b) {
                a = find_root(a);
                b = find_root(b);
                root[b] = a;
        }
};
 
class GRAPH {
        public:
        int N, M;
        int components;
        DSU dsu;
        vector<tuple<int, int, lli>> edge_list;
 
        GRAPH(int n, int m):
                N(n),
                M(m),
                components(N),
                dsu(N),
                edge_list()
        {}
 
        void add_edge(int u, int v, lli w) {
                edge_list.eb(u, v, w);
                edge_list.eb(v, v, w);
        }
 
        void find_minimum_spanning_tree() {
                lli cost = 0;
                sort(ALL(edge_list), [](auto a, auto b) {
                        return get<2>(a) < get<2>(b);
                });
 
                for (const auto &[u, v, w] : edge_list) {
                        if (dsu.same_component(u, v))
                                continue;
 
                        dsu.unite(u, v);
                        cost += w;
                        components--;
                }
 
                if (components > 1) {
                        cout << "IMPOSSIBLE\n";
                } else {
                        cout << cost << '\n';
                }
        }
};
 
void solve() {
        int N, M;
        cin >> N >> M;
        GRAPH g(N, M);
 
        for (int i = 0; i < M; i++) {
                int u, v;
                lli w;
                cin >> u >> v >> w;
                g.add_edge(u, v, w);
        }
 
        g.find_minimum_spanning_tree();
}
 
int main() {
        fastio;
        solve();
        return 0;
}
