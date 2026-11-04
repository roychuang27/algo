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

constexpr lli INF = 1e18;

namespace SEGTREE {
        struct S {
                lli maxl, maxr, sum, mx;
                S() : maxl(0), maxr(0), sum(0), mx(0) {}
                S(lli val) : maxl(max(0LL, val)), maxr(max(0LL, val)), sum(val), mx(max(0LL, val)) {}
                S(lli a, lli b, lli c, lli d) : maxl(a), maxr(b), sum(c), mx(d) {}
        };

        S op(S l, S r) {
                return {
                        max(l.sum + r.maxl, l.maxl),
                        max(r.sum + l.maxr, r.maxr),
                        l.sum + r.sum,
                        max({l.mx, r.mx, l.maxr + r.maxl})
                };
        }

        struct zkw {
                int N;
                vector<S> t;

                zkw(vector<S> &v) : N(SZ(v)), t(2*N) {
                        for (int i = 0; i < N; i++) {
                                t[N+i] = v[i];
                        }
                        for (int i = N-1; i > 0; i--) {
                                t[i] = op(t[i<<1], t[i<<1|1]);
                        }
                }

                S qry(int l, int r) {
                        S lhs{}, rhs{};
                        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
                                if (l & 1) lhs = op(lhs, t[l++]);
                                if (r & 1) rhs = op(t[--r], rhs);
                        }
                        return op(lhs, rhs);
                }
        };
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);

        int N;
        lli K;
        cin >> N >> K;
        vector<SEGTREE::S> A(N);
        for (int a, i = 0; i < N; i++) {
                cin >> a;
                A[i] = SEGTREE::S(a);
        }

        vector<lli> d(N+2, 0);
        SEGTREE::zkw t(A);

        for (int l = 0, r = 0; l < N; l++) {
                r = max(l+1, r);
                while (r <= N and t.qry(l, r).mx < K) {
                        r++;
                }
                if (r > N) continue;
                d[r - l]++;
                d[N - l + 1]--;
        }

        for (int i = 1; i <= N; i++) d[i] += d[i-1];
        for (int i = 1; i <= N; i++) d[i] += d[i-1];

        int Q;
        cin >> Q;
        for (int x, _ = 0; _ < Q; _++) {
                cin >> x;
                cout << d[x] << '\n';
        }
        
        return 0;
}
