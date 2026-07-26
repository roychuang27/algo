#include <cmath>
#include <functional>
#include <iostream>
#include <vector>
#define test(x) cerr << "Line(" << __LINE__ << ") " #x << ' ' << x << endl
#define printv(x)                          \
{                                          \
        for (auto i : x) cout << i << ' '; \
        cout << endl;                      \
}
#define SQ(x) ((x) * (x))
#define SZ(x) ((int)x.size())
#define eb emplace_back
#define ALL(x) x.begin(), x.end()
#define rALL(x) x.begin(), x.end()

using namespace std;
using lli = long long int;

constexpr lli INF = 1e18;

void solution() {
        int N; cin >> N;
        vector<lli> P(N), W(N-1);
        for (auto &x : P) cin >> x;
        for (auto &x : W) cin >> x;
        vector<vector<lli>> dp(1<<N, vector<lli> (N, -INF));
        for (int i = 0; i < N; i++) dp[1<<i][i] = 0;
        const function<lli(int, int)> treeman = [&](int mask, int j) -> lli {
                if (not (mask & (1 << j))) return -INF;
                if (dp[mask][j] != -INF) return dp[mask][j];
                for (int i = 0; i < N; i++) {
                        if (not (mask & (1 << i))) continue;
                        if (not (mask & (1 << j))) continue;
                        if (i == j) continue;
                        int mask2 = mask ^ (1 << j);
                        int k = __builtin_popcount(mask2) - 1;
                        dp[mask][j] = max(treeman(mask2, i) + W[k] * llabs(P[j] - P[i]), dp[mask][j]);
                }
                return dp[mask][j];
        };
        lli ans = 0;
        for (int i = 0; i < N; i++) ans = max(treeman((1<<N)-1, i), ans);
        cout << ans << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
