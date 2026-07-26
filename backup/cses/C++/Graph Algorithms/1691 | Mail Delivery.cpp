#include <functional>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N, M;
    cin >> N >> M;

    vector<vector<pair<int, int>>> adj(N+1);
    vector<bool> edge_visited(M, 0);

    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].emplace_back(b, i);
        adj[b].emplace_back(a, i);
    }

    for (int i = 1; i <= N; i++) {
        if (adj[i].size() % 2 != 0) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    vector<int> it(N+1, 0);
    vector<int> path;

    const auto dfs = [&](auto &&self, int cur) -> void {
        while (it[cur] < adj[cur].size()) {
            if (!edge_visited[adj[cur][it[cur]].second]) {
                edge_visited[adj[cur][it[cur]].second] = 1;
                self(self, adj[cur][it[cur]].first);
            }
            it[cur]++;
        }

        path.emplace_back(cur);
    };

    dfs(dfs, 1);

    if (path.size()-1 != M) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (auto v : path) cout << v << ' ';
    cout << '\n';
    
    return 0;
}