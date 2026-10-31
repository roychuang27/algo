#include <bits/stdc++.h>
#include <cassert>
#define RED_BOLD "\033[1;31m"
#define WHITE_NORMAL "\033[0m"
#if defined(LOCAL) && __cplusplus >= 202302L
#define line(...) std::println(stderr, RED_BOLD "#{} passed" WHITE_NORMAL, __LINE__)
#define dbg(...)                                                                             \
        std::println(stderr, RED_BOLD "#{}, ({}) = {}" WHITE_NORMAL, __LINE__, #__VA_ARGS__, \
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
using namespace std;

struct DSU {
        int N;
        vector<int> f, xor_edge;
        vector<array<int, 2> > siz;
        int ans = 0;

        DSU(int n): N(n), f(n), xor_edge(n), siz(n, {1, 0}) {
                std::iota(ALL(f), 0);
        }

        int find(int x) {
                if (f[x] == f[f[x]]) { // f[x] is root
                        return f[x];
                }
                find(f[x]);
                xor_edge[x] ^= xor_edge[f[x]]; // merge xor edges
                f[x] = f[f[x]];
                return f[x];
        }

        bool merge(int x, int y) {
                int fx = find(x);
                int fy = find(y);

                if (fx == fy) {
                        return xor_edge[x] != xor_edge[y];
                }

                ans -= min(siz[fx][0], siz[fx][1]);
                ans -= min(siz[fy][0], siz[fy][1]);

                int w = (xor_edge[x] == xor_edge[y]);
                siz[fx][0] += siz[fy][w];
                siz[fx][1] += siz[fy][1 ^ w];
                f[fy] = fx;
                xor_edge[fy] = w;

                ans += min(siz[fx][0], siz[fx][1]);
                return true;
        }
};

void solve() {
        int N, Q;
        cin >> N >> Q;

        DSU dsu(N);
        bool bipart = true;
        for (int _ = 0; _ < Q; _++) {
                int u, v;
                cin >> u >> v;
                u--;
                v--;

                if (bipart and !dsu.merge(u, v)) {
                        bipart = false;
                }

                if (bipart) {
                        cout << dsu.ans << '\n';
                } else {
                        cout << -1 << '\n';
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
