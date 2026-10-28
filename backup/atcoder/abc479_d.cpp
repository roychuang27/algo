#include <bits/stdc++.h>
#include <cassert>
#include <cstdio>
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

void solve() {
        int n, q;
        cin >> n >> q;
        vector<long long> ls(n), rs(n);
        for (int i = 1; i < n; i++) cin >> ls[i];
        for (int i = 0; i < n - 1; i++) cin >> rs[i];

        vector<long long> pre_mn(n), suf_mn(n);
        pre_mn[0] = rs[0];
        for (int i = 1; i < n - 1; i++) pre_mn[i] = min(pre_mn[i - 1], rs[i]);
        suf_mn[n - 1] = ls[n - 1];
        for (int i = n - 2; i > 0; i--) suf_mn[i] = min(suf_mn[i + 1], ls[i]);

        for (int _ = 0; _ < q; _++) {
                int s, t;
                cin >> s >> t;
                s--;
                t--;

                if (s < t) {
                        if (s > 0) {
                                cout << min(rs[s], pre_mn[s - 1] + ls[s]) << '\n';
                        } else {
                                cout << rs[s] << '\n';
                        }
                } else {
                        if (s < n - 1) {
                                cout << min(ls[s], suf_mn[s + 1] + rs[s]) << '\n';
                        } else {
                                cout << ls[s] << '\n';
                        }
                }
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
