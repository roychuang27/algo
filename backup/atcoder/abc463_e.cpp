#include <pthread.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
#ifdef LOCAL
#define test(...) do { std::cerr << "Line(" << __LINE__ << ") [" #__VA_ARGS__ "] =>"; ([](auto&&... args){ ((std::cerr << ' ' << args), ...); }(__VA_ARGS__)); std::cerr << std::endl; } while(0)
#define testv(x) do { std::cerr << "Line(" << __LINE__ << ") " #x " => ["; int _i=0; for (auto& _e : (x)) std::cerr << (_i++ ? ", " : "") << _e; std::cerr << "]" << std::endl; } while(0)
#else
#define test(...) 0
#define testv(...) 0
#endif
#define ALL(x) std::begin(x), std::end(x)
#define rALL(x) std::rbegin(x), std::rend(x)
#define SZ(x) ((int) x.size())
#define SQ(x) ((x) * (x))
#define CORDCOMP(x, fx) std::sort(ALL(x)); x.erase(std::unique(ALL(x)), std::end(x)); const auto fx = [&](int val) -> int { return std::lower_bound(ALL(x), val) - std::begin(x); }
#define fst first
#define sec second

using lli = long long int;
using namespace std;

void solution() {
        int N, M;
        lli Y;
        cin >> N >> M >> Y;
        vector<vector<pair<int, lli>>> adj(N+3);
        for (int _ = 0; _ < M; _++) {
                int u, v, t;
                cin >> u >> v >> t;
                adj[u].emplace_back(v, t);
                adj[v].emplace_back(u, t);
        }
        for (int i = 1; i <= N; i++) {
                int x;
                cin >> x;
                adj[i].emplace_back(N+1, x);
                adj[N+2].emplace_back(i, x);
        }
        adj[N+1].emplace_back(N+2, Y);

        vector<lli> dist(N+3, 1e18);
        priority_queue<pair<lli, int>> pq;
        pq.push({0, 1});
        while (!pq.empty()) {
                const auto [d, cur] = pq.top();
                pq.pop();

                if (dist[cur] <= -d) continue;
                dist[cur] = -d;

                for (auto &[nxt, w] : adj[cur]) {
                        pq.push({d - w, nxt});
                }
        }

        for (int i = 2; i <= N; i++) cout << dist[i] << ' ';
        cout << '\n';
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        solution();
        return 0;
}
