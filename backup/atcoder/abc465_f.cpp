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
template <class A, class B>
std::istream &operator>>(std::istream &is, std::pair<A, B> &p) {
        return is >> p.first >> p.second;
}
template <class T, class U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p) {
        return os << p.first << ' ' << p.second;
}
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
template <class T>
struct ITER {
        const T &_v;
        std::string_view _sep = " ";
        ITER(const T &v, std::string sep = " "):
                _v(v),
                _sep(sep) {
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

int pow10[6] = {1, 10, 100, 1000, 10000, 100000};

int kth_digit(int x, int i) {
        return (x / pow10[i]) % 10;
}

void single_testcase() {
        int n;
        cin >> n;

        vector<string> s(n);
        vector<long long> v(n);
        for (int i = 0; i < n; i++) {
                cin >> s[i] >> v[i];
        }

        vector<long long> zeta(1'000'000);
        for (int i = 0; i < n; i++) {
                zeta[stoi(s[i])] += v[i];
        }

        for (int i = 0; i < 6; i++) {
                // zeta[i][j] = zeta[i-1][j] + zeta[i][j - pow10[5-i]]
                for (int num = 0; num < 1'000'000; num++) {
                        if (kth_digit(num, 5-i) > 0) {
                                zeta[num] += zeta[num - pow10[5-i]];
                        }
                }
        }

        // dbg(zeta);

        auto qry = [&](string &q1, string &q2) -> long long {
                for (int i = 0; i < 6; i++) {
                        if (q1[i] > q2[i]) {
                                return 0;
                        }
                }
                vector<int> d1(6), d2(6);
                for (int i = 0; i < 6; i++) {
                        d1[i] = q1[5-i] - '0';
                        d2[i] = q2[5-i] - '0';
                }
                dbg(d1, d2);

                long long res = 0;

                for (int mask = 0; mask < 64; mask++) {
                        int k = 0;
                        bool ok = true;
                        for (int j = 0; j < 6; j++) {
                                if (mask & (1 << j)) {
                                        // exclusive
                                        if (d1[j] == 0) {
                                                ok = false;
                                                break;
                                        }
                                        k += (d1[j] - 1) * pow10[j];
                                } else {
                                        // inclusive
                                        k += d2[j] * pow10[j];
                                }
                        }

                        if (!ok) {
                                continue;
                        }

                        dbg(k, zeta[k], popcount((unsigned) mask));

                        if (popcount((unsigned) mask) & 1) {
                                res -= zeta[k];
                        } else {
                                res += zeta[k];
                        }
                }

                return res;
        };

        int q;
        cin >> q;

        for (int _ = 0; _ < q; _++) {
                string q1, q2;
                cin >> q1 >> q2;
                cout << qry(q1, q2) << '\n';
        }
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
