#include <bits/stdc++.h>
#include <atcoder/dsu>
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

struct Graph {
        int N;
        vector<vector<int>> adj;
        vector<vector<int>> adj_reversed;
        vector<int> dfs_post_order;
        vector<bool> visited;
        vector<int> scc;
        vector<vector<int>> scc_members;
        vector<vector<int>> adj_scc;
        vector<int> toposort_on_scc;
        int scc_cnt;
        bool cycle_between_scc;
        vector<int> state;

        Graph(int n)
                : N(n)
                , adj(N)
                , adj_reversed(N)
                , visited(N)
                , scc(N)
                , scc_cnt(0)
                , cycle_between_scc(0),
                state(N, 0) {
        }

        void reset_visited_arr() {
                fill(ALL(visited), 0);
        }

        void add_directed_edge(int u, int v) {
                adj[u].emplace_back(v);
                adj_reversed[v].emplace_back(u);
        }

        void dfs_find_order(int cur) {
                if (visited[cur])
                        return;
                visited[cur] = 1;

                for (const auto &nxt : adj[cur]) {
                        dfs_find_order(nxt);
                }

                dfs_post_order.emplace_back(cur);
        }

        void sfd_find_scc(int cur, int scc_id) {
                if (visited[cur])
                        return;
                visited[cur] = 1;
                scc[cur] = scc_id;

                for (const auto &nxt : adj_reversed[cur]) {
                        sfd_find_scc(nxt, scc_id);
                }
        }

        void find_scc() {
                reset_visited_arr();
                for (int i = 0; i < N; i++) if (!visited[i]) {
                        dfs_find_order(i);
                }

                reverse(ALL(dfs_post_order));
                reset_visited_arr();
                for (int i : dfs_post_order) if (!visited[i]) {
                        sfd_find_scc(i, scc_cnt);
                        scc_cnt++;
                }
        }

        bool in_same_scc(int u, int v) {
                return scc[u] == scc[v];
        }

        void build_scc_graph() {
                adj_scc.resize(scc_cnt);
                scc_members.resize(scc_cnt);

                for (int i = 0; i < N; i++) {
                        scc_members[scc[i]].emplace_back(i);
                        for (const auto &nxt : adj[i]) {
                                if (scc[nxt] != scc[i]) {
                                        adj_scc[scc[i]].emplace_back(scc[nxt]);
                                }
                        }
                }
        }

        bool find_toposort_on_scc() {
                dbg(adj_scc);
                toposort_on_scc.reserve(N);
                for (int i = 0; i < scc_cnt and !cycle_between_scc; i++) {
                        if (state.at(i) == 0) {
                                dfs_on_scc(i);
                        }
                }
                reverse(ALL(toposort_on_scc));
                return cycle_between_scc;
        }

        void dfs_on_scc(int cur) {
                if (state.at(cur) == 1) {
                        cycle_between_scc = 1;
                        return;
                }
                if (state.at(cur) == 2) {
                        return;
                }
                state.at(cur) = 1;
                for (int nxt : adj_scc.at(cur)) {
                        dfs_on_scc(nxt);
                }
                toposort_on_scc.emplace_back(cur);
                state.at(cur) = 2;
        }
};

void solve() {
        int N, Q;
        cin >> N >> Q;
        Graph g(N);
        vector<array<int, 3>> qs(Q);
        for (int _ = 0; _ < Q; _++) {
                int t, u, v;
                cin >> t >> u >> v;
                u--;
                v--;
                g.add_directed_edge(u, v);
                qs.at(_) = {t, u, v};
        }
        g.find_scc();
        g.build_scc_graph();
        vector<int> ans(N, N);
        dbg(g.scc_members);
        g.find_toposort_on_scc();
        dbg(g.toposort_on_scc);
        for (int v : g.toposort_on_scc) {
                for (int i : g.scc_members.at(v)) {
                        ans.at(i) = v + 1;
                }
        }
        dbg(ans);
        for (auto [t, u, v] : qs) {
                if (t == 1 and ans.at(u) == ans.at(v)) {
                        cout << "No\n";
                        return;
                }
        }
        cout << "Yes\n";
        for (int i : ans)
                cout << i << ' ';
        cout << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        cin.exceptions(cin.failbit);
        solve();
        return 0;
}
