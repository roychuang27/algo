#include <atcoder/modint.hpp>
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

using mint = atcoder::modint998244353;

constexpr int MAXVAL = 1e6;
bool is_prime[MAXVAL + 1];
vector<lli> primes;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

void precompute_primes() {
        primes.reserve(MAXVAL);
        for (int i = 2; i <= MAXVAL; i++)
                is_prime[i] = true;
        is_prime[0] = false;
        is_prime[1] = false;
        for (int i = 2; i <= MAXVAL; i++) {
                if (is_prime[i])
                        primes.emplace_back(i);
                for (lli p : primes) {
                        if (i * p > MAXVAL)
                                break;
                        is_prime[i * p] = false;
                        if (i % p == 0)
                                break;
                }
        }
}

lli lowest_multiple(lli x, lli p) {
        if (x % p) {
                return x - x % p + p;
        } else {
                return x;
        }
}

void solve() {
        lli N, K;
        cin >> N >> K;
        unordered_map<lli, int, custom_hash> prime_cnt;
        auto sieve = [&](lli L, lli R, int delta) -> void {
                unordered_map<lli, lli, custom_hash> tmp;
                for (lli i = L; i <= R; i++)
                        tmp[i] = i;
                for (lli p : primes) {
                        for (lli i = lowest_multiple(L, p); i <= R; i += p) {
                                while (tmp[i] % p == 0) {
                                        tmp[i] /= p;
                                        prime_cnt[p] += delta;
                                }
                        }
                }
                for (auto [key, val] : tmp) {
                        if (val != 1) {
                                prime_cnt[key] += delta;
                        }
                }
        };
        sieve(N-K+1, N, +1);
        sieve(1, K, -1);
        mint ans = 1;
        for (auto [key, val] : prime_cnt) {
                ans *= (val + 1);
        }
        cout << ans.val() << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        cin.exceptions(cin.failbit);
        precompute_primes();
        solve();
        return 0;
}
