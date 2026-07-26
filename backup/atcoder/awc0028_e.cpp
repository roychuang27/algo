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

constexpr int MOD = 1e9 + 7;

void solution() {
        int N, K; cin >> N >> K;
        vector<int> A(N+1), P(K+1);
        for (int i = 1; i <= N; i++) cin >> A[i];
        for (int i = 1; i <= K; i++) cin >> P[i];
        vector<int> dp(K+1);
        dp[0] = 1;
        for (int i = 1; i <= N; i++) {
                for (int j = K; j >= 1; j--) {
                        if (A[i] == P[j]) {
                                dp[j] += dp[j-1];
                                if (dp[j] >= MOD) dp[j] %= MOD;
                        }
                }
        }
        cout << dp[K] << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
