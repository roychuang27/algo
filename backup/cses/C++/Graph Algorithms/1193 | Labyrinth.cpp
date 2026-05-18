#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>
#define test(x) cerr << "Line(" << __LINE__ << ") " #x << ' ' << x << endl

using namespace std;
using ll = long long;
typedef pair<int, int> pii;

const int di[4] = {-1, 1, 0, 0};
const int dj[4] = {0, 0, -1, 1};
const string directions = "UDLR";

const int inf = 1e9;

void solve() {
        int N, M;
        cin >> N >> M;
        vector<vector<bool>> visited(N + 2, vector<bool>(M + 2, 1));
        vector<vector<int>> distance(N + 2, vector<int> (M + 2, inf));
        vector<vector<int>> direction(N + 2, vector<int> (M + 2));
        int ai, aj, bi, bj;
        for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= M; j++) {
                        char c;
                        cin >> c;
                        if (c == '.') {
                                visited[i][j] = 0;
                        }
                        if (c == 'A') {
                                ai = i;
                                aj = j;
                                visited[i][j] = 0;
                        }
                        if (c == 'B') {
                                bi = i;
                                bj = j;
                                visited[i][j] = 0;
                        }
                }
        }
        queue<pair<int, int>> qu;
        qu.push({ai, aj});
        distance[ai][aj] = 0;
        visited[ai][aj] = 1;
        while (!qu.empty()) {
                const auto [i, j] = qu.front();
                qu.pop();
                if (i == bi and j == bj) {
                        cout << "YES\n";
                        cout << distance[i][j] << '\n';
                        
                        string path = "";
                        int cur_i = i, cur_j = j;
                        while (cur_i != ai or cur_j != aj) {
                                int dir = direction[cur_i][cur_j];
                                path += directions[dir];
                                cur_i -= di[dir];
                                cur_j -= dj[dir];
                        }
                        reverse(path.begin(), path.end());
                        cout << path << '\n';
                        return;
                }
                for (int k = 0; k < 4; k++) {
                        int ni = i + di[k], nj = j + dj[k];
                        if (!visited[ni][nj]) {
                                distance[ni][nj] = distance[i][j] + 1;
                                visited[ni][nj] = 1;
                                direction[ni][nj] = k;
                                qu.push({ni, nj});
                        }
                }
        }
        cout << "NO\n";
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solve();
        return 0;
}