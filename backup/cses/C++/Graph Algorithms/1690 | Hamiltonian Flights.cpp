/*
 * Submission ID: 17171901
 * Problem: Hamiltonian Flights
 * Link: https://cses.fi/problemset/task/1690
 */

#include <functional>
#include <iostream>
#include <vector>
#ifdef LOCAL
#define test(...) do { std::cerr << "Line(" << __LINE__ << ") [" #__VA_ARGS__ "] =>"; ([](auto&&... args){ ((std::cerr << ' ' << args), ...); }(__VA_ARGS__)); std::cerr << std::endl; } while(0)
#define testv(x) do { std::cerr << "Line(" << __LINE__ << ") " #x " => ["; int _i=0; for (auto& _e : (x)) std::cerr << (_i++ ? ", " : "") << _e; std::cerr << "]" << std::endl; } while(0)
#else
#define test(...) 0
#define testv(...) 0
#endif
#define SQ(x) ((x) * (x))
#define CORDCOMP(x, fx) std::sort(ALL(x)); x.erase(std::unique(ALL(x)), std::end(x)); const auto fx = [&](int val) -> int { return std::lower_bound(ALL(x), val) - std::begin(x); }
#define fst first
#define sec second

using lli = long long int;
using namespace std;

constexpr int MOD = 1e9 + 7;

void solution() {
        int N, M;
        cin >> N >> M;

        vector<vector<int>> adj(N);
        for (int _ = 0; _ < M; _++) {
                int u, v;
                cin >> u >> v;
                adj[v-1].emplace_back(u-1);
        }

        vector<vector<int>> dp(N, vector<int> (1 << N, -1));

        const auto f = [&](auto &&self, int mask, int dest) -> int {
                if (dest == 0) {
                        if (mask == 1) return 1;
                        else return 0;
                }
                if (!(mask & (1 << dest))) return 0;
                if (dp[dest][mask] != -1) return dp[dest][mask];

                int x = mask ^ (1 << dest);
                dp[dest][mask] = 0;
                for (auto &nxt : adj[dest]) {
                        dp[dest][mask] += self(self, x, nxt);
                        dp[dest][mask] %= MOD;
                }

                return dp[dest][mask];
        };

        cout << f(f, (1<<N)-1, N-1) << '\n';
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        solution();
        return 0;
}
