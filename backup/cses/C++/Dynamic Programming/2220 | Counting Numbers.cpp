#include <bits/stdc++.h>
#include <cassert>
#define RED_BOLD "\033[1;31m"
#define WHITE_NORMAL "\033[0m"
// I'll give them a shelter like you've done for me
#if defined(SHELTER) && defined(__cpp_lib_print)
#define line(...)                                            \
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

long long solve(long long x) {
        if (x == -1) {
                return 0;
        }

        string s = to_string(x);
        vector dp(2, vector(2, vector(10, vector<long long>(s.size(), -1))));

        function<long long(int, int, bool, bool)> recursive = [&](int prev_digit, int i, bool leading_zero, bool tight) -> long long {
                if (i == s.size()) {
                        return 1;
                }

                if (dp[leading_zero][tight][prev_digit][i] != -1) {
                        return dp[leading_zero][tight][prev_digit][i];
                }

                long long res = 0;
                int limit = 9;
                if (tight) {
                        limit = s[i] - '0';
                }

                for (int nxt_digit = 0; nxt_digit <= limit; nxt_digit++) {
                        if (nxt_digit == prev_digit and nxt_digit != 0) {
                                continue;
                        }
                        if (nxt_digit == 0 and nxt_digit == prev_digit and !leading_zero) {
                                continue;
                        }

                        res += recursive(nxt_digit, i + 1, leading_zero & (nxt_digit == 0), tight & (nxt_digit == limit));
                }

                return dp[leading_zero][tight][prev_digit][i] = res;
        };

        return recursive(0, 0, 1, 1);
}

void single_testcase() {
        long long a, b;
        cin >> a >> b;

        cout << solve(b) - solve(a - 1);
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
