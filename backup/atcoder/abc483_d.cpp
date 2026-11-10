#include <atcoder/lazysegtree.hpp>
#include <bits/stdc++.h>
#include <cassert>
#define RED_BOLD "\033[1;31m"
#define WHITE_NORMAL "\033[0m"
// I'll give them a shelter like you've done for me
#if defined(SHELTER) && defined(__cpp_lib_print)
#define line(...) \
        std::println(stderr, RED_BOLD "#{} passed" WHITE_NORMAL, __LINE__)
#define dbg(...)                                             \
        std::println(stderr,                                 \
                     RED_BOLD "#{}, ({}) = {}" WHITE_NORMAL, \
                     __LINE__,                               \
                     #__VA_ARGS__,                           \
                     std::forward_as_tuple(__VA_ARGS__))
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
        ITER(const T &v, std::string sep = " "):
                _v(v),
                _sep(sep) {
        }
        ITER(const T &v, char sep = ' '):
                _v(v),
                _sep(sep, 1) {
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

using namespace std;

struct S {
        long long mx = 0, mn = 0;
};
S op(S a, S b) {
        return { max(a.mx, b.mx), min(a.mn, b.mn) };
}
S e() {
        return { (long long)-1e18, (long long)1e18 };
}
using F = long long;
F c(F f, F g) {
        return f + g;
}
S m(F f, S s) {
        return { s.mx + f, s.mn + f };
}
F id() {
        return 0LL;
}

void single_testcase() {
        int n;
        cin >> n;
        vector<long long> a(n);
        cin >> a;
        vector<S> v(n + 1);
        for (int i = 1; i <= n; i++) {
                v[i] = {a[i - 1] + v[i - 1].mx, a[i - 1] + v[i - 1].mn};
        }
        for (auto [mx, mn] : v) dbg(mx, mn);
        atcoder::lazy_segtree<S, op, e, F, m, c, id> seg(v);
        auto tmp = seg.all_prod();
        dbg(tmp.mx, tmp.mn);
        long long ans = tmp.mx - tmp.mn + 1;

        for (int i = 1; i <= n; i++) {
                seg.apply(i, n + 1, -2 * a[i - 1]);
                auto res = seg.all_prod();
                dbg(res.mx, res.mn);
                chmax(ans, res.mx - res.mn + 1);
                seg.apply(i, n + 1, +2 * a[i - 1]);
        }

        cout << ans;
}

int main() {
        std::cin.tie(nullptr)->sync_with_stdio(false);
        std::cin.exceptions(std::cin.failbit);
        int t = 1;
        // std::cin >> t;
        for (int i = 0; i < t; i++) {
                if (i) {
                        std::cout << '\n';
                }
                single_testcase();
        }
        return 0;
}
