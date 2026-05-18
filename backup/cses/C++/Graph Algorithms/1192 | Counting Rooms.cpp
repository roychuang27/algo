#include <iostream>
#include <queue>

#define test(x) cerr << x << endl;

using namespace std;

bool can_go[1005][1005];
int N, M;

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

void bfs(int i, int j) {
        queue<pair<int, int>> qu;
        qu.push({i, j});
        can_go[i][j] = false;           // Mark visited / Cannot go to
        while (qu.empty() == false) {
                auto [cur_i, cur_j] = qu.front();
                qu.pop();
                
                for (int k = 0; k < 4; k++) {
                        int new_i = cur_i + dy[k], new_j = cur_j + dx[k] ;
                        if (new_i < 0 or new_i >= N or new_j < 0 or new_j >= M)
                                continue;
                        if (can_go[new_i][new_j] == false)
                                continue;

                        can_go[new_i][new_j] = false;
                        qu.push({new_i, new_j});
                }
        }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        cin >> N >> M;
        for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                        char c; cin >> c;
                        if (c == '.')
                                can_go[i][j] = true;
                }
        }        
        int cnt = 0;
        for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                        if (can_go[i][j]) {      // Empty Room
                                cnt++;           // Counter + 1
                                bfs(i, j);       // How far i can reach
                        }
                }
        }
        cout << cnt << '\n';
        return 0;
}