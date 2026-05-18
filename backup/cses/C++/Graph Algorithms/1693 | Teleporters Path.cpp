#include <algorithm>
#include <iostream>
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
    vector<vector<int>> adj;
    vector<int> in_deg, out_deg;
    vector<int> path;
    int N, M;

    GRAPH(int n, int m): N(n), M(m) {
        adj.resize(N+1);
        in_deg.resize(N+1);
        fill(ALL(in_deg), 0);
        out_deg.resize(N+1);
        fill(ALL(out_deg), 0);
    }

    void add_directed_edge(int a, int b) {
        adj[a].eb(b);
        out_deg[a]++;
        in_deg[b]++;
    }

    bool is_possible() {
        if (!(out_deg[1]-in_deg[1] == 1 and in_deg[N]-out_deg[N] == 1)) return false;
        for (int i = 2; i <= N - 1; i++) {
            if (out_deg[i] - in_deg[i] != 0) return false;
        }
        return true;
    }

    void dfs(int cur) {
        while (out_deg[cur] > 0) {
            dfs(adj[cur][--out_deg[cur]]);
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
        graph.add_directed_edge(a, b);
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