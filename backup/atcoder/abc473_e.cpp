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

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        int N, K;
        cin >> N >> K;
        vector<lli> S(N+1, 0);
        for (int i = 1; i <= N; i++) {
                int a;
                cin >> a;
                S[i] = (S[i-1] + a) % K;
        }
        map<int, int> mp;
        mp[0] = 0;
        vector<int> dp(N+1, 0);
        for (int i = 1; i <= N; i++) {
                dp[i] = dp[i-1];
                if (mp.contains(S[i])) {
                        dp[i] = max(mp[S[i]] + 1, dp[i]);
                }
                mp[S[i]] = dp[i];
        }
        cout << dp[N] << '\n';
        return 0;
}
