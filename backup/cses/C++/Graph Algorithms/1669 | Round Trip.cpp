#pragma GCC optimize("Ofast")
#include <iostream>
#include <vector>
#define fastio cin.tie(0)->sync_with_stdio(false)
#define eb emplace_back
#define test(x) cerr << "Line(" << __LINE__ << ") " #x << ' ' << x << endl
#define printv(x) { \
    for (auto i : x) cout << i << ' '; \
    cout << '\n'; \
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

bool flag = 1;

void backtrace(vector<int> &parents, int from) {
    if (!flag) return;
    vector<int> res;
    int cur = from;
    do {
        res.eb(cur);
        cur = parents[cur];
    } while (cur != from);
    res.eb(from);
    cout << SZ(res) << '\n';
    printv(res);
    flag = 0;
}

void dfs(vector<vector<int>> &adj, vector<int> &parents, vector<bool> &visited, int cur) {
    if (!flag) return;
    visited[cur] = 1;
    for (auto nxt : adj[cur]) {
        if (nxt == parents[cur]) continue;
        if (parents[nxt] == -1) {
            parents[nxt] = cur;
            dfs(adj, parents, visited, nxt);
        } else {
            parents[nxt] = cur;
            backtrace(parents, nxt);
        }
    }
}

void solve() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> adj(N+1);
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].eb(b);
        adj[b].eb(a);
    }
    vector<bool> visited(N+1, 0);
    vector<int> parents(N+1, -1);
    visited[0] = 1;
    for (int i = 1; i <= N; i++) {
        if (!flag) break;
        if (visited[i]) continue;
        parents[i] = 0;
        dfs(adj, parents, visited, i);
    }

    if (flag) cout << "IMPOSSIBLE\n";
}

int main() {
    fastio;
    solve();
    return 0;
}