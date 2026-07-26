#include <atcoder/modint>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
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
using i128 = __int128;

constexpr int digits = 20;
i128 pow10[digits];

using mint = atcoder::modint998244353;

void preprocess() {
        pow10[0] = 1;
        for (int i = 1; i < digits; i++) pow10[i] = pow10[i-1] * 10;
}

void solution() {
        lli N, M;
        cin >> N >> M;
        mint ans = 0;

        for (int i = 1; i < digits; i++) {
                i128 lb_y = pow10[i-1];
                i128 ub_y = min(pow10[i] - 1, (i128)N);
                if (lb_y > ub_y) break;

                lli g = gcd(pow10[i]-1, M);
                ans += (mint(ub_y - lb_y + 1) * mint(N / (M / g)));
        }

        cout << ans.val() << '\n';
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        preprocess();
        int T;
        cin >> T;
        while(T--)
                solution();
        return 0;
}
