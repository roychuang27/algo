#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
#define test(x) cerr << "Line(" << __LINE__ << ") " #x << ' ' << x << endl
#define printv(x)                          \
{                                          \
        for (auto i : x) cout << i << ' '; \
        cout << endl;                      \
}
#define SQ(x) ((x) * (x))
#define SZ(x) ((int)x.size())
#define eb emplace_back
#define ALL(x) x.begin(), x.end()
#define rALL(x) x.begin(), x.end()

using namespace std;
using lli = long long int;

void solution() {
        int N, M; cin >> N >> M;
        vector<vector<int>> adj(N);
        vector<int> T(N), in_deg(N);
        vector<int> blackout;
        for (int i = 0; i < N; i++) cin >> T[i];
        vector<bool> visited(N);
        queue<int> qu;
        for (int i = 0; i < M; i++) {
                int u, v; cin >> u >> v;
                u--; v--;
                adj[u].eb(v);
                in_deg[v]++;
                if (in_deg[v] > T[v] and !visited[v]) {
                        qu.push(v);
                        visited[v] = 1;
                }
        }
        while (!qu.empty()) {
                int cur = qu.front(); qu.pop();
                blackout.eb(cur);
                for (const int &nxt : adj[cur]) {
                        in_deg[nxt]++;
                        if (in_deg[nxt] > T[nxt] and !visited[nxt]) {
                                qu.push(nxt);
                                visited[nxt]= 1;
                        }
                }
        }
        if (SZ(blackout) == 0) {
                cout << -1 << '\n';
        } else {
                sort(ALL(blackout));
                for (auto &v : blackout) cout << v+1 << ' ';
                cout << '\n';
        }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
