#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
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
        vector<int> depth;

        DSU(int n): N(n), root(n+1), depth(n+1, 1) {
                for (int i = 0; i <= N; i++) {
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
                if (depth[a] < depth[b]) swap(a, b);
                else if (depth[a] == depth[b]) depth[a]++;
                root[b] = a;
        }
};

struct edge {
        int u, v;
        lli w;
};

void solve() {
        // freopen("5.txt", "r", stdin);
        int N, M;
        cin >> N >> M;
        
        vector<edge> edges;

        for (int i = 0; i < M; i++) {
                int u, v;
                lli w;
                cin >> u >> v >> w;
                edges.eb(edge{u, v, w});
        }
        
        sort(ALL(edges), [&](auto &e1, auto &e2) {
                return e1.w < e2.w;
        });
        
        DSU dsu(N);
        int components = N;
        
        lli cost = 0;
        
        for (const auto &e : edges) {
                if (components <= 1) break;
                if (dsu.same_component(e.u, e.v)) continue;
                
                dsu.unite(e.u, e.v);
                components--;
                cost += e.w;
        }

        cout << cost << '\n';
}

int main() {
        fastio;
        solve();
        return 0;
}