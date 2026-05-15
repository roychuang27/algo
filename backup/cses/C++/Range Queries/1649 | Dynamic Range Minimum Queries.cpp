/*
 * Submission ID: 16716272
 * Problem: Dynamic Range Minimum Queries
 * Link: https://cses.fi/problemset/task/1649
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>
#define test(x) cerr << "Line(" << __LINE__ << ") " #x << ' ' << x << endl
#define printv(x)                          \
{                                          \
        for (auto i : x) cout << i << ' '; \
        cout << endl;                      \
}
#define SQ(x) ((x) * (x))
#define SZ(x) ((int)x.size())
#define eb emplace_back
#define ALL(x) begin(x), end(x)
#define rALL(x) rbegin(x), rend(x)
#define fst first
#define sec second

using namespace std;
using lli = long long int;

template <class S, S (*op)(S, S), S (*e)()>
struct segtree {
        int n, size, log;
        std::vector<S> d;

        segtree(int _n = 0) : n(_n) {
                size = 1, log = 0;
                while (size < n) size <<= 1, log++;
                d.assign(2 * size, e());
        }

        segtree(const std::vector<S>& v) : segtree((int)v.size()) {
                for (int i = 0; i < n; i++) d[size + i] = v[i];
                for (int i = size - 1; i; i--)
                        d[i] = op(d[i<<1], d[i<<1|1]);
        }

        void set(int p, S x) {
                p += size;
                d[p] = x;
                for (p >>= 1; p; p >>= 1)
                        d[p] = op(d[p<<1], d[p<<1|1]);
        }

        S get(int p) const {
                return d[p + size];
        }

        // [l, r)
        S prod(int l, int r) const {
                S L = e(), R = e();
                for (l += size, r += size; l < r; l >>= 1, r >>= 1) {
                        if (l & 1) L = op(L, d[l++]);
                        if (r & 1) R = op(d[--r], R);
                }
                return op(L, R);
        }

        S all_prod() const {
                return d[1];
        }

        template <class F>
        int max_right(int l, F f) const {
                if (l == n) return n;
                S sm = e();
                for (l += size;; l >>= 1) {
                        while (!(l & 1)) l >>= 1;
                        if (!f(op(sm, d[l]))) {
                                while (l < size) {
                                        l <<= 1;
                                        if (f(op(sm, d[l])))
                                                sm = op(sm, d[l++]);
                                }
                                return l - size;
                        }
                        sm = op(sm, d[l++]);
                        if ((l & -l) == l) break;
                }
                return n;
        }

        template <class F>
        int min_left(int r, F f) const {
                if (!r) return 0;
                S sm = e();
                for (r += size;; r >>= 1) {
                        --r;
                        while (r > 1 && (r & 1)) r >>= 1;
                        if (!f(op(d[r], sm))) {
                                while (r < size) {
                                        r = r<<1 | 1;
                                        if (f(op(d[r], sm)))
                                                sm = op(d[r--], sm);
                                }
                                return r + 1 - size;
                        }
                        sm = op(d[r], sm);
                        if ((r & -r) == r) break;
                }
                return 0;
        }
};

void solution() {
        int N, Q; cin >> N >> Q;
        vector<int> X(N);
        for (int i = 0; i < N; i++) cin >> X[i];
        const auto op = [](int a, int b) -> int {
                return min(a, b);
        };
        const auto e = []() -> int {
                return 0x3f3f3f3f;
        };
        segtree<int, op, e> st(X);
        while (Q-->0) {
                int t; cin >> t;
                if (t == 1) {
                        int k, u; cin >> k >> u;
                        st.set(k-1, u);
                } else {
                        int a, b; cin >> a >> b;
                        a--;
                        cout << st.prod(a, b) << '\n';
                }
        }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
