/*
 * Submission ID: 15951506
 * Problem: Knight's Tour
 * Link: https://cses.fi/problemset/task/1689
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>
#define test(x) cerr << "Line(" << __LINE__ << ") " #x << ' ' << x << endl
#define printv(x)                          \
{                                          \
        for (auto i : x) cout << i << ' '; \
        cout << endl;                      \
}
#define SQ(x) ((x) * (x))
#define SZ(x) ((int)x.size())

using namespace std;
using lli = long long int;

const int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
const int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};

bool is_valid(vector<vector<int>> &grid, int i, int j) {
        if (i < 0 or j < 0) return false;
        if (i > 7 or j > 7) return false;
        return grid[i][j] == 0;
}

int h(vector<vector<int>> &grid, int i, int j) {
        int res = 0;
        if (!is_valid(grid, i, j)) return -1;
        for (int k = 0; k < 8; k++) res += is_valid(grid, i+dy[k], j+dx[k]);
        return res;
}

vector<vector<int>> dfs(vector<vector<int>> grid, int x, int y, int c) {
        grid[y][x] = c;
        if (c == 64) return grid;
        vector<pair<int, int>> nxts;
        
        for (int k = 0; k < 8; k++) {
                int t = h(grid,  y+dy[k], x+dx[k]);
                if (t == -1) continue;
                nxts.emplace_back(t, k);
        }
        
        sort(nxts.begin(), nxts.end());
        
        for (auto &[_, i] : nxts) {
                auto ret = dfs(grid, x+dx[i], y+dy[i], c+1);
                if (SZ(ret) != 0) return ret;
        }
        return {};
}

void solution() {
        int x, y;
        cin >> x >> y;
        x--, y--;
        
        auto ans = dfs(vector<vector<int>> (8, vector<int> (8, 0)), x, y, 1);
        
        for (auto v : ans)
                printv(v);
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}