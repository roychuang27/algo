#include <bits/stdc++.h>
using namespace std;

const int dx[4] = {-1, 0, 0, 1};
const int dy[4] = {0, 1, -1, 0};

void solution() {
        int H, W, K;
        cin >> H >> W >> K;
        vector<string> g(H);
        for (int i = 0; i < H; i++)
                cin >> g[i];
        vector<bool> row(H, 1), col(W, 1);
        queue<tuple<int, int, int>> qu;
        for (int i = 0; i < H; i++) {
                for (int j = 0; j < W; j++) {
                        if (g[i][j] == '#') {
                                row[i] = 0;
                                col[j] = 0;
                        }
                }
        }

        for (int i = 0; i < H; i++) if (row[i]) {
                for (int j = 0; j < W; j++) if (col[j]) {
                        qu.emplace(i, j, 0);
                }
        }

        int ans = 0;
        vector vis(H, vector<bool> (W, 0));

        while (!qu.empty()) {
                const auto [i, j, d] = qu.front();
                qu.pop();
                if (d > K or vis[i][j]) continue;
                vis[i][j] = 1;
                ans++;
                // cerr << i << ' ' << j << endl;
                for (int k = 0; k < 4; k++) {
                        int ni = i + dy[k], nj = j + dx[k];
                        if (-1 < ni and ni < H and -1 < nj and nj < W and g[ni][nj] != '#' and !vis[ni][nj]) {
                                qu.emplace(ni, nj, d+1);
                        }
                }
        }

        cout << ans << '\n';
}

int main() {
        cin.tie(0)->sync_with_stdio(0);
        solution();
        return 0;
}
