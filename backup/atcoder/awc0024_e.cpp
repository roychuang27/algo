#include <algorithm>
#include <iostream>
#include <vector>
#define test(x) cerr << "Line(" << __LINE__ << ") " #x << ' ' << x << endl
#define SQ(x) ((x) * (x))
#define SZ(x) ((int)x.size())
#define eb emplace_back
#define ALL(x) x.begin(), x.end()
#define rALL(x) x.begin(), x.end()

using namespace std;
using lli = long long int;

const int INF = 0x3f3f3f3f;

void solution() {
        int N, W; cin >> N >> W;
        vector<int> L(N), C(N);
        for (int i = 0; i < N; i++) cin >> L[i] >> C[i];
        vector<int> dp(W+1, INF);
        dp[0] = 0;
        for (int i = 0; i < N; i++) {
                int cnt = C[i];
                for (int k = 1; cnt > 0; k <<= 1) {
                        int t = min(k, cnt);
                        cnt -= t;
                        int s = L[i] * t;
                        for (int j = W; j >= s; j--) {
                                dp[j] = min(dp[j-s] + t, dp[j]);
                        }
                }
                // for (int k = 1; k <= C[i]; k++) for (int j = W; j >= L[i]; j--) dp[j] = min(dp[j], dp[j-L[i]]+1);
        }
        if (dp[W] == INF) {
                cout << -1 << '\n';
        } else {
                cout << dp[W] << '\n';
        }
}

int32_t main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
