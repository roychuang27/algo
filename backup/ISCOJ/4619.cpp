#include <functional>
#include <iostream>
#include <queue>
#include <vector>
#ifdef LOCAL
#define test(...) do { cerr << "Line(" << __LINE__ << ") [" #__VA_ARGS__ "] =>"; ([](auto&&... args){ ((cerr << ' ' << args), ...); }(__VA_ARGS__)); cerr << endl; } while(0)
#define testv(x) do { cerr << "Line(" << __LINE__ << ") " #x " => ["; int _i=0; for (auto& _e : (x)) cerr << (_i++ ? ", " : "") << _e; cerr << "]" << endl; } while(0)
#else
#define test(...) 0
#define testv(...) 0
#endif
#define printv(x) { for (auto i : (x)) cout << i << ' '; cout << endl; }
#define printlnv(x) { for (auto i : (x)) cout << i << '\n'; }
#define SQ(x) ((x) * (x))
#define SZ(x) ((int)x.size())
#define eb emplace_back
#define ALL(x) begin(x), end(x)
#define rALL(x) rbegin(x), rend(x)
#define CORDCOMP(x, fx) sort(ALL(x)); x.erase(unique(ALL(x)), end(x)); const auto fx = [&](int val) -> int { return lower_bound(ALL(x), val) - begin(x); }

using namespace std;
using lli = long long int;

void solution() {
        int N, M;
        cin >> N >> M;

        vector<vector<int>> al(N+1);
        for (int _ = 0; _ < M; _++) {
                int u, v;
                cin >> u >> v;
                al[u].emplace_back(v);
                al[v].emplace_back(u);
        }

        const auto bfs = [&](int origin) -> lli {
                queue<pair<int, int>> qu;
                vector<bool> visited(N+1, 0);
                lli ans = 0;
                qu.emplace(origin, 0);
                visited[origin] = 1;
                while (!qu.empty()) {
                        const auto [cur, dist] = qu.front();
                        qu.pop();
                        ans += dist;
                        for (const auto &nxt : al[cur]) {
                                if (!visited[nxt]) {
                                        qu.emplace(nxt, dist+1);
                                        visited[nxt] = 1;
                                }
                        }
                }
                return ans;
        };
        for (int i = 1; i <= N; i++) {
                cout << bfs(i) << " \n"[i==N];
        }
}

int main() {
        ios_base::sync_with_stdio(false); cin.tie(nullptr);
        solution();
        return 0;
}
