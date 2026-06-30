#include <atcoder/lazysegtree>
#include <algorithm>
#include <iostream>
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

namespace seg {
        struct S {
                lli M, S;
                int L;
        };
        S op(S a, S b) {
                return {max(a.M, b.M), a.S + b.S, a.L + b.L};
        }
        S e() {
                return {0, 0, 0};
        }
        enum Type { None, Set, Add };
        struct F {
                Type T;
                lli val;
        };
        S mapping(F f, S s) {
                if (f.T == Set) {
                        s.M = f.val;
                        s.S = f.val * s.L;
                }
                if (f.T == Add) {
                        s.M += f.val;
                        s.S += f.val * s.L;
                }
                return s;
        }
        F composition(F f, F g) {
                if (g.T == None) return f;
                if (f.T == Set) {
                        return f;
                }
                if (f.T == Add) {
                        if (g.T == Add) {
                                return {Add, f.val + g.val};
                        } else {
                                return {Set, f.val + g.val};
                        }
                }
                return g;
        }
        F id() {
                return {None, 0};
        }
}

void solution() {
        int N, Q;
        cin >> N >> Q;
        vector<lli> H(N);
        for (auto &h : H) cin >> h;
        vector<seg::S> v(N);
        for (int i = 0; i < N; i++) {
                v[i] = {H[i], H[i], 1};
        }
        atcoder::lazy_segtree<seg::S, seg::op, seg::e, seg::F, seg::mapping, seg::composition, seg::id> segtr(v);
        for (int _ = 0; _ < Q; _++) {
                int t;
                cin >> t;
                if (t == 1) {
                        int l, r;
                        cin >> l >> r;
                        l--;
                        segtr.apply(l, r, {seg::Set, segtr.prod(l, r).M});
                }
                if (t == 2) {
                        lli k;
                        int l, r;
                        cin >> k >> l >> r;
                        l--;
                        segtr.apply(l, r, {seg::Add, k});
                }
                if (t == 3) {
                        lli k;
                        int l, r;
                        cin >> k >> l >> r;
                        l--;
                        if (segtr.prod(l, r).S >= k * (r - l)) {
                                cout << "Yes\n";
                        } else {
                                cout << "No\n";
                        }
                }
        }
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        solution();
        return 0;
}
