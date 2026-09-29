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
template <class T, std::size_t n> auto array_fill(T value) {
        std::array<T, n> res;
        res.fill(value);
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

void precompute() {
}

void solve() {
        map<int, int> mp;
        int N;
        cin >> N;
        vector<int> v(N);
        cin >> v;
        for (int i = N-1; i >= 0; i--) {
                chmax(mp[v[i]], mp[v[i]+1]+1);
        }
        int ans = 0;
        for (auto &[v, c] : mp) {
                chmax(ans, c);
        }
        cout << ans << '\n';
}

int main() {
#ifndef LOCAL
        cin.tie(nullptr)->sync_with_stdio(false);
#endif
        precompute();
        solve();
        return 0;
}
