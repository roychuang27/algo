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

constexpr int MOD = 1e9 + 7;

class GRAPH {
        public:
        vector<vector<int>> adj;
        vector<int> state;
        vector<int> topo_sort;
        vector<lli> dp;
        bool cycle = 0;
        bool have_topo_sort = 1;
        int N, M;

        GRAPH(int n, int m) : N(n), M(m) {
                N = n;
                M = m;
                adj.resize(N+1);
                state = vector<int> (N+1, 0);
                dp = vector<lli> (N+1, 0);
        }

        void add_edge(int u, int v) {
                adj[u].eb(v);
        }

        void dfs_find_topo_sort (int cur) {
                if (state[cur] == 1) {
                        cycle = 1;
                        return;
                }
                if (state[cur] == 2) return;
                state[cur] = 1;

                for (const auto &nxt : adj[cur]) {
                        dfs_find_topo_sort(nxt);
                }

                topo_sort.eb(cur);
                state[cur] = 2;
        }

        void gen_topo_sort() {
                for (int i = 1; i <= N and !cycle; i++) {
                        if (state[i] == 0) {
                                dfs_find_topo_sort(i);
                        }
                }

                if (cycle or SZ(topo_sort) < N) {
                        have_topo_sort = 0;
                        topo_sort = {};
                } else {
                        reverse(ALL(topo_sort));
                }
        }

        int find_routes() {
                gen_topo_sort();
                dp[1] = 1;

                for (const int &cur : topo_sort) {
                        for (const int &nxt : adj[cur]) {
                                dp[nxt] = (dp[nxt] + dp[cur]) % MOD;
                        }
                }

                return dp[N] % MOD;
        }
};

void solve() {
        int N, M;
        cin >> N >> M;

        GRAPH g(N, M);
        for (int i = 0; i < M; i++) {
                int u, v; cin >> u >> v;
                g.add_edge(u, v);
        }

        cout << g.find_routes() << '\n';
}

int main() {
        fastio;
        solve();
        return 0;
}