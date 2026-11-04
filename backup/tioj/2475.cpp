#include <bits/stdc++.h>
#include <cassert>
#define RED_BOLD "\033[1;31m"
#define WHITE_NORMAL "\033[0m"
// I'll give them a shelter like you've done for me
#if defined(SHELTER) && __cplusplus >= 202302L
#define line(...) \
        std::println(stderr, RED_BOLD "#{} passed" WHITE_NORMAL, __LINE__)
#define dbg(...)                                                               \
        std::println(stderr, RED_BOLD "#{}, ({}) = {}" WHITE_NORMAL, __LINE__, \
                     #__VA_ARGS__, std::forward_as_tuple(__VA_ARGS__))
#else
#define line(...) 39
#define dbg(...) 39
#endif
#ifdef __cpp_lib_format
#define _FMT_ADD_TYPE_PRINT(T, E)                                     \
        template <>                                                   \
        struct std::formatter<T> : std::formatter<std::string_view> { \
                auto format(const T &x, auto &c) const {              \
                        return std::format_to(c.out(), "{}", E);      \
                }                                                     \
        };
#else
#define _FMT_ADD_TYPE_PRINT(T, E)
#endif
#define ADD_TYPE_PRINT(T, E)                                    \
        _FMT_ADD_TYPE_PRINT(T, E)                               \
        std::ostream &operator<<(std::ostream &o, const T &x) { \
                return o << (E);                                \
        }
#define ALL(x) std::begin(x), std::end(x)
#define rALL(x) std::rbegin(x), std::rend(x)
#define ifeq(t, x) if (t == x)
template <class T>
T square(T a) {
        return a * a;
}
template <bool strict = true, class T>
bool chmin(T &a, T b) {
        if constexpr (strict) {
                if (b < a) {
                        a = b;
                        return true;
                }
        } else {
                if (b <= a) {
                        a = b;
                        return true;
                }
        }
        return false;
}
template <bool strict = true, class T>
bool chmax(T &a, T b) {
        if constexpr (strict) {
                if (a < b) {
                        a = b;
                        return true;
                }
        } else {
                if (a <= b) {
                        a = b;
                        return true;
                }
        }
        return false;
}
namespace std {
template <class T, std::size_t n>
auto array_fill(T value) {
        std::array<T, n> res;
        for (auto &e : res) {
                e = value;
        }
        return res;
}
} // namespace std
template <class T, size_t N>
std::istream &operator>>(std::istream &is, std::array<T, N> &a) {
        for (auto &x : a) {
                is >> x;
        }
        return is;
}
template <class T>
std::istream &operator>>(std::istream &is, std::vector<T> &a) {
        for (auto &x : a) {
                is >> x;
        }
        return is;
}
template <class A, class B>
std::istream &operator>>(std::istream &is, std::pair<A, B> &p) {
        return is >> p.first >> p.second;
}
template <class T, class U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p) {
        return os << p.first << ' ' << p.second;
}
template <class T>
struct ITER {
        const T &_v;
        std::string _sep = " ";
        ITER(const T &v, std::string sep = " "): _v(v), _sep(sep) {
        }
        ITER(const T &v, char sep = ' '): _v(v), _sep(sep, 1) {
        }
        friend std::ostream &operator<<(std::ostream &os, const ITER &o) {
                bool first = true;
                for (const auto &x : o._v) {
                        if (!first) {
                                os << o._sep;
                        }
                        first = false;
                        os << x;
                }
                return os;
        }
};

using i32 = std::int32_t;  // -2147483648 ~ 2147483647 (10^9)
using u32 = std::uint32_t; // 0 ~ 4294967295 (10^9)
using i64 = std::int64_t;  // -9223372036854775808 ~ 9223372036854775807 (10^18)
using u64 = std::uint64_t; // 0 ~ 18446744073709551615 (10^19)
using i128 = __int128;     // -170141183460469231731687303715884105728 ~
                           // 170141183460469231731687303715884105727 (10^38)
using u128 = unsigned __int128; // 0 ~ 340282366920938463463374607431768211455
                                // (10^38)
using f32 = float;              // 7 significant decimal digits
using f64 = double;             // 15 significant decimal digits
using f80 = long double;        // 18 significant decimal digits
using f128 = __float128;        // 34 significant decimal digits

using namespace std;

template <class S, auto op, auto e>
struct segtree {
    public:
        segtree(): segtree(0) {
        }
        explicit segtree(int n): segtree(std::vector<S>(n, e())) {
        }
        explicit segtree(const std::vector<S> &v): _n(int(v.size())) {
                size = 1;
                log = 0;
                while (size < _n) {
                        size <<= 1;
                        log++;
                }
                d = std::vector<S>(2 * size, e());
                for (int i = 0; i < _n; i++) {
                        d[size + i] = v[i];
                }
                for (int i = size - 1; i >= 1; i--) {
                        update(i);
                }
        }

        void set(int p, S x) {
                assert(0 <= p && p < _n);
                p += size;
                d[p] = x;
                for (int i = 1; i <= log; i++) {
                        update(p >> i);
                }
        }

        S get(int p) const {
                assert(0 <= p && p < _n);
                return d[p + size];
        }

        S prod(int l, int r) const {
                assert(0 <= l && l <= r && r <= _n);
                S sml = e(), smr = e();
                l += size;
                r += size;

                while (l < r) {
                        if (l & 1) {
                                sml = op(sml, d[l++]);
                        }
                        if (r & 1) {
                                smr = op(d[--r], smr);
                        }
                        l >>= 1;
                        r >>= 1;
                }
                return op(sml, smr);
        }

        S all_prod() const {
                return d[1];
        }

        template <bool (*f)(S)>
        int max_right(int l) const {
                return max_right(l, [](S x) { return f(x); });
        }
        template <class F>
        int max_right(int l, F f) const {
                assert(0 <= l && l <= _n);
                assert(f(e()));
                if (l == _n) {
                        return _n;
                }
                l += size;
                S sm = e();
                do {
                        while (l % 2 == 0) {
                                l >>= 1;
                        }
                        if (!f(op(sm, d[l]))) {
                                while (l < size) {
                                        l = (2 * l);
                                        if (f(op(sm, d[l]))) {
                                                sm = op(sm, d[l]);
                                                l++;
                                        }
                                }
                                return l - size;
                        }
                        sm = op(sm, d[l]);
                        l++;
                } while ((l & -l) != l);
                return _n;
        }

        template <bool (*f)(S)>
        int min_left(int r) const {
                return min_left(r, [](S x) { return f(x); });
        }
        template <class F>
        int min_left(int r, F f) const {
                assert(0 <= r && r <= _n);
                assert(f(e()));
                if (r == 0) {
                        return 0;
                }
                r += size;
                S sm = e();
                do {
                        r--;
                        while (r > 1 && (r % 2)) {
                                r >>= 1;
                        }
                        if (!f(op(d[r], sm))) {
                                while (r < size) {
                                        r = (2 * r + 1);
                                        if (f(op(d[r], sm))) {
                                                sm = op(d[r], sm);
                                                r--;
                                        }
                                }
                                return r + 1 - size;
                        }
                        sm = op(d[r], sm);
                } while ((r & -r) != r);
                return 0;
        }

    private:
        int _n, size, log;
        std::vector<S> d;

        void update(int k) {
                d[k] = op(d[2 * k], d[2 * k + 1]);
        }
};

using S = pair<i32, i32>;
S op(S a, S b) {
        return max(a, b);
}
S e() {
        return {-1, -1};
}

void single_testcase() {
        i32 n;
        cin >> n;
        vector<i32> a(n);
        cin >> a;

        auto vals = a;
        sort(ALL(vals));
        vals.erase(unique(ALL(vals)), vals.end());
        for (auto &x : a) {
                x = distance(vals.begin(), lower_bound(ALL(vals), x));
        }

        i32 down = n;
        for (i32 i = 1; i < n; i++) {
                if (a[i - 1] > a[i]) {
                        down = i;
                        break;
                }
        }

        vector<i32> sep;
        sep.reserve(n + 1);
        sep.emplace_back(0);
        vector<i32> cnt_l(vals.size()), cnt_r(vals.size());

        segtree<S, op, e> seg(n);

        for (i32 i = 0, j; i < n; i = j) {
                j = i;
                while (j < n and a[j] == a[i]) {
                        j++;
                }
                if (i < down) {
                        cnt_l[a[i]] += (j - i);
                        seg.set(sep.size() - 1, {j - i, a[i]});
                } else {
                        cnt_r[a[i]] += (j - i);
                        seg.set(sep.size() - 1, {j - i, a[i]});
                }
                sep.emplace_back(j);
        }

        auto calc_same_side = [&](i32 l, i32 r) -> pair<i32, i32> {
                if (a[l] == a[r - 1]) {
                        return {r - l, a[l]};
                }
                i32 bl = lower_bound(ALL(sep), l) - sep.begin(), br = lower_bound(ALL(sep), r) - sep.begin();
                i32 cl = *lower_bound(ALL(sep), l) - l;
                i32 cr = 0;
                {
                        auto it = lower_bound(ALL(sep), r);
                        if (*it != r) {
                                cr = r - *prev(it);
                                br--;
                        }
                }
                return max({{cl, a[l]}, seg.prod(bl, br), {cr, a[r - 1]}});
        };

        vector<pair<i32, i32>> mx(vals.size(), {-1, -1});
        for (i32 x = vals.size() - 1; x >= 0; x--) {
                mx[x] = {cnt_l[x] + cnt_r[x], x};
                if (x < vals.size() - 1) chmax(mx[x], mx[x+1]);
        }

        i32 q;
        cin >> q;

        for (i32 _ = 0; _ < q; _++) {
                i32 l, r;
                cin >> l >> r;
                l--;
                r--;
                if (r < down or l >= down) {
                        cout << vals[calc_same_side(l, r + 1).second] << '\n';
                } else {
                        i32 cl = *lower_bound(ALL(sep), l) - l;
                        i32 cr = 0;
                        {
                                auto it = lower_bound(ALL(sep), r + 1);
                                if (*it != r + 1) {
                                        cr = r - *prev(it) + 1;
                                }
                        }
                        pair<i32, i32> res = {-1, -1};
                        i32 x = max(a[l], a[r]) + 1;
                        if (x < vals.size()) res = mx[x];
                        if (cl == 0) cl = cnt_l[a[l]];
                        if (cr == 0) cr = cnt_r[a[r]];
                        if (a[l] == a[r]) {
                                chmax(res, {cl + cr, a[l]});
                        } else if (a[l] < a[r]) {
                                chmax(res, calc_same_side(l, down));
                                chmax(res, {cnt_l[a[r]] + cr, a[r]});
                        } else {
                                chmax(res, {cl + cnt_r[a[l]], a[l]});
                                chmax(res, calc_same_side(down, r + 1));
                        }
                        cout << vals[res.second] << '\n';
                }
        }
}

i32 main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        cin.exceptions(cin.failbit);
        i32 t = 1;
        // cin >> t;
        for (i32 i = 0; i < t; i++) {
                single_testcase();
                cout << '\n';
        }
        return 0;
}
