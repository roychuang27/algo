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
#define SZ(x) ((int) x.size())
#define SQ(x) ((x) * (x))
#define CORDCOMP(x, fx) std::sort(ALL(x)); x.erase(std::unique(ALL(x)), std::end(x)); const auto fx = [&](int val) -> int { return std::lower_bound(ALL(x), val) - std::begin(x); }
#define fst first
#define sec second

using lli = long long int;
using namespace std;

void precompute() {
}

lli fpow(lli base, lli exp, lli mod) {
        lli res = 1;
        while (exp) {
                if (exp & 1) {
                        res *= base;
                        res %= mod;
                }
                base *= base;
                base %= mod;
                exp >>= 1;
        }
        return res;
}

void solve() {
        lli A, X, M;
        cin >> A >> X >> M;

        function<lli(lli)> f = [&](lli x) -> lli {
                if (M == 1) return 0;
                if (x == 1) return 1;
                if (x & 1) {
                        return (1 + A * f(x-1)) % M;
                } else {
                        return ( (1 + fpow(A, x / 2, M)) * f(x / 2) ) % M;
                }
        };

        cout << f(X) << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        precompute();
        solve();
        return 0;
}

