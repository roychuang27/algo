/*
 * Submission ID: 15700314
 * Problem: Road Reparation
 * Link: https://cses.fi/problemset/task/1675
 */

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
        DSU *dsu;
        vector<vector<pair<int, lli>>> adj;
        vector<bool> visited;
 
        GRAPH(int n, int m): N(n), M(m) {
                components = N;
                dsu = new DSU(N);
                adj = vector<vector<pair<int, lli>>> (N + 1);
                visited = vector<bool> (N + 1, 0);
        }
 
        void add_edge(int &u, int &v, lli &w) {
                adj[u].eb(v, w);
                adj[v].eb(u, w);
        }
 
        void find_minimum_spanning_tree() {
                lli cost = 0;
                priority_queue<tuple<lli, int, int>> pq;
                pq.push({0, 1, 0});
 
                while (!pq.empty()) {
                        const auto [w, cur, parent] = pq.top();
                        pq.pop();
                        if (visited[cur])
                                continue;
                        visited[cur] = 1;
                        
                        if (dsu->same_component(cur, parent))
                                continue;
 
                        dsu->unite(cur, parent);
                        cost -= w;
                        components--;
                        
                        for (const auto &[nxt, nw] : adj[cur]) if (!visited[nxt]) {
                                pq.push({-nw, nxt, cur});
                        }
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