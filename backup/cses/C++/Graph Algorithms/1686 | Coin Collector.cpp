/*
 * Submission ID: 14839743
 * Problem: Coin Collector
 * Link: https://cses.fi/problemset/task/1686
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
        vector<vector<int>> adj_scc;
        vector<lli> val_each_scc;
        int scc_cnt = 0;
        lli max_val = 0;
        vector<lli> dp;
 
        GRAPH(int n, int m): N(n), M(m) {
                adj.resize(N+1);
                adj_reversed.resize(N+1);
                visited.resize(N+1);
                scc.resize(N+1);
        }

        void reset_visited_arr() {
                fill(ALL(visited), 0);
        }
 
        void add_directed_edge(int &u, int &v) {
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
                reset_visited_arr();
                for (int i = 1; i <= N; i++) if (!visited[i]) {
                        dfs_find_order(i);
                }
 
                reverse(ALL(dfs_post_order));
                reset_visited_arr();
                for (const auto &i : dfs_post_order) if (!visited[i]) {
                        scc_cnt++;
                        sfd_find_scc(i, scc_cnt);
                }
        }
 
        bool in_same_scc(int u, int v) {
                return scc[u] == scc[v];
        }
 
        void print_all_scc() {
                cout << scc_cnt << '\n';
                for (int i = 1; i <= N; i++) {
                        cout << scc[i] << " \n"[i==N];
                }
        }

        void build_scc_graph(vector<lli> &val_each_node) {
                adj_scc.resize(scc_cnt+1);
                val_each_scc = vector<lli> (scc_cnt+1, 0);
                dp = vector<lli> (scc_cnt+1, 0);

                for (int i = 1; i <= N; i++) {
                        val_each_scc[scc[i]] += val_each_node[i];

                        for (const auto &nxt : adj[i]) {
                                if (scc[nxt] != scc[i]) {
                                        adj_scc[scc[i]].eb(scc[nxt]);
                                }
                        }
                }
        }

        void dfs_solve(int cur) {
                if (visited[cur])
                        return;
                visited[cur] = 1;

                for (const auto &nxt : adj_scc[cur]) {
                        dfs_solve(nxt);
                        dp[cur] = max(dp[cur], dp[nxt]);
                }
                dp[cur] += val_each_scc[cur];

                max_val = max(dp[cur], max_val);
        }

        void solve() {
                reset_visited_arr();
                for (int i = 1; i <= scc_cnt; i++) {
                        if (!visited[i]) {
                                dfs_solve(i);
                        }
                }
        }

};
 
void solve() {
        int N, M;
        cin >> N >> M;

        vector<lli> val_each_node(N+1);

        for (int i = 1; i <= N; i++)
                cin >> val_each_node[i];
 
        GRAPH g(N, M);
        for (int i = 0; i < M; i++) {
                int u, v;
                cin >> u >> v;
                g.add_directed_edge(u, v);
        }
 
        g.find_scc();
        g.build_scc_graph(val_each_node);
        g.solve();

        cout << g.max_val << '\n';
}
 
int main() {
        fastio;
        solve();
        return 0;
}