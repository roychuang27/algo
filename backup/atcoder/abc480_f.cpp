#include <bits/stdc++.h>
#include <cassert>
#define RED_BOLD "\033[1;31m"
#define WHITE_NORMAL "\033[0m"
// I'll give them a shelter like you've done for me
#if defined(SHELTER) && __cplusplus >= 202302L
#define line(...) std::println(stderr, RED_BOLD "#{} passed" WHITE_NORMAL, __LINE__)
#define dbg(...)                                                                             \
        std::println(stderr, RED_BOLD "#{}, ({}) = {}" WHITE_NORMAL, __LINE__, #__VA_ARGS__, \
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
        const T         &_v;
        std::string_view _sep = " ";
        ITER(const T &v, std::string_view sep = " "): _v(v), _sep(sep) {
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

using i32  = std::int32_t;  // -2147483648 ~ 2147483647 (10^9)
using u32  = std::uint32_t; // 0 ~ 4294967295 (10^9)
using i64  = std::int64_t;  // -9223372036854775808 ~ 9223372036854775807 (10^18)
using u64  = std::uint64_t; // 0 ~ 18446744073709551615 (10^19)
using i128 = __int128; // -170141183460469231731687303715884105728 ~ 170141183460469231731687303715884105727 (10^38)
using u128 = unsigned __int128; // 0 ~ 340282366920938463463374607431768211455 (10^38)
using f32  = float;             // 7 significant decimal digits
using f64  = double;            // 15 significant decimal digits
using f80  = long double;       // 18 significant decimal digits
using f128 = __float128;        // 34 significant decimal digits

using namespace std;

void single_testcase() {
        i32 n;
        i64 m;
        cin >> n >> m;
        vector<i64> a(n);
        cin >> a;
        i64 s = reduce(ALL(a));
        i64 t = s / m;

        vector<i32> dp(1 << n, -1);
        dp[0] = 0;

        auto f = [&](this auto &&self, int mask, i64 sum) -> i32 {
                if (dp[mask] != -1) return dp[mask];

                for (int j = 0; j < n; j++) {
                        if (!((1 << j) & mask)) continue;
                        chmax(dp[mask], self(mask ^ (1 << j), sum - a[j]));
                }
                if (sum % t == 0) dp[mask]++;
                return dp[mask];
        };

        cout << m - f((1 << n) - 1, s);
        dbg(dp);
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
