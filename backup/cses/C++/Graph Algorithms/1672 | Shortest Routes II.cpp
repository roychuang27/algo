/*
 * Submission ID: 14673749
 * Problem: Shortest Routes II
 * Link: https://cses.fi/problemset/task/1672
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

constexpr lli infty = 500'000'000'000'000'000;

void solve() {
    int N, M, Q;
    cin >> N >> M >> Q;
    vector<vector<lli>> adj_matrix(N+1, vector<lli> (N+1, infty));

    for (int i = 0; i < M; i++) {
        int a, b; lli c;
        cin >> a >> b >> c;
        adj_matrix[a][b] = min(c, adj_matrix[a][b]);
        adj_matrix[b][a] = min(c, adj_matrix[b][a]);
    }

    for (int i = 1; i <= N; i++) adj_matrix[i][i] = 0;

    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                adj_matrix[i][j] = min(adj_matrix[i][k] + adj_matrix[k][j], adj_matrix[i][j]);
            }
        }
    }

    while (Q--) {
        int a, b;
        cin >> a >> b;
        if (adj_matrix[a][b] != infty)
            cout << adj_matrix[a][b] << '\n';
        else
            cout << -1 << '\n';
    }

}

int main() {
    fastio;
    solve();
    return 0;
}