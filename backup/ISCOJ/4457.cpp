#pragma GCC optimize("Ofast")
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

constexpr lli INF = 1e18;
constexpr int MOD = 998244353;

vector<lli> dijkstra(vector<vector<pair<int, lli>>>& adj, int N, int from) {
        vector<lli> dist(N + 1, INF);
        vector<bool> visited(N + 1, 0);
        dist[from] = 0;
        priority_queue<pair<lli, int>, vector<pair<lli, int>>,
                       greater<pair<lli, int>>>
            pq;
        pq.push({0, from});

        while (!pq.empty()) {
                auto [_, cur] = pq.top();
                pq.pop();
                if (visited[cur]) continue;
                visited[cur] = 1;

                for (auto& [nxt, weight] : adj[cur]) {
                        if (dist[nxt] > dist[cur] + weight) {
                                dist[nxt] = dist[cur] + weight;
                                pq.push({dist[nxt], nxt});
                        }
                }
        }

        return dist;
}

void solve() {
        int N, M;
        cin >> N >> M;
        vector<vector<pair<int, lli>>> adj(N + 1);
        for (int i = 0; i < M; i++) {
                int a, b;
                lli c;
                cin >> a >> b >> c;
                adj[a].push_back({b, c});
        }

        lli ans = 0;
        
        for (int i = 1; i <= N; i++) {
                auto dist = dijkstra(adj, N, i);
                for (int j = 1; j <= N; j++) {
                        if (dist[j] == INF) ans += MOD - 1;
                        else ans += dist[j];
                        
                        if (ans >= MOD) ans %= MOD;
                }
        }
        
        cout << ans << '\n';
}

int main() {
        fastio;
        solve();
        return 0;
}