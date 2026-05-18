#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
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
constexpr lli INF = 1e18;

class GRAPH {
        public:
        vector<vector<pair<int, lli>>> adj;
        vector<lli> price;
        vector<lli> ways;
        vector<int> dist_min, dist_max;
        vector<bool> visited;
        bool cycle = 0;
        bool have_topo_sort = 1;
        int N, M;

        GRAPH(int n, int m) : N(n), M(m) {
                N = n;
                M = m;
                adj.resize(N + 1);
                price = vector<lli> (N+1, INF);
                visited = vector<bool> (N+1, 0);
                ways.resize(N+1);
                dist_min.resize(N+1);
                dist_max.resize(N+1); 
        }

        void add_edge(int u, int v, int w) {
                adj[u].eb(v, w);
        }

        void dijkstra() {
                price[1] = 0;
                ways[1] = 1;
                dist_min[1] = 0;
                dist_max[1] = 0;

                priority_queue<pair<lli, int>> pq;
                pq.emplace(0, 1);

                while (!pq.empty()) {
                        const auto [_, cur] = pq.top();
                        pq.pop();
                        if (visited[cur]) continue;
                        visited[cur] = 1;
                        
                        for (const auto &[nxt, w] : adj[cur]) {
                                if (price[nxt] == price[cur] + w) {
                                        ways[nxt] = (ways[nxt] + ways[cur]) % MOD;
                                        dist_max[nxt] = max(dist_max[cur] + 1, dist_max[nxt]);
                                        dist_min[nxt] = min(dist_min[cur] + 1, dist_min[nxt]);
                                } else if (price[nxt] >  price[cur] + w) {
                                        price[nxt] = price[cur] + w;
                                        ways[nxt] = ways[cur];
                                        dist_max[nxt] = dist_max[cur] + 1;
                                        dist_min[nxt] = dist_min[cur] + 1;
                                        pq.emplace(-price[nxt], nxt);
                                }
                        }
                }
        }

        void solve() {
                dijkstra();
                cout << price[N] << ' ' << ways[N] << ' ' << dist_min[N] << ' ' << dist_max[N] << '\n';
        }
};

void solve() {
        int N, M;
        cin >> N >> M;

        GRAPH g(N, M);
        for (int i = 0; i < M; i++) {
                int u, v, w;
                cin >> u >> v >> w;
                g.add_edge(u, v, w);
        }

        g.solve();
}

int main() {
        fastio;
        solve();
        return 0;
}