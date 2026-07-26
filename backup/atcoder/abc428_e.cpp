#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;

    vector<vector<int>> adj(N+1);

    for (int _ = 0; _ < N-1; _++) {
        int A, B;
        cin >> A >> B;
        adj[A].emplace_back(B);
        adj[B].emplace_back(A);
    }

    const auto calc_dist = [&](int source) -> vector<int> {
        vector<int> dist(N+1, -1);
        queue<pair<int, int>> qu;
        qu.emplace(source, 0);
        while (!qu.empty()) {
            auto [cur, d] = qu.front();
            qu.pop();
            dist[cur] = d;
            for (auto &nxt : adj[cur]) if (dist[nxt] == -1) {
                qu.emplace(nxt, d+1);
            }
        }
        return dist;
    };

    auto d1 = calc_dist(1);
    int u = N;
    for (int i = N-1; i > 0; i--) {
        if (d1[i] > d1[u]) u = i;
    }

    auto du = calc_dist(u);
    int v = N;
    for (int i = N-1; i > 0; i--) {
        if (du[i] > du[v]) v = i;
    }

    auto dv = calc_dist(v);

    for (int i = 1; i <= N; i++) {
        if (du[i] == dv[i]) cout << max(u, v) << '\n';
        else if (du[i] > dv[i]) cout << u << '\n';
        else cout << v << '\n';
    }
}