#include <bits/stdc++.h>
#include <atcoder/modint.hpp>
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

using mint = atcoder::modint;

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        int N;
        lli M;
        cin >> N >> M;
        atcoder::modint::set_mod(M);
        vector<lli> A(N+1, 0), B(N, 0);
        for (int i = 1; i <= N; i++) cin >> A[i];
        for (int i = 1; i <  N; i++) cin >> B[i];

        lli cost = 0, slope = (N % 2 == 1);
        mint s = 0;
        map<lli, lli> events;
        for (int i = 1; i <= N; i++) {
                s = -s + B[i-1];
                lli d = (s - A[i]).val();
                cost += d;
                if (i % 2 == 1) {
                        events[M - d] -= M;
                } else {
                        events[d + 1] += M;
                }
        }

        lli ans = cost;
        for (auto [a, b] : events) {
                cost += b;
                ans = min(ans, cost + a * slope);
        }

        cout << ans << '\n';
        return 0;
}