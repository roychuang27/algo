/*
 * Submission ID: 14820167
 * Problem: Planets and Kingdoms
 * Link: https://cses.fi/problemset/task/1683
 */

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
        int components = 0;

        GRAPH(int n, int m): N(n), M(m) {
                adj.resize(N+1);
                adj_reversed.resize(N+1);
                visited.resize(N+1);
                scc.resize(N+1);
        }

        void add_edge(int &u, int &v) {
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

};

void solve() {
        int N, M;
        cin >> N >> M;

        GRAPH g(N, M);
        for (int i = 0; i < M; i++) {
                int u, v;
                cin >> u >> v;
                g.add_edge(u, v);
        }

        g.find_scc();
        g.print_all_scc();
}

int main() {
        fastio;
        solve();
        return 0;
}