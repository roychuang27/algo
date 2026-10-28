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
                  << WHITE_NORMAL << std::endl;
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
using lli = long long int;

void solve() {
        int n, m, s, t;
        cin >> n >> m >> s >> t;
        s--;
        t--;
        vector<vector<int>> adj(n);
        for (int _ = 0; _ < m; _++) {
                int u, v;
                cin >> u >> v;
                u--;
                v--;
                adj[u].emplace_back(v);
        }
        vector<vector<pair<int, int>>> adj_w(n);
        for (int u = 0; u < n; u++) {
                sort(ALL(adj[u]));
                for (size_t i = 0; i < adj[u].size(); i++) {
                        if (i == 0) {
                                adj_w[u].emplace_back(adj[u][i], 0);
                        } else {
                                adj_w[u].emplace_back(adj[u][i], 1);
                        }
                }
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>>> qu;
        vector<bool> vis(n);
        qu.push({0, s});
        while (!qu.empty()) {
                auto [d, cur] = qu.top();
                qu.pop();
                if (vis[cur]) continue;
                vis[cur] = 1;
                if (cur == t) {
                        cout << d << '\n';
                        return;
                }
                for (auto [v, w] : adj_w[cur]) {
                        qu.push({d + w, v});
                }
        }
        cout << -1 << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        cin.exceptions(cin.failbit);
        solve();
        return 0;
}
