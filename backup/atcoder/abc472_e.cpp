#include <bits/stdc++.h>
#include <atcoder/dsu>
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

void solve() {
        int N, M;
        cin >> N >> M;
        vector<pair<int, int>> edges(M);
        for (auto &[a, b] : edges) {
                cin >> a >> b;
                a--;
                b--;
        }
        atcoder::dsu uf(N);
        vector<bool> color(N, 0);
        vector<vector<int>> adj(N);

        for (auto [a, b] : edges) {
                if (!uf.same(a, b)) {
                        adj[a].emplace_back(b);
                        adj[b].emplace_back(a);
                        uf.merge(a, b);
                }
        }

        auto dfs = [&](this auto &&self, int cur, int par) -> void {
                if (cur != 0) {
                        color[cur] = !color[par];
                }
                for (auto nxt : adj[cur]) if (nxt != par) {
                        self(nxt, cur);
                }
        };
        dfs(0, 0);

        auto find_path = [&](this auto &&self, int cur, int par, int target, int d) -> bool {
                if (cur == target) {
                        cout << d << '\n';
                        cout << cur + 1 << ' ';
                        return 1;
                }
                for (auto &nxt : adj[cur]) if (nxt != par) {
                        if (self(nxt, cur, target, d+1)) {
                                cout << cur + 1 << ' ';
                                return 1;
                        }
                }
                return 0;
        };

        for (auto [a, b] : edges) {
                if (color[a] == color[b]) {
                        find_path(a, -1, b, 1);
                        cout << '\n';
                        return;
                }
        }
        cout << "-1\n";
        return;
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        int T;
        cin >> T;
        while(T--) {
                solve();
        }
        return 0;
}
