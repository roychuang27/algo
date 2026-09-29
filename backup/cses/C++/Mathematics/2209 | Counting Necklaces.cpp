#include <bits/stdc++.h>
#include <cassert>
#include <numeric>
#ifdef LOCAL
template <class T> concept Iterable = requires(T x) {
        std::begin(x);
        std::end(x);
};
template <class T> void dbg_print(const T &x) {
        if constexpr (Iterable<T> &&
                      !std::is_convertible_v<T, std::string_view>) {
                std::cerr << '[';
                bool first = true;
                for (const auto &e : x) {
                        if (!first) {
                                std::cerr << ", ";
                        }
                        first = false;
                        dbg_print(e);
                }
                std::cerr << ']';
        } else {
                std::cerr << x;
        }
}
#define dbg(...)                                                             \
        do {                                                                 \
                std::cerr << "\033[1;31m(" #__VA_ARGS__ ") = (";             \
                bool _first = true;                                          \
                ([&](auto &&...args) {                                       \
                        ((std::cerr << (_first ? "" : ", "), _first = false, \
                          dbg_print(args)),                                  \
                         ...);                                               \
                }(__VA_ARGS__));                                             \
                std::cerr << ")\033[0m\n";                                   \
        } while (0)
#else
#define dbg(...) 39
#endif
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
template <class T, std::size_t n> constexpr auto array_fill(T value) {
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
using lli = long long int;

template <long long M> struct Modint {
        long long x;
        Modint(long long _x = 0)
                : x(_x % M) {
        }
        Modint &operator+=(Modint b) {
                x += b.x;
                if (x >= M) {
                        x -= M;
                }
                return *this;
        }
        Modint &operator-=(Modint b) {
                x -= b.x;
                if (x < 0) {
                        x += M;
                }
                return *this;
        }
        Modint &operator*=(Modint b) {
                x = 1LL * x * b.x % M;
                return *this;
        }
        Modint pow(long long n) const {
                Modint r = 1, a = *this;
                for (; n; n >>= 1, a *= a) {
                        if (n & 1) {
                                r *= a;
                        }
                }
                return r;
        }
        Modint inv() const {
                return pow(M - 2);
        }
        Modint &operator/=(Modint b) {
                return *this *= b.inv();
        }
        friend Modint operator+(Modint a, Modint b) {
                return a += b;
        }
        friend Modint operator-(Modint a, Modint b) {
                return a -= b;
        }
        friend Modint operator*(Modint a, Modint b) {
                return a *= b;
        }
        friend Modint operator/(Modint a, Modint b) {
                return a /= b;
        }
        friend std::ostream &operator<<(std::ostream &os, Modint a) {
                return os << a.x;
        }
        friend std::istream &operator>>(std::istream &is, Modint &a) {
                long long x;
                is >> x;
                a = x;
                return is;
        }
};

using mint = Modint<1'000'000'007>;
constexpr int MAXVAL = 1e6;
mint fact[MAXVAL + 1];

void precompute() {
        fact[0] = 1;
        for (int i = 1; i <= MAXVAL; i++) {
                fact[i] = fact[i-1] * i;
        }
}

mint Combination(int n, int m) {
        assert(n >= m);
        return fact[n] / (fact[m] * fact[n-m]);
}

void solve() {
        int N;
        mint M;
        cin >> N >> M;
        dbg(N, M);
        mint res = 0;
        for (int k = 0; k < N; k++) {
                res += M.pow(gcd(N, k));
                dbg(res);
        }
        res /= N;
        cout << res << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        cin.exceptions(cin.failbit);
        solve();
        return 0;
}
