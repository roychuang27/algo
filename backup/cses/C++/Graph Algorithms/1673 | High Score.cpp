/*
 * Submission ID: 14714123
 * Problem: High Score
 * Link: https://cses.fi/problemset/task/1673
 */

#pragma GCC optimize("Ofast")
#include <iostream>
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

lli INF = 1e18;

void solve() {
    int N, M;
    cin >> N >> M;
    vector<tuple<int, int, lli>> edges_list;
    vector<bool> connected_to_N(N+1, 0);
    connected_to_N[N] = 1;
    for (int i = 0; i < M; i++) {
        int a, b;
        lli x;
        cin >> a >> b >> x;
        edges_list.eb(a, b, x);
        if (b == N) connected_to_N[a] = 1;
    }
    // for (int i = 1; i <= N; i++) cerr << connected_to_N[i] << ' ';
    vector<lli> distance(N+1, -INF);
    vector<bool> reachable(N+1, 0);
    reachable[1] = 1;
    distance[1] = 0;
    for (int i = 1; i <= N - 1; i++) {
        bool relax = 0;
        for (const auto &[a, b, w] : edges_list) {
            if (distance[b] < distance[a] + w) {
                relax = 1;
                distance[b] = distance[a] + w;
            }
            if (reachable[a]) reachable[b] = 1;
            if (connected_to_N[b]) connected_to_N[a] = 1;
        }
        if (!relax) break;
    }
    // check
    for (const auto &[a, b, w] : edges_list) {
        if (reachable[a] and distance[b] < distance[a] + w and connected_to_N[b]) {
            cout << "-1\n";
            return;
        }
    }

    cout << distance[N] << '\n';

}

int main() {
    fastio;
    solve();
    return 0;
}