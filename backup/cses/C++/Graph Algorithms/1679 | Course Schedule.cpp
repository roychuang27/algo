/*
 * Submission ID: 14743050
 * Problem: Course Schedule
 * Link: https://cses.fi/problemset/task/1679
 */

#pragma GCC optimize("Ofast")
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

void dfs(vector<vector<int>> &adj, vector<int> &state, bool &cycle, vector<int> &toposort, int cur) {
    if (state[cur] == 1) {
        cycle = 1;
        return;
    }
    if (state[cur] == 2) return;
    state[cur] = 1;

    for (auto nxt : adj[cur]) {
        dfs(adj, state, cycle, toposort, nxt);
    }

    toposort.eb(cur);
    state[cur] = 2;
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
    bool cycle = 0;
    bool all = 0;
    vector<int> state(N+1, 0);
    vector<int> toposort;
    for (int i = 1; i <= N and !cycle; i++) {
        if (state[i] == 0) {
            dfs(adj, state, cycle, toposort, i);
        }
    }

    if (cycle or SZ(toposort) < N) {
        cout <<"IMPOSSIBLE";
    } else {
        reverse(ALL(toposort));
        printv(toposort);
    }

}

int main() {
    fastio;
    solve();
    return 0;
}