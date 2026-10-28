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

void solve() {
        int N;
        cin >> N;
        vector<pair<int, int>> edges(N-1);
        vector<vector<int>> adj(N);
        vector<lli> d(N, 0);
        for (auto &[a, b] : edges) {
                cin >> a >> b;
                a--;
                b--;
                adj[a].emplace_back(b);
                adj[b].emplace_back(a);
        }
        vector<int> subtr_sz(N, 1);
        [&](this auto &&self, int cur, int par) -> int {
                for (int nxt : adj[cur]) if (nxt != par) {
                        subtr_sz[cur] += self(nxt, cur);
                }
                return subtr_sz[cur];
        }(0, 0);
        for (int i = 0; i < N-1; i++) {
                auto [u, v] = edges[i];
                if (subtr_sz[u] < subtr_sz[v])
                        swap(u, v);
                if (subtr_sz[v] > N - subtr_sz[v]) {
                        d[v] += i + 1;
                } else {
                        d[0] += i + 1;
                        d[v] -= i + 1;
                }
        }
        [&](this auto &&self, int cur, int par) -> void {
                if (par != -1)
                        d[cur] += d[par];
                for (int nxt : adj[cur]) if (nxt != par) {
                        self(nxt, cur);
                }
        }(0, -1);
        for (auto i : d) cout << i << ' ';
        cout << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        cin.exceptions(cin.failbit);
        solve();
        return 0;
}
