#pragma GCC optimize("Ofast")
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

bool flag = 1;

void dfs(vector<vector<int>> &adj, int cur, int prev, vector<int> &color) {
    color[cur] = (color[prev] == 1 ? 2 : 1);
    for (auto nxt : adj[cur]) {
        if (color[nxt] != 0) {
            if (color[nxt] != color[cur]) {
                continue;
            } else {
                flag = 0;
                return;
            }
        } else {
            dfs(adj, nxt, cur, color);
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
    vector<int> color(N+1, 0);
    color[0] = 3;
    for (int i = 1; i <= N; i++) {
        if (color[i] == 0) {
            dfs(adj, i, 0, color);
        }
    }
    if (flag) {
        for (int i = 1; i <= N; i++) cout << color[i] << " \n"[i == N];
    } else {
        cout << "IMPOSSIBLE\n";
    }
}

int main() {
    fastio;
    solve();
    return 0;
}