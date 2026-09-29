#include <bits/stdc++.h>
#include <cassert>
#define RED_BOLD "\033[1;31m"
#define WHITE_NORMAL "\033[0m"
#if defined(LOCAL) && __cplusplus >= 202002L
template <class T> concept Iterable = requires(T x) {
        std::begin(x);
        std::end(x);
};
template <class T> concept TupleLike = requires {
        std::tuple_size<T>::value;
};
template <class T> void dbg_print(const T &x);
template <TupleLike T, size_t... I>
void dbg_print_tuple(const T &x, std::index_sequence<I...>) {
        std::cerr << '(';
        size_t i = 0;
        ((dbg_print(std::get<I>(x)),
          std::cerr << (++i == sizeof...(I) ? "" : ", ")),
         ...);
        std::cerr << ')';
}
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
        } else if constexpr (TupleLike<T>) {
                dbg_print_tuple(
                        x, std::make_index_sequence<std::tuple_size_v<T> >{});
        } else {
                std::cerr << x;
        }
}
#define dbg(...)                                                             \
        do {                                                                 \
                std::cerr << RED_BOLD << "#" << __LINE__ << '\n'             \
                          << "(" #__VA_ARGS__ ") = (";                       \
                bool _first = true;                                          \
                ([&](auto &&...args) {                                       \
                        ((std::cerr << (_first ? "" : ", "), _first = false, \
                          dbg_print(args)),                                  \
                         ...);                                               \
                }(__VA_ARGS__));                                             \
                std::cerr << ')' << WHITE_NORMAL << '\n';                    \
        } while (0)
#define checkpoint(x) cerr << RED_BOLD << x << WHITE_NORMAL << endl
#else
#define dbg(...) 39
#define checkpoint(...) 39
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

struct Tree {
        int N, K;
        vector<vector<int>> adj;
        vector<int> sz;
        vector<int> cnt;
        vector<char> removed;
        int mx_depth;
        lli ans = 0;

        int get_subtr_sz(int cur, int par) {
                sz[cur] = 1;
                for (int &nxt : adj[cur]) {
                        if (!removed[nxt] and nxt != par) {
                                sz[cur] += get_subtr_sz(nxt, cur);
                        }
                }
                return sz[cur];
        }

        int find_centroid(int n_div_2, int cur, int par) {
                for (int &nxt : adj[cur]) {
                        if (!removed[nxt] and nxt != par and sz[nxt] > n_div_2) {
                                return find_centroid(n_div_2, nxt, cur);
                        }
                }
                return cur;
        }

        void do_dp(int cur, int par, bool f, int depth) {
                if (depth > K) {
                        return;
                }
                chmax(mx_depth, depth);
                if (f) {
                        cnt[depth]++;
                } else {
                        ans += cnt[K - depth];
                }
                for (int &nxt : adj[cur]) {
                        if (!removed[nxt] and nxt != par) {
                                do_dp(nxt, cur, f, depth + 1);
                        }
                }
        }

        void centroid_decomposition(int cur) {
                int centroid = find_centroid(get_subtr_sz(cur, -1) / 2, cur, -1);
                removed[centroid] = true;
                mx_depth = 0;
                for (int &nxt : adj[centroid]) {
                        if (!removed[nxt]) {
                                do_dp(nxt, centroid, false, 1);
                                do_dp(nxt, centroid, true, 1);
                        }
                }
                fill(cnt.begin() + 1, cnt.begin() + mx_depth + 1, 0);
                for (int &nxt : adj[centroid]) {
                        if (!removed[nxt]) {
                                centroid_decomposition(nxt);
                        }
                }
        }

        Tree(vector<vector<int> > &v, int k)
                : N(v.size())
                , K(k)
                , adj(v)
                , sz(N)
                , cnt(K+1, 0)
                , removed(N, false) {
                cnt[0] = 1;
                centroid_decomposition(0);
        }
};

void solve() {
        int N, K;
        cin >> N >> K;
        vector<vector<int>> adj(N);
        for (int _ = 1; _ < N; _++) {
                int u, v;
                cin >> u >> v;
                u--;
                v--;
                adj[u].emplace_back(v);
                adj[v].emplace_back(u);
        }
        Tree tree(adj, K);
        cout << tree.ans << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        cin.exceptions(cin.failbit);
        solve();
        return 0;
}
