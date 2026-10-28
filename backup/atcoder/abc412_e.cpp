#include <bit>
#include <bits/stdc++.h>
#include <cassert>
#define RED_BOLD "\033[1;31m"
#define WHITE_NORMAL "\033[0m"
#if defined(LOCAL) && __cplusplus >= 202302L
#define dbg(...)                                                               \
        std::println(stderr, RED_BOLD "#{}\n({}) = {}" WHITE_NORMAL, __LINE__, \
                     #__VA_ARGS__, std::forward_as_tuple(__VA_ARGS__))
#define log(msg)                                                      \
        std::println(stderr,                                          \
                "{}#{}\n{}{}", RED_BOLD, __LINE__, #msg, WHITE_NORMAL)
#else
#define dbg(...) 39
#define log(...) 39
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

lli fpow(lli a, lli b, lli m) {
        lli res = 1;
        while (b) {
                if (b & 1) {
                        res *= a;
                        res %= m;
                }
                a *= a;
                a %= m;
                b >>= 1;
        }
        return res;
}

bool miller_test(unsigned long long n) {
        if (!(n & 1)) return false;
        constexpr array<int, 7> as = {2, 3, 5, 7, 11, 13, 17};
        int s = std::countr_zero(n - 1);
        unsigned long long d = (n - 1) >> s;
        for (int a : as) {
                __int128 x = fpow(a, d, n);
                for (int _ = 0; _ < s; _++) {
                        __int128 y = (x * x) % n;
                        if (y == 1 and x != 1 and x != n - 1) {
                                return false;
                        }
                        x = y;
                }
                if ((x * x) % n != 1) {
                        return false;
                }
        }
        return true;
}

constexpr int MAXVAL = 1e7;
bool is_prime[MAXVAL + 1];
vector<lli> primes;

void find_primes() {
        primes.reserve(MAXVAL);
        for (int i = 2; i <= MAXVAL; i++)
                is_prime[i] = 1;
        is_prime[0] = 0;
        is_prime[1] = 0;
        for (int i = 2; i <= MAXVAL; i++) {
                if (!is_prime[i])
                        continue;
                primes.emplace_back(i);
                for (int p : primes) {
                        if (i * p > MAXVAL)
                                break;
                        is_prime[i * p] = 0;
                        if (p % i == 0)
                                break;
                }
        }
}

void solve() {
        lli L, R;
        cin >> L >> R;
        int ans = 1; // L
        vector<int> vis(R - L);
        // segment sieve
        for (lli p : primes) {
                for (lli x = (L / p + 1) * p; x <= R; x += p) {
                        if (vis.at(x - L - 1))
                                continue;
                        vis.at(x - L - 1) = 1;
                        // p ^ k
                        lli y = x;
                        while (y % p == 0)
                                y /= p;
                        if (y == 1)
                                ans++;
                }
        }
        for (int v : vis)
                ans += v == 0; // primes
        cout << ans << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        cin.exceptions(cin.failbit);
        find_primes();
        log(precomute done);
        solve();
        return 0;
}
