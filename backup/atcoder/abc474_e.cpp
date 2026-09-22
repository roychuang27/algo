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
#define SZ(x) ((size_t) x.size())
#define SQ(x) ((x) * (x))
#define CORDCOMP(x, fx) std::sort(ALL(x)); x.erase(std::unique(ALL(x)), std::end(x)); const auto fx = [&](int val) -> int { return std::lower_bound(ALL(x), val) - std::begin(x); }
#define fst first
#define sec second

using lli = long long int;
using namespace std;

void solve() {
        int N;
        cin >> N;
        vector<pair<lli, lli>> v(N);
        lli m = 1e18;
        for (auto &[a, b] : v) {
                cin >> a >> b;
                m = min(m, a);
        }
        sort(ALL(v), [&](auto a, auto b) {
                     if (a.fst - a.sec == b.fst - b.sec) return a.fst < b.fst;
                     return a.fst - a.sec < b.fst - b.sec;
        });
        lli ans = 0;
        for (int l = 0, r = N - 1; l <= r;) {
                if (l == r) {
                        ans += min(v[l].fst, v[l].sec + m);
                        break;
                }
                if (v[l].fst - v[l].sec <= 2*m) {
                        ans += v[l].fst;
                        ans += v[r].sec;
                        l++;
                        r--;
                } else {
                        ans += v[l].sec + m;
                        l++;
                }
        }
        cout << ans << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        int T;
        cin >> T;
        while (T--) solve();
        return 0;
}



