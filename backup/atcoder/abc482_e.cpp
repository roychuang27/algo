#include <bits/stdc++.h>
#include <cassert>
#define RED_BOLD "\033[1;31m"
#define WHITE_NORMAL "\033[0m"
// I'll give them a shelter like you've done for me
#if defined(SHELTER) && defined(__cpp_lib_print)
#define line(...) \
        std::println(stderr, RED_BOLD "#{} passed" WHITE_NORMAL, __LINE__)
#define dbg(...)                                             \
        std::println(stderr,                                 \
                     RED_BOLD "#{}, ({}) = {}" WHITE_NORMAL, \
                     __LINE__,                               \
                     #__VA_ARGS__,                           \
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
template <class T, class U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p) {
        return os << p.first << ' ' << p.second;
}
template <class T>
struct ITER {
        const T &_v;
        std::string _sep = " ";
        ITER(const T &v, std::string sep = " "):
                _v(v),
                _sep(sep) {
        }
        ITER(const T &v, char sep = ' '):
                _v(v),
                _sep(sep, 1) {
        }
        friend std::ostream &operator<<(std::ostream &os, const ITER &o) {
                bool first = true;
                for (const auto &x : o._v) {
                        if (!first) {
                                os << o._sep;
                        }
                        first = false;
                        os << x;
                }
                return os;
        }
};

using namespace std;

void single_testcase() {
        int n;
        cin >> n;
        vector<vector<int>> adj(n);
        for (int _ = 0; _ < n - 1; _++) {
                int u, v;
                cin >> u >> v;
                u--;
                v--;
                adj[u].emplace_back(v);
                adj[v].emplace_back(u);
        }

        vector<int> color(n);
        cin >> color;
        for (auto &x : color) x--;

        auto bfs_dist = [&](int src) -> vector<int> {
                vector<int> dist(n, n);
                dist[src] = 0;
                queue<int> qu;
                qu.push(src);
                while (!qu.empty()) {
                        int cur = qu.front();
                        qu.pop();
                        for (int nxt : adj[cur]) {
                                if (dist[nxt] == n) {
                                        dist[nxt] = dist[cur] + 1;
                                        qu.push(nxt);
                                }
                        }
                }
                return dist;
        };

        auto find_furthest_vert = [&](const vector<int> &dist) {
                return max_element(ALL(dist)) - dist.begin();
        };

        auto dist0 = bfs_dist(0);
        int v1 = find_furthest_vert(dist0);
        auto dist1 = bfs_dist(v1);
        int v2 = find_furthest_vert(dist1);
        auto dist2 = bfs_dist(v2);

        int diam = dist1[v2];
        long long ans = 0;

        if (diam & 1) {
                int c1 = -1, c2 = -1;
                for (int i = 0; i < n; i++) {
                        if (dist1[i] == (diam - 1) / 2 and dist2[i] == (diam + 1) / 2) {
                                c1 = i;
                        }
                        if (dist1[i] == (diam + 1) / 2 and dist2[i] == (diam - 1) / 2) {
                                c2 = i;
                        }
                }
                dbg(c1, c2);
                vector<int> count1(n), count2(n);
                auto dfs = [&](this auto self, int cur, int par, int d, vector<int> &count) -> void {
                        if (d == (diam - 1) / 2) {
                                count[color[cur]]++;
                        }

                        for (int nxt : adj[cur]) {
                                if (nxt == par) {
                                        continue;
                                }
                                self(nxt, cur, d + 1, count);
                        }
                };
                dfs(c1, c2, 0, count1);
                dfs(c2, c1, 0, count2);
                for (int i = 0; i < n; i++) {
                        ans += 1LL * count1[i] * count2[i];
                }
        } else {
                int c = -1;
                for (int i = 0; i < n; i++) {
                        if (dist1[i] == diam / 2 and dist2[i] == diam / 2) {
                                c = i;
                        }
                }
                dbg(c);
                vector<int> count_all(n), count_subtr(n);
                stack<int> modified;
                auto dfs = [&](this auto self, int cur, int par, int d) -> void {
                        if (d == diam / 2) {
                                ans += count_all[color[cur]]++;
                                ans -= count_subtr[color[cur]]++;
                                modified.push(color[cur]);
                        }
                        for (int nxt : adj[cur]) {
                                if (nxt == par) {
                                        continue;
                                }
                                self(nxt, cur, d + 1);
                        }
                };

                for (int nxt : adj[c]) {
                        dfs(nxt, c, 1);
                        while (!modified.empty()) {
                                count_subtr[modified.top()] = 0;
                                modified.pop();
                        }
                }
        }

        cout << ans;
}

int main() {
        std::cin.tie(nullptr)->sync_with_stdio(false);
        std::cin.exceptions(std::cin.failbit);
        int t = 1;
        // std::cin >> t;
        for (int i = 0; i < t; i++) {
                if (i) {
                        std::cout << '\n';
                }
                single_testcase();
        }
        return 0;
}
