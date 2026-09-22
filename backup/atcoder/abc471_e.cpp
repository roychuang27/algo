#include <bits/stdc++.h>
#include <atcoder/modint.hpp>
#include <cassert>
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

using mint = atcoder::modint998244353;

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);

        int N, K;
        cin >> N >> K;
        vector<lli> A(N);
        mint sum = 0;
        for (auto &i : A) {
                cin >> i;
                sum += i;
        }

        vector<mint> frac(N+1);
        frac[0] = 1;
        for (int i = 1; i <= N; i++) frac[i] = frac[i-1] * i;

        auto C = [&](int m, int n) -> mint {
                assert(m >= n);
                if (n < 0) return 0;
                return frac[m] / frac[n] / frac[m-n];
        };

        mint ans = 0;

        for (auto i : A) {
                ans += i * i * C(N-1, K-1);
                ans += i * (sum - i) * C(N-2, K-2);
        }

        cout << ans.val() << '\n';
        
        return 0;
}

