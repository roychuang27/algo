#include <iostream>
#include <vector>

using namespace std;

bool flag = 1;
vector<vector<int>> adj(1e5 + 5);
vector<int> color(1e5 + 5, 0);

void dfs(int cur, int prev) {
        color[cur] = (color[prev] == 1 ? 2 : 1);
        for (auto nxt : adj[cur]) {
                if (color[nxt] != 0) {
                        if (color[nxt] != color[cur]) {
                                continue;
                        } else {
                                flag = 0;
                                return;
                        }
                } else {
                        dfs(nxt, cur);
                }
        }
}

int main() {
        int N, M;
        cin >> N >> M;
        for (int i = 0; i < M; i++) {
                int a, b;
                cin >> a >> b;
                adj[a].push_back(b);
                adj[b].push_back(a);
        }
        color[0] = 3;
        for (int i = 1; i <= N; i++) {
                if (color[i] == 0) {
                        dfs(i, 0);
                }
        }
        if (flag) {
                for (int i = 1; i <= N; i++) cout << color[i] << " \n"[i == N];
        } else {
                cout << "IMPOSSIBLE\n";
        }
        return 0;
}