#include <bits/stdc++.h>
#include <cassert>
#define RED_BOLD "\033[1;31m"
#define WHITE_NORMAL "\033[0m"
#if defined(LOCAL) && __cplusplus >= 202302L
#define dbg(...)                                                               \
        std::println(stderr, RED_BOLD "#{}, ({}) = {}" WHITE_NORMAL, __LINE__, \
                     #__VA_ARGS__, std::forward_as_tuple(__VA_ARGS__))
#define log(msg)                                                 \
        std::cerr << RED_BOLD << '#' << __LINE__ << ", " << #msg \
                  << WHITE_NORMAL << '\n'
#else
#define dbg(...) 39
#define log(...) 39
#endif
#ifdef __cpp_lib_format
#define _FMT_ADD_TYPE_PRINT(T, E)                                    \
        template <> struct std::formatter<T> : std::formatter<int> { \
                auto format(const T &x, auto &c) const {             \
                        return std::format_to(c.out(), "{}", E);     \
                }                                                    \
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
template <class T> T square(T a) {
        return a * a;
}
template <class T> bool chmin(T &a, T b) {
        if (b < a) {
                a = b;
                return 1;
        } else {
                return 0;
        }
}
template <class T> bool chmax(T &a, T b) {
        if (a < b) {
                a = b;
                return 1;
        } else {
                return 0;
        }
}
namespace std {
template <class T, std::size_t n> auto array_fill(T value) {
        std::array<T, n> res;
        for (auto &e : res) {
                e = value;
        }
        return res;
}
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
template <class A, class B>
std::istream &operator>>(std::istream &is, std::pair<A, B> &p) {
        return is >> p.first >> p.second;
}
using namespace std;

template <long long MOD> struct static_modint {
        static_assert(MOD > 0);
        long long v = 0;
        using mint = static_modint;
        constexpr static_modint() = default;
        template <class T> static_modint(T x) {
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
struct std::formatter<static_modint<MOD> > : std::formatter<long long> {
        auto format(const static_modint<MOD> &x, auto &ctx) const {
                return std::formatter<long long>::format(x.val(), ctx);
        }
};
#endif

using mint = static_modint<1000000007>;

void solve() {
        int n, m;
        cin >> n >> m;
        vector a(n, vector<mint>(m + 1));
        cin >> a;

        vector<int> row_of_var(m, -1);
        int row = 0, col = 0;
        while (col < m and row < n) {
                int pivot = row;
                while (pivot < n and a[pivot][col] == 0) {
                        pivot++;
                }

                if (pivot == n) {
                        col++;
                        continue;
                }

                swap(a[row], a[pivot]);
                row_of_var[col] = row;

                mint div = a[row][col].inv();
                for (int j = col; j <= m; j++) {
                        a[row][j] *= div;
                }

                for (int i = 0; i < n; i++) {
                        if (i != row and a[i][col] != 0) {
                                mint mul = a[i][col];
                                for (int j = col; j <= m; j++) {
                                        a[i][j] -= mul * a[row][j];
                                }
                        }
                }

                row++;
                col++;
        }

        for (int i = row; i < n; i++) {
                // contradiction
                if (a[i][m] != 0) {
                        cout << -1;
                        return;
                }
        }

        vector<mint> ans(m, 0); // fill untouched variable with 0
        for (int j = 0; j < m; j++) {
                if (row_of_var[j] != -1) {
                        ans[j] = a[row_of_var[j]][m];
                }
        }

        for (auto v : ans) {
                cout << v << ' ';
        }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        cin.exceptions(cin.failbit);
        int t = 1;
        // cin >> t;
        for (int i = 0; i < t; i++) {
                solve();
                cout << '\n';
        }
        return 0;
}
