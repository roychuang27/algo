#include <iostream>
#include <utility>
#include <set>
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
#define int long long

void solution() {
        int N, K;
        cin >> N >> K;
        vector<pair<int, int>> v(N);
        for (auto &[l, r] : v) cin >> l >> r;
        sort(ALL(v), [](auto p1, auto p2) {
                        if (p1.sec == p2.sec) return p1.fst > p2.fst;
                        return p1.sec < p2.sec;
        });
        const auto check = [&](lli gap) -> bool {
                int cnt = 1;
                int i = 0, j = 1;
                while (j < N) {
                        while (j < N and v[j].fst - v[i].sec < gap) j++;
                        if (j == N) break;
                        cnt++;
                        i = j;
                        j++;
                }
                return cnt >= K;
        };
        if (check(1) == false) {
                cout << -1 << '\n';
                return;
        }
        lli L = 1, R = 2e9 + 1;
        while (R - L > 1) {
                lli m = (L + R) / 2;
                if (check(m)) L = m;
                else R = m;
                test(m);
        }
        cout << L << '\n';
}

signed main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        solution();
        return 0;
}
