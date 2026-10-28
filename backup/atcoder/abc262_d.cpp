#include <bits/stdc++.h>
#include <atcoder/modint.hpp>
#include <cassert>
#define RED_BOLD "\033[1;31m"
#define WHITE_NORMAL "\033[0m"
template <class T> requires requires(T x) {
        x.val();
}
struct std::formatter<T> : std::formatter<unsigned> {
        auto format(T x, auto &c) const {
                return std::formatter<unsigned>::format(x.val(), c);
        }
};
#if defined(LOCAL) && __cplusplus >= 202302L
#define dbg(...)                                                             \
        ([](auto &&...a) {                                                   \
                std::string V[] = { std::format("{}", a)... },               \
                            K[sizeof...(a)];                                 \
                size_t i = 0, d = 0, w = 0;                                  \
                for (char c : #__VA_ARGS__)                                  \
                        if (c == ',' && !d)                                  \
                                i++;                                         \
                        else if (d += (c == '(' || c == '[' || c == '{' ||   \
                                       c == '<') -                           \
                                      (c == ')' || c == ']' || c == '}' ||   \
                                       c == '>');                            \
                                 c && (c != ' ' || K[i].size()))             \
                                w = std::max(w, (K[i] += c).size());         \
                std::println(stderr, RED_BOLD "#{}" WHITE_NORMAL, __LINE__); \
                for (i = 0; auto &v : V)                                     \
                        std::println(stderr,                                 \
                                     RED_BOLD "{:<{}} | {}" WHITE_NORMAL,    \
                                     K[i++], w, v);                          \
        }(__VA_ARGS__))
#define log(msg)                                                      \
        std::println(stderr, "{}#{}\n{}{}", RED_BOLD, __LINE__, #msg, \
                     WHITE_NORMAL)
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

void solve() {
        int N;
        cin >> N;
        vector<lli> A(N);
        cin >> A;
        mint ans = 0;
        for (int items = 1; items <= N; items++) {
                vector dp(items + 1, vector<mint>(items, 0));
                dp[0][0] = 1;
                for (int j = 0; j < N; j++) {
                        for (int k = items; k > 0; k--) {
                                for (int val = 0; val < items; val++) {
                                        dp[k][(val + A[j]) % items] +=
                                                dp[k - 1][val];
                                }
                        }
                }
                ans += dp[items][0];
                dbg(items, dp);
        }
        cout << ans.val() << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        cin.exceptions(cin.failbit);
        solve();
        return 0;
}
