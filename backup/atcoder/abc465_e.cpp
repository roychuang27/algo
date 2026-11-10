#include <bit>
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

template <long long MOD>
struct StaticModint {
        static_assert(MOD > 0);
        long long v = 0;
        using mint = StaticModint;
        constexpr StaticModint() = default;
        template <class T>
        StaticModint(T x) {
                v = static_cast<long long>(x % MOD);
                if (v < 0) {
                        v += MOD;
                }
        }
        long long val() const {
                return v;
        }
        mint &operator+=(const mint &rhs) {
                if (v >= MOD - rhs.v) {
                        v -= MOD - rhs.v;
                } else {
                        v += rhs.v;
                }
                return *this;
        }
        mint &operator-=(const mint &rhs) {
                v -= rhs.v;
                if (v < 0) {
                        v += MOD;
                }
                return *this;
        }
        mint &operator*=(const mint &rhs) {
                v = v * rhs.v % MOD;
                return *this;
        }
        mint &operator/=(const mint &rhs) {
                return *this *= rhs.inv();
        }
        mint pow(long long n) const {
                assert(n >= 0);
                mint a = *this, res = 1;
                while (n > 0) {
                        if (n & 1) {
                                res *= a;
                        }
                        a *= a;
                        n >>= 1;
                }
                return res;
        }
        mint inv() const {
                assert(v != 0);
                return pow(MOD - 2);
        }
        mint operator+() const {
                return *this;
        }
        mint operator-() const {
                return mint(v == 0 ? 0 : MOD - v);
        }
        friend mint operator+(mint lhs, const mint &rhs) {
                return lhs += rhs;
        }
        friend mint operator-(mint lhs, const mint &rhs) {
                return lhs -= rhs;
        }
        friend mint operator*(mint lhs, const mint &rhs) {
                return lhs *= rhs;
        }
        friend mint operator/(mint lhs, const mint &rhs) {
                return lhs /= rhs;
        }
        friend bool operator==(const mint &lhs, const mint &rhs) {
                return lhs.v == rhs.v;
        }
        friend bool operator!=(const mint &lhs, const mint &rhs) {
                return lhs.v != rhs.v;
        }
        friend std::ostream &operator<<(std::ostream &os, mint a) {
                return os << a.val();
        }
        friend std::istream &operator>>(std::istream &is, mint &a) {
                long long x;
                is >> x;
                a = x;
                return is;
        }
};
#ifdef __cpp_lib_format
template <long long MOD>
struct std::formatter<StaticModint<MOD>> : std::formatter<long long> {
        auto format(const StaticModint<MOD> &x, auto &ctx) const {
                return std::formatter<long long>::format(x.val(), ctx);
        }
};
#endif

// using mint = StaticModint<1'000'000'007>;
using mint = StaticModint<998244353>;

using namespace std;

void single_testcase() {
        string s;
        cin >> s;

        int tight_mod3 = 0, tight_mask = 0;
        vector dp(3, vector<mint> (1024));
        for (int i = 0; i < s.size(); i++) {
                vector ndp(3, vector<mint> (1024));
                if (i > 0) {
                        for (int c = 1; c < 10; c++) {
                                ndp[c % 3][1 << c] += 1;
                        }
                }
                for (int m = 0; m < 3; m++) {
                        for (int mask = 0; mask < 1024; mask++) {
                                for (int c = 0; c < 10; c++) {
                                        ndp[(m + c) % 3][mask | (1 << c)] += dp[m][mask];
                                }
                        }
                }
                for (int c = (i == 0 ? 1 : 0); c < s[i] - '0'; c++) {
                        ndp[(tight_mod3 + c) % 3][tight_mask | (1 << c)] += 1;
                }
                tight_mod3 = (tight_mod3 + s[i] - '0') % 3;
                tight_mask |= (1 << (s[i] - '0'));
                swap(dp, ndp);
        }
        dp[tight_mod3][tight_mask] += 1;

        mint ans = 0;
        for (int m = 0; m < 3; m++) {
                for (uint32_t mask = 0; mask < 1024; mask++) {
                        int cond = 0;
                        if (m == 0) cond++;
                        if (mask & (1 << 3)) cond++;
                        if (std::popcount(mask) == 3) cond++;

                        if (cond == 1) {
                                ans += dp[m][mask];
                        }
                }
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
