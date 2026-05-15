/*
 * Submission ID: 14628414
 * Problem: Flight Routes Check
 * Link: https://cses.fi/problemset/task/1682
 */

#pragma GCC optimize("Ofast")
#include <iostream>
#include <queue>
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

void bfs(vector<vector<int>> &adj, vector<bool> &visited) {
    queue<int> ord;
    ord.push(1);
    while (!ord.empty()) {
        int cur = ord.front();
        ord.pop();
        if (visited[cur]) continue;
        visited[cur] = 1;
        for (auto nxt : adj[cur]) {
            if (!visited[nxt]) ord.push(nxt);
        }
    }
}

void solve() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> adj1(N+1), adj2(N+1);
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        adj1[a].eb(b);
        adj2[b].eb(a);
    }
    vector<bool> visited1(N+1, 0), visited2(N+1, 0);
    bfs(adj1, visited1);
    bfs(adj2, visited2);
    for (int i = 2; i <= N; i++) {
        if (!visited1[i]) {
            cout << "NO\n";
            cout << 1 << ' ' << i;
            return;
        }
    }
    for (int i = 2; i <= N; i++) {
        if (!visited2[i]) {
            cout << "NO\n";
            cout << i << ' ' << 1;
            return;
        }
    }
    cout << "YES\n";
}

int main() {
    fastio;
    solve();
    return 0;
}