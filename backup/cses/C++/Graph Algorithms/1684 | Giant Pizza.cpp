#include <algorithm>
#include <iostream>
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

class GRAPH {
        public:
        int N, M;
        vector<vector<int>> adj;
        vector<vector<int>> adj_reversed;
        vector<int> dfs_post_order;
        vector<bool> visited;
        vector<int> scc;
        vector<bool> val;
        int components = 0;

        GRAPH(int n, int m): N(n), M(m) {
                adj.resize(N+1);
                adj_reversed.resize(N+1);
                visited.resize(N+1);
                scc.resize(N+1);
                val.resize(N/2+1);
        }

        void add_edge(int u, int v) {
                adj[u].eb(v);
                adj_reversed[v].eb(u);
        }

        void dfs_find_order(int cur) {
                if (visited[cur])
                        return;
                visited[cur] = 1;

                for (const auto &nxt : adj[cur]) {
                        dfs_find_order(nxt);
                }

                dfs_post_order.eb(cur);
        }

        void sfd_find_scc(int cur, int scc_id) {
                if (visited[cur])
                        return;
                visited[cur] = 1;
                scc[cur] = scc_id;

                for (const auto &nxt : adj_reversed[cur]) {
                        sfd_find_scc(nxt, scc_id);
                }
        }

        void find_scc() {
                fill(ALL(visited), 0);
                for (int i = 1; i <= N; i++) if (!visited[i]) {
                        dfs_find_order(i);
                }

                reverse(ALL(dfs_post_order));
                fill(ALL(visited), 0);
                for (const auto &i : dfs_post_order) if (!visited[i]) {
                        components++;
                        sfd_find_scc(i, components);
                }
        }

        bool in_same_scc(int u, int v) {
                return scc[u] == scc[v];
        }

        void print_all_scc() {
                cout << components << '\n';
                for (int i = 1; i <= N; i++) {
                        cout << scc[i] << " \n"[i==N];
                }
        }

        void print_2sat() {
                for (int i = 1; i <= N / 2; i++) {
                        int x = 2 * i - 1;
                        int not_x = 2 * i;
                        if (in_same_scc(x, not_x)) {
                                cout << "IMPOSSIBLE\n";
                                return;
                        }

                        if (scc[x] > scc[not_x]) {
                                val[i] = 1;
                        } else {
                                val[i] = 0;
                        }
                }

                for (int i = 1; i <= N / 2; i++) {
                        cout << (val[i]?'+':'-') << ' ';
                }
                cout << '\n';
        }

};

void solve() {
        int N, M;
        cin >> M >> N;

        GRAPH g(2*N, M);

        for (int i = 0; i < M; i++) {
                char a, b;
                int u, v;
                cin >> a >> u >> b >> v;

                if (a == '+') {
                        if (b == '+') {  // +u +v
                                g.add_edge(2*u, 2*v-1);      // -u -> +v
                                g.add_edge(2*v, 2*u-1);      // -v -> +u
                        } else {        // +u -v
                                g.add_edge(2*u, 2*v);        // -u -> -v
                                g.add_edge(2*v-1, 2*u-1);    // +v -> +u
                        }
                } else {
                        if (b == '+') {  // -u +v
                                g.add_edge(2*u-1, 2*v-1);    // +u -> +v
                                g.add_edge(2*v, 2*u);        // -v -> -u
                        } else {         // -u -v
                                g.add_edge(2*u-1, 2*v);      // +u -> -v
                                g.add_edge(2*v-1, 2*u);      // +v -> -u
                        }
                }
        }

        g.find_scc();

        // for (int i = 1; i <= 2*N; i++) {
        //         for (auto &j : g.adj[i]) cout << (j%2?j/2+1:-j/2) << ' ';
        //         cout << endl;
        // }

        // g.print_all_scc();

        g.print_2sat();
}

int main() {
        fastio;
        solve();
        return 0;
}