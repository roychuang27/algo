/*
 * Submission ID: 14673835
 * Problem: Grid Coloring I
 * Link: https://cses.fi/problemset/task/3311
 */

#pragma GCC optimize("Ofast")
#include <array>
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

char get_another(array<bool, 4> &used) {
    for (int i = 0; i < 4; i++) {
        if (!used[i]) return 'A' + i;
    }
}

void solve() {
    int N, M;
    cin >> N >> M;
    vector<string> grid(N);
    for (int i = 0; i < N; i++) cin >> grid[i];

    vector<vector<char>> res(N, vector<char> (M));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            array<bool, 4> used = {0, 0, 0, 0};
            if (i != 0) used[res[i-1][j]-'A'] = 1;
            if (j != 0) used[res[i][j-1]-'A'] = 1;
            used[grid[i][j]-'A'] = 1;
            res[i][j] = get_another(used);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << res[i][j];
        }
        cout << '\n';
    }
}

int main() {
    fastio;
    solve();
    return 0;
}