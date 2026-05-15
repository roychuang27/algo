/*
 * Submission ID: 14725809
 * Problem: Flight Discount
 * Link: https://cses.fi/problemset/task/1195
 */

#pragma GCC optimize("Ofast")
#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
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

constexpr lli INF = 1e18;

vector<vector<lli>> dijkstra(vector<vector<pair<int, lli>>> &adj, int N, int from) {
    vector<vector<lli>> dist(2, vector<lli> (N+1, INF));
    dist[0][1] = 0;
    vector<vector<bool>> visited(2, vector<bool> (N+1, 0));
    priority_queue<tuple<lli, int, int>> pq;
    pq.push({0, from, 0});
    while (!pq.empty()) {
        auto [_, cur, discounted] = pq.top();
        pq.pop();
        if (visited[discounted][cur]) continue;
        visited[discounted][cur] = 1;
        for (const auto &[nxt, w] : adj[cur]) {
            if (dist[discounted][nxt] > dist[discounted][cur] + w) {
                dist[discounted][nxt] = dist[discounted][cur] + w;
                pq.push({-dist[discounted][nxt], nxt, discounted});
            }
            if (!discounted) {
                if (dist[1][nxt] > dist[0][cur] + w / 2) {
                    dist[1][nxt] = dist[0][cur] + w / 2;
                    pq.push({-dist[1][nxt], nxt, 1});
                }
            }
        }
    }
    return dist;
}

void solve() {
    int N, M;
    cin >> N >> M;
    vector<vector<pair<int, lli>>> adj(N+1);
    for (int i = 0; i < M; i++) {
        int a, b;
        lli c;
        cin >> a >> b >> c;
        adj[a].eb(b, c);
    }
    auto res = dijkstra(adj, N, 1);
    cout << min(res[0][N], res[1][N]) <<'\n';
}

int main() {
    fastio;
    solve();
    return 0;
}