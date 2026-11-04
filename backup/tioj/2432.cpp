#include <bits/stdc++.h>
#ifdef LOCAL
#define dbg(...) do { std::cerr << "Line(" << __LINE__ << ") [" #__VA_ARGS__ "] =>"; ([](auto&&... args){ ((std::cerr << ' ' << args), ...); }(__VA_ARGS__)); std::cerr << std::endl; } while(0)
#define dbgv(x) do { std::cerr << "Line(" << __LINE__ << ") " #x " => ["; int _i=0; for (auto& _e : (x)) std::cerr << (_i++ ? ", " : "") << _e; std::cerr << "]" << std::endl; } while(0)
#else
#define dbg(...) 39
#define dbgv(...) 39
#endif
#define ALL(x) std::begin(x), std::end(x)
#define rALL(x) std::rbegin(x), std::rend(x)
#define SZ(x) ((size_t) x.size())
#define SQ(x) ((x) * (x))
#define CORDCOMP(x, fx) std::sort(ALL(x)); x.erase(std::unique(ALL(x)), std::end(x)); const auto fx = [&](int val) -> int { return std::lower_bound(ALL(x), val) - std::begin(x); }
#define fst first
#define sec second

using lli = long long int;
using namespace std;

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);

        int N, K, M;
        cin >> N >> K >> M;
        vector C(N*K, vector<bool> (N*K, 0));
        vector A(N, vector<lli> (K));

        for (int i = 0; i < N; i++) {
                for (int j = 0; j < K; j++) {
                        cin >> A[i][j];
                }
        }

        for (int u, v, _ = 0; _ < M; _++) {
                cin >> u >> v;
                u--;
                v--;
                C[u][v] = 1;
        }

        vector<vector<int>> masks(K+1);
        for (int i = 1; i < (1 << K); i++) masks[__builtin_popcount(i)].emplace_back(i);

        vector dp(N, vector<lli> (1<<K, -1));
        for (int i = 1; i < (1 << K); i++) {
                dp[0][i] = 0;
                for (int j = 0; j < K; j++) if ((1 << j) & i) dp[0][i] += A[0][j];
        }
        for (int row = 1; row < N; row++) {
                vector have_perfect_match(1<<K, vector<bool> (1<<K, 0));
                have_perfect_match[0][0] = 1;
                for (int p = 1; p <= K; p++) {
                        for (auto i : masks[p]) {
                                for (auto j : masks[p]) {
                                        int u = __lg(i & -i);
                                        for (int v = 0; v < K; v++) if (j & (1 << v)) {
                                                if (C[u+(row-1)*K][v+row*K] and have_perfect_match[i^(1<<u)][j^(1<<v)]) {
                                                        have_perfect_match[i][j] = 1;
                                                        break;
                                                }
                                        }

                                        if (have_perfect_match[i][j]) {
                                                if (dp[row-1][i] == -1) continue;
                                                lli s = 0;
                                                for (int v = 0; v < K; v++) if ((1 << v) & j) s += A[row][v];
                                                dp[row][j] = max(dp[row][j], dp[row-1][i] + s);
                                        }
                                }
                        }
                }
        }

        for (auto v : dp) dbgv(v);
        for (int i = 1; i <= K; i++) {
                lli ans = -1;
                for (auto j : masks[i]) ans = max(dp[N-1][j], ans);
                cout << ans << ' ';
        }
        cout << '\n';

        return 0;
}
