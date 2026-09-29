#include <bits/stdc++.h>
#include <cassert>
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

const int B = 31;

void solve() {
        int N, M;
        cin >> N >> M;
        vector<vector<int>> adj(N);
        for (int _ = 1; _ < N; _++) {
                int u, v;
                cin >> u >> v;
                u--;
                v--;
                adj[u].emplace_back(v);
                adj[v].emplace_back(u);
        }

        vector table(N, array_fill<int, B>(0));
        vector<int> tin(N), tout(N);
        int timer = 1;
        auto dfs_build = [&](auto &&self, int cur, int par) -> void {
                tin[cur] = timer++;
                table[cur][0] = par;
                for (int &nxt : adj[cur]) if (nxt != par) {
                        self(self, nxt, cur);
                }
                tout[cur] = timer++;
        };
        dfs_build(dfs_build, 0, 0);
        for (int b = 1; b < B; b++) {
                for (int i = 0; i < N; i++) {
                        table[i][b] = table[table[i][b-1]][b-1];
                }
        }
        auto anc = [&](int f, int s) -> bool {
                return tin[f] <= tin[s] and tout[s] <= tout[f];
        };
        auto lca = [&](int a, int b) -> int {
                if (anc(a, b)) return a;
                if (anc(b, a)) return b;
                for (int j = B-1; j >= 0; j--) {
                        if (!anc(table[a][j], b)) a = table[a][j];
                }
                return table[a][0];
        };

        vector<int> dp(N, 0);
        for (int _ = 0; _ < M; _++) {
                int u, v;
                cin >> u >> v;
                u--;
                v--;
                int l = lca(u, v);
                dp[l]--;
                if (l != 0) {
                        dp[table[l][0]]--;
                }
                dp[u]++;
                dp[v]++;
        }

        auto dfs_dp = [&](auto &&self, int cur, int par) -> void {
                for (int &nxt : adj[cur]) if (nxt != par) {
                        self(self, nxt, cur);
                        dp[cur] += dp[nxt];
                }
        };
        dfs_dp(dfs_dp, 0, 0);

        for (auto v : dp) cout << v << ' ';
        cout << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        cin.exceptions(cin.failbit);
        solve();
        return 0;
}
