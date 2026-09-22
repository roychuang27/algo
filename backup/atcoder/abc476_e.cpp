#include <bits/stdc++.h>
#include <atcoder/segtree.hpp>
using namespace std;
#ifdef LOCAL
#define dbg(...) do { std::cerr << "Line(" << __LINE__ << ") [" #__VA_ARGS__ "] =>"; ([](auto&&... args){ ((std::cerr << ' ' << args), ...); }(__VA_ARGS__)); std::cerr << std::endl; } while(0)
#define dbgv(x) do { std::cerr << "Line(" << __LINE__ << ") " #x " => ["; int _i=0; for (auto& _e : (x)) std::cerr << (_i++ ? ", " : "") << _e; std::cerr << "]" << std::endl; } while(0)
#else
#define dbg(...) 39
#define dbgv(...) 39
#endif
#define ALL(x) std::begin(x), std::end(x)
#define rALL(x) std::rbegin(x), std::rend(x)
template<typename T> struct CORDCOMP { vector<T> v; CORDCOMP(vector<T> x) : v(std::move(x)) { sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end()); } int operator()(const T& x) const { return lower_bound(v.begin(), v.end(), x) - v.begin(); } };
template<class T> T square(T a) { return a * a; }
template<class T> bool chmin(T &a,T b) { if (b < a) { a = b; return 1; } else return 0; }
template<class T> bool chmax(T &a,T b) { if (a < b) { a = b; return 1; } else return 0; }
template<class T, class U> auto vec(size_t n, U value) { return std::vector<T>(n, value); }
template<class T, class... Args> auto vec(size_t n, Args... args) { return std::vector(n, vec<T>(args...)); }
template<typename T, std::size_t N> using arr = std::array<T, N>;
using lli = long long int;

namespace seg {
        struct S {
                int mx, ix, mn, in;
        };
        S e() {
                return {-1, -1, 1000000000, -1};
        }
        S op(S a, S b) {
                S res = e();
                if (a.mx > b.mx) {
                        res.mx = a.mx;
                        res.ix = a.ix;
                } else {
                        res.mx = b.mx;
                        res.ix = b.ix;
                }
                if (a.mn < b.mn) {
                        res.mn = a.mn;
                        res.in = a.in;
                } else {
                        res.mn = b.mn;
                        res.in = b.in;
                }
                return res;
        }
}

void precompute() {
}

void solve() {
        int N, M;
        cin >> N >> M;
        vector<int> P(N);
        for (auto &i : P) {
                cin >> i;
        }
        vector<seg::S> v(N);
        for (int i = 0; i < N; i++) {
                v[i] = {P[i], i, P[i], i};
        }
        atcoder::segtree<seg::S, seg::op, seg::e> t(v);
        for (int _ = 0; _ < M; _++) {
                int l, r;
                cin >> l >> r;
                l--;
                auto [mx, ix, mn, in] = t.prod(l, r);
                dbg(mx, ix, mn, in);
                P[ix] = mn;
                P[in] = mx;
                t.set(ix, {mn, ix, mn, ix});
                t.set(in, {mx, in, mx, in});
                dbgv(P);
        }
        for (auto i : P) cout << i << ' ';
        cout << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        precompute();
        solve();
        return 0;
}


