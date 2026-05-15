/*
 * Submission ID: 14673950
 * Problem: Mex Grid Construction
 * Link: https://cses.fi/problemset/task/3419
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

int report_mex(vector<int> &nums, int N) {
    vector<bool> used(10000, 0);
    for (auto &x : nums) used[x] = 1;
    for (int i = 0; i <= 10000; i++) if (!used[i]) return i;
    return 0;
}

int get_grid_pos(vector<vector<int>> &grid, int i, int j) {
    return grid[max(i, j)][min(i, j)];
}

void solve() {
    int N; cin >> N;
    vector<vector<int>> grid(N, vector<int> (N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            vector<int> nums;
            for (int k = 0; k < i; k++) {
                nums.eb(get_grid_pos(grid, k, j));
            }
            for (int k = 0; k < j; k++) {
                nums.eb(get_grid_pos(grid, i, k));
            }
            grid[i][j] = report_mex(nums, N);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << get_grid_pos(grid, i, j) << ' ';
        }
        cout << '\n';
    }
}

int main() {
    fastio;
    solve();
    return 0;
}