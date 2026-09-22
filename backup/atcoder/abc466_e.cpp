#include <bits/stdc++.h>
#include <algorithm>
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

int main() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
        int N, K;
        cin >> N >> K;
        vector<lli> A(N), B(N);
        for (int i = 0; i < N; i++) cin >> A[i] >> B[i];
        vector<lli> dp(2*K+1, -1);
        dp[0] = 0;
        for (int i = 0; i < N; i++) {
                for (int j = 2*K; j > 0; j--) {
                        if (dp[j-1] != -1) {
                                if (dp[j] == -1) dp[j] = 0;
                                if (j % 2) {
                                        dp[j] = max(dp[j-1]+B[i], dp[j]+B[i]);
                                } else {
                                        dp[j] = max(dp[j-1]+A[i], dp[j]+A[i]);
                                }
                        }
                }
                dp[0] += A[i];
                testv(dp);
        }
        cout << *max_element(ALL(dp)) << '\n';
        return 0;
}

