/*
 * Submission ID: 16716019
 * Problem: Range Updates and Sums
 * Link: https://cses.fi/problemset/task/1735
 */

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

using namespace std;
using lli = long long int;

template <class Monoid,
          Monoid (*op)(Monoid, Monoid),
          Monoid (*e)(),
          class Tag,
          Monoid (*mapping)(Tag, Monoid),
          Tag (*composition)(Tag, Tag),
          Tag (*id)()>
struct lazy_segtree {
        int n, size, log;
        std::vector<Monoid> d;
        std::vector<Tag> lz;

        lazy_segtree(int _n = 0) : n(_n) {
                size = 1, log = 0;
                while (size < n) size <<= 1, log++;
                d.assign(2 * size, e());
                lz.assign(size, id());
        }

        lazy_segtree(const std::vector<Monoid>& v) : lazy_segtree((int)v.size()) {
                for (int i = 0; i < n; i++) d[size + i] = v[i];
                for (int i = size - 1; i; i--)
                        d[i] = op(d[i<<1], d[i<<1|1]);
        }

        void apply_node(int k, Tag f) {
                d[k] = mapping(f, d[k]);
                if (k < size) lz[k] = composition(f, lz[k]);
        }

        void push(int k) {
                apply_node(k<<1, lz[k]);
                apply_node(k<<1|1, lz[k]);
                lz[k] = id();
        }

        void set(int p, Monoid x) {
                p += size;
                for (int i = log; i; i--) push(p >> i);
                d[p] = x;
                for (p >>= 1; p; p >>= 1)
                        d[p] = op(d[p<<1], d[p<<1|1]);
        }

        Monoid get(int p) {
                p += size;
                for (int i = log; i; i--) push(p >> i);
                return d[p];
        }

        // [l, r)
        Monoid prod(int l, int r) {
                if (l == r) return e();
                l += size; r += size;
                for (int i = log; i; i--) {
                        if ((l >> i) << i != l) push(l >> i);
                        if ((r >> i) << i != r) push((r - 1) >> i);
                }
                Monoid L = e(), R = e();
                for (; l < r; l >>= 1, r >>= 1) {
                        if (l & 1) L = op(L, d[l++]);
                        if (r & 1) R = op(d[--r], R);
                }
                return op(L, R);
        }

        Monoid all_prod() { return d[1]; }

        void apply(int p, Tag f) {
                p += size;
                for (int i = log; i; i--) push(p >> i);
                d[p] = mapping(f, d[p]);
                for (p >>= 1; p; p >>= 1)
                        d[p] = op(d[p<<1], d[p<<1|1]);
        }

        void apply(int l, int r, Tag f) {
                if (l == r) return;
                l += size; r += size;
                for (int i = log; i; i--) {
                        if ((l >> i) << i != l) push(l >> i);
                        if ((r >> i) << i != r) push((r - 1) >> i);
                }
                int l0 = l, r0 = r;
                for (; l < r; l >>= 1, r >>= 1) {
                        if (l & 1) apply_node(l++, f);
                        if (r & 1) apply_node(--r, f);
                }
                l = l0; r = r0;
                for (int i = 1; i <= log; i++) {
                        if ((l >> i) << i != l) d[l>>i] = op(d[(l>>i)<<1], d[(l>>i)<<1|1]);
                        if ((r >> i) << i != r) d[(r-1)>>i] = op(d[((r-1)>>i)<<1], d[((r-1)>>i)<<1|1]);
                }
        }

        template <class Predicate>
        int max_right(int l, Predicate g) {
                if (l == n) return n;
                l += size;
                for (int i = log; i; i--) push(l >> i);
                Monoid sm = e();
                do {
                        while (!(l & 1)) l >>= 1;
                        if (!g(op(sm, d[l]))) {
                                while (l < size) {
                                        push(l);
                                        l <<= 1;
                                        if (g(op(sm, d[l])))
                                                sm = op(sm, d[l++]);
                                }
                                return l - size;
                        }
                        sm = op(sm, d[l++]);
                } while ((l & -l) != l);
                return n;
        }

        template <class Predicate>
        int min_left(int r, Predicate g) {
                if (!r) return 0;
                r += size;
                for (int i = log; i; i--) push((r - 1) >> i);
                Monoid sm = e();
                do {
                        --r;
                        while (r > 1 && (r & 1)) r >>= 1;
                        if (!g(op(d[r], sm))) {
                                while (r < size) {
                                        push(r);
                                        r = r<<1 | 1;
                                        if (g(op(d[r], sm)))
                                                sm = op(d[r--], sm);
                                }
                                return r + 1 - size;
                        }
                        sm = op(d[r], sm);
                } while ((r & -r) != r);
                return 0;
        }
};

enum TagType { ADD, SET, NONE };

struct Tag {
        TagType type;
        lli val;
};
Tag id() { return {NONE, 0}; }

struct S {
        lli sum;
        int len;
};
S e() { return {0, 0}; }

S op(S a, S b) {
        return {a.sum + b.sum, a.len + b.len};
}

S mapping(Tag f, S x) {
        if (f.type == ADD)
                return {x.sum + f.val * x.len, x.len};
        if (f.type == SET)
                return {f.val * x.len, x.len};
        return x;
}

Tag composition(Tag f, Tag g) {
        if (f.type == SET)
                return f;
        if (f.type == ADD) {
                if (g.type == SET)
                        return Tag{SET, g.val + f.val};
                if (g.type == ADD)
                        return Tag{ADD, g.val + f.val};
                return f;
        }
        return g;
}

void solution() {
        int N, Q; cin >> N >> Q;
        vector<S> A(N, {0, 1});
        for (int i = 0; i < N; i++) cin >> A[i].sum;
        lazy_segtree<S, op, e, Tag, mapping, composition, id> st(A);
        while (Q-->0) {
                int p, a, b; cin >> p >> a >> b;
                a--;
                if (p == 1) {
                        int x; cin >> x;
                        st.apply(a, b, Tag{ADD, x});
                }
                if (p == 2) {
                        int x; cin >> x;
                        st.apply(a, b, Tag{SET, x});
                }
                if (p == 3) {
                        cout << st.prod(a, b).sum << '\n';
                }
        }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
