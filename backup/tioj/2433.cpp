#include <bits/stdc++.h>
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
        int N, K, Q;
        cin >> N >> K >> Q;
        vector<vector<int>> adj(N+1);
        vector<int> C(N+1);
        C[0] = 0;
        for (int i = 1; i <= N; i++) {
                cin >> C[i];
        }
        for (int _ = 0; _ < N-1; _++) {
                int u, v;
                cin >> u >> v;
                adj[u].emplace_back(v);
                adj[v].emplace_back(u);
        }
        vector<map<int, int>> cnt_by_color(N+1);
        vector<int> cnt_son(N+1, 0), par(N+1);
        const auto dfs = [&](auto &&self, int cur, int parent) -> void {
                par[cur] = parent;
                for (auto &nxt : adj[cur]) if (nxt != parent) {
                        cnt_son[cur]++;
                        cnt_by_color[cur][C[nxt]]++;
                        self(self, nxt, cur);
                }
        };
        dfs(dfs, 1, 0);

        int ans = (C[1] == 0 ? 0 : 1);
        for (int i = 1; i <= N; i++) {
                for (auto &[key, value] : cnt_by_color[i]) {
                        if (key != C[i]) {
                                ans += value;
                        }
                }
        }

        for (int _ = 0; _ < Q; _++) {
                int w, x;
                cin >> w >> x;
                ans -= (C[par[w]] != C[w]);
                ans -= (cnt_son[w] - cnt_by_color[w][C[w]]);
                cnt_by_color[par[w]][C[w]]--;
                C[w] = x;
                cnt_by_color[par[w]][C[w]]++;
                ans += (C[par[w]] != C[w]);
                ans += (cnt_son[w] - cnt_by_color[w][C[w]]);
                cout << ans << '\n';
        }
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        solution();
        return 0;
}
