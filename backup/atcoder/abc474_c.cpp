#include <bits/stdc++.h>
#include <atcoder/fenwicktree.hpp>
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

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        int N, Q;
        cin >> N >> Q;
        vector<int> p(N+Q);
        vector<int> v(N+1);
        for (int i = 0; i < N; i++) {
                cin >> p[i];
                v[p[i]] = i;
        }
        atcoder::fenwick_tree<int> f(N + Q);
        auto idx = [&](int x) -> int {
                int l = 0, r = N + Q - 1;
                while (l < r) {
                        int m = (l + r) / 2;
                        if (f.sum(0, m) < x) {
                                l = m + 1;
                        } else {
                                r = m;
                        }
                }
                dbg(x, f.sum(0, l));
                return l;
        };
        for (int i = 0; i < N; i++) f.add(i, 1);
        for (int i = 0; i < Q; i++) {
                int a;
                cin >> a;
                p[N+i] = a;
                p[v[a]] = -1;
                v[a] = N+i;
        }
        for (auto i : p) {
                if (i != -1) cout << i << ' ';
        }
        return 0;
}



