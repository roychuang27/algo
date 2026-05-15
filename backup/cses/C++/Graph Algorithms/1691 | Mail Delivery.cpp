/*
 * Submission ID: 14757224
 * Problem: Mail Delivery
 * Link: https://cses.fi/problemset/task/1691
 */

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#define fastio cin.tie(0)->sync_with_stdio(false)
#define eb emplace_back
#define test(x) cerr << "Line(" << __LINE__ << ") " #x << ' ' << x << endl
#define printv(x) { \
    for (auto i : x) cout << i << ' '; \
    cout << endl; \
}
#define pii pair<int, int>
#define pll pair<lli, lli>
#define ALL(x) x.begin(), x.end()
#define rALL(x) x.rbegin(), x.rend()
#define MP(x, y) make_pair((x), (y))
#define SQ(x) ((x)*(x))
#define SZ(x) ((int) x.size())

using namespace std;
typedef long long int lli;

template <typename A, typename B>
ostream& operator << (ostream& o, pair<A, B> a) {
    return o << a.first << ' ' << a.second;
}
template <typename A, typename B>
istream& operator >> (istream& o, pair<A, B> &a) {
    return o >> a.first >> a.second;
}

class GRAPH {
    public:
    vector<vector<pair<int, int>>> adj;
    vector<int> path;
    vector<bool> visited_edge;
    vector<int> idx;
    int N, M;

    GRAPH(int n, int m): N(n), M(m) {
        adj.resize(N+1);
        idx.resize(N+1);
        fill(ALL(idx), 0);
        visited_edge.resize(M);
        fill(ALL(visited_edge), 0);
    }

    void add_directed_edge(int a, int b, int w) {
        adj[a].eb(b, w);
        adj[b].eb(a, w);
    }

    bool is_possible() {
        for (int i = 1; i <= N; i++) {
            if (SZ(adj[i]) % 2 != 0) return false;
        }
        return true;
    }

    void dfs(int cur) {
        while (idx[cur] < SZ(adj[cur])) {
            if (!visited_edge[adj[cur][idx[cur]].second]) {
                visited_edge[adj[cur][idx[cur]].second] = 1;
                dfs(adj[cur][idx[cur]].first);
            }
            idx[cur]++;
        }

        path.eb(cur);
    }

    vector<int> get_eulerian_path() {
        if (!is_possible()) return {};
        dfs(1);
        if (SZ(path)-1 != M) return {};
        reverse(ALL(path));
        return path;
    }
};

void solve() {
    int N, M;
    cin >> N >> M;
    GRAPH graph(N, M);

    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        graph.add_directed_edge(a, b, i);
    }

    auto res = graph.get_eulerian_path();

    if (SZ(res) == 0) {
        cout << "IMPOSSIBLE\n";
    } else {
        printv(res);
    }

}

int main() {
    fastio;
    solve();
    return 0;
}