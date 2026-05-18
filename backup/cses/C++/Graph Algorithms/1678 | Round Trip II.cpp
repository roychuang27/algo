#pragma GCC optimize("Ofast")
#include <algorithm>
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
        // cerr << cur << endl;
    } while (cur != from);
    res.eb(from);
    cout << SZ(res) << '\n';
    reverse(ALL(res));
    printv(res);
    flag = 0;
}

void dfs(vector<vector<int>> &adj, vector<int> &parent, vector<bool> &eliminated, int cur) {
    if (!flag) return;
    if (eliminated[cur]) return;
    for (auto nxt : adj[cur]) {
        if (parent[nxt] == -1) {
            parent[nxt] = cur;
            dfs(adj, parent, eliminated, nxt);
        } else {
            if (!eliminated[nxt]) {
                parent[nxt] = cur;
                backtrace(parent, nxt);
                return;
            } else {
                continue;
            }
        }
    }
    eliminated[cur] = 1;
}
 
void solve() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> adj(N+1);
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].eb(b);
    }
    vector<int> parent(N+1, -1);
    vector<int> root(N+1, -1);
    vector<bool> eliminated(N+1, 0);
    for (int i = 1; i <= N; i++) {
        if (!flag) break;
        if (root[i] != -1) continue;
        root[i] = i;
        dfs(adj, parent, eliminated, i);
    }
 
    if (flag) cout << "IMPOSSIBLE\n";
}
 
int main() {
    fastio;
    solve();
    return 0;
}