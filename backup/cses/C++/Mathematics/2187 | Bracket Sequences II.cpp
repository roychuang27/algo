#include <bits/stdc++.h>
#include <cassert>
#ifdef LOCAL
#define dbg(...)                                                               \
        do {                                                                   \
                std::cerr << "Line(" << __LINE__ << ") [" #__VA_ARGS__ "] =>"; \
                ([](auto &&...args) {                                          \
                        ((std::cerr << ' ' << args), ...);                     \
                }(__VA_ARGS__));                                               \
                std::cerr << std::endl;                                        \
        } while (0)
#define dbgv(x)                                                      \
        do {                                                         \
                std::cerr << "Line(" << __LINE__ << ") " #x " => ["; \
                int _i = 0;                                          \
                for (auto &_e : (x))                                 \
                        std::cerr << (_i++ ? ", " : "") << _e;       \
                std::cerr << "]" << std::endl;                       \
        } while (0)
#else
#define dbg(...) 39
#define dbgv(...) 39
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
        for (auto &e : res) e = value;
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

using mint = Modint<1000000007>;
constexpr int MAXVAL = 2e6;
mint fact[MAXVAL + 1];

void precompute() {
        fact[0] = 1;
        for (int i = 1; i <= MAXVAL; i++) fact[i] = fact[i-1] * i;
}

mint Comb(int n, int m) {
        assert(n >= m);
        return fact[n] / (fact[m] * fact[n-m]);
}

void solve() {
        int N;
        cin >> N;
        string S;
        cin >> S;
        if (N & 1) {
                cout << 0 << '\n';
                return;
        }
        int h = 0;
        for (auto &c : S) {
                h += (c == '(' ?  1 : -1);
                if (h < 0) {
                        cout << 0 << '\n';
                        return;
                }
        }
        int a = (N - S.size() - h) / 2;
        if (a < 0) {
                cout << 0 << '\n';
                return;
        }
        cout << Comb(2 * a + h, a) - Comb(2 * a + h, a - 1) << '\n';
}

int main() {
#ifndef LOCAL
        cin.tie(nullptr)->sync_with_stdio(false);
#endif
        precompute();
        solve();
        return 0;
}
