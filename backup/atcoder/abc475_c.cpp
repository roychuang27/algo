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

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        int N, S;
        lli L;
        cin >> N >> S >> L;
        vector<lli> A(N);
        for (int i = 1; i < N; i++) cin >> A[i];
        vector<lli> disl = {0}, disr = {0};
        lli s1 = 0;
        for (int i = S; i < N; i++) {
                s1 += A[i];
                disr.emplace_back(s1);
        }
        lli s2 = 0;
        for (int i = S-1; i > 0; i--) {
                s2 += A[i];
                disl.emplace_back(s2);
        }
        int ans = 0;
        for (int i = 0; i < SZ(disl); i++) {
                if (disl[i] * 2 <= L) {
                        auto it = upper_bound(ALL(disr), L-disl[i]*2);
                        if (it != disr.end() or disr.back() <= L-disl[i]*2) ans = max(ans, i + (int)(it - disr.begin()));
                }
        }
        for (int i = 0; i < SZ(disr); i++) {
                if (disr[i] * 2 <= L) {
                        auto it = upper_bound(ALL(disl), L-disr[i]*2);
                        if (it != disl.end() or disl.back() <= L-disr[i]*2) ans = max(ans, i + (int)(it - disl.begin()));
                }
        }
        cout << ans << '\n';

        return 0;
}


