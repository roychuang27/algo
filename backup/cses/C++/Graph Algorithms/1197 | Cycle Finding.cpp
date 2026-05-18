#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
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
 
constexpr lli INF = 1e18;
 
int dfs(vector<vector<pair<int, lli>>> &adj, vector<bool> &visited, vector<lli> &val, vector<int> &path, int from, lli s) {
    if (visited[from]) {
        if (s >= val[from]) {
            return 0;
        }
        path.eb(from);
        return 1;
    }
    visited[from] = 1;
    path.eb(from);
    val[from] = s;
    for (auto &[nxt, w] : adj[from]) {
        int ret = dfs(adj, visited, val, path, nxt, s+w);
        if (ret == 1) return 1;
    }
    visited[from] = 0;
    path.pop_back();
    return 0;
}
 
void solve() {
    int N, M;
    cin >> N >> M;
    vector<tuple<int, int,lli>> edge_list;
    vector<vector<pair<int, lli>>> adj(N+1);
    for (int i = 0; i < M; i++) {
        int a, b;
        lli c;
        cin >> a >> b >> c;
        edge_list.eb(a, b, c);
        adj[b].eb(a, c);
    }
 
    vector<lli> dist(N+1, INF);
    vector<int> parent(N+1);
    dist[1] = 0;
    for (int i = 0; i < N-1; i++) {
        for (const auto &[a, b, w] : edge_list) {
            if (dist[b] > dist[a] + w) {
                dist[b] = dist[a] + w;
                parent[b] = a;
            }
        }
    }
 
    vector<int> stk;
    vector<bool> visited(N+1, 0);
    // check
    for (auto &[a, b, w] : edge_list) {
        if (dist[b] > dist[a] + w) { // neg cycle
            cout << "YES\n";
            stk.push_back(b);
            visited[b] = 1;
            while (!visited[a]) {
                stk.push_back(a);
                visited[a] = 1;
                a = parent[a];
            }
            stk.push_back(a);
            reverse(ALL(stk));
            cout << stk[0] << ' ';
            for (int i = 1; i < SZ(stk); i++) {
                cout << stk[i] << ' ';
                if (stk[i] == a) break;
            }
            return;
        }
    }
 
    cout << "NO";
}
 
int main() {
    fastio;
    solve();
    return 0;
}