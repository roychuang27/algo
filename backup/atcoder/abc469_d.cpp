#include <bits/stdc++.h>
#include <pthread.h>
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
        cin >> N >> M;
        vector<vector<int>> adj(N);
        vector<int> deg(N, 0), cnt(M+1, 0);
        cnt[0] = M;

        auto add = [&](int x, int v) -> void {
                cnt[deg[x]]--;
                deg[x] += v;
                cnt[deg[x]]++;
        };

        for (int _ = 0; _ < M; _++) {
                int u, v;
                cin >> u >> v;
                u--;
                v--;
                adj[u].emplace_back(v);
                adj[v].emplace_back(u);
                add(u, 1);
                add(v, 1);
        }

        lli ans = 0;
        for (int i = 0; i < N; i++) {
                int needed = M - adj[i].size();
                if (needed == 0) {
                        ans += N - 1;
                } else {
                        for (auto j : adj[i]) {
                               add(i, -1);
                               add(j, -1);
                        }
                        ans += cnt[needed];
                        for (auto j : adj[i]) {
                               add(i, 1);
                               add(j, 1);
                        }
                }
        }
        test(ans);
        cout << ans / 2 << '\n';
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        solution();
        return 0;
}
