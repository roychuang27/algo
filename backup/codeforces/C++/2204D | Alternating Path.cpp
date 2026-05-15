/*
 * Submission ID: 370494496
 * Problem: Alternating Path
 * Link: https://codeforces.com/contest/2204/problem/D
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <utility>
#include <queue>
#include <vector>
#ifdef LOCAL
#define test(...) do { cerr << "Line(" << __LINE__ << ") [" #__VA_ARGS__ "] =>"; ([](auto&&... args){ ((cerr << ' ' << args), ...); }(__VA_ARGS__)); cerr << endl; } while(0)
#define testv(x) do { cerr << "Line(" << __LINE__ << ") " #x " => ["; int _i=0; for (auto& _e : (x)) cerr << (_i++ ? ", " : "") << _e; cerr << "]" << endl; } while(0)
#else
#define test(...) 0
#define testv(...) 0
#endif
#define printv(x) { for (auto i : (x)) cout << i << ' '; cout << endl; }
#define SQ(x) ((x) * (x))
#define SZ(x) ((int)x.size())
#define eb emplace_back
#define ALL(x) begin(x), end(x)
#define rALL(x) rbegin(x), rend(x)
#define fst first
#define sec second
 
using namespace std;
using lli = long long int;
 
void solution() {
        int N, M; cin >> N >> M;
        vector<vector<int>> adj(N+1);
        for (int i = 0; i < M; i++) {
                int u, v; cin >> u >> v;
                adj[u].eb(v);
                adj[v].eb(u);
        }
        vector<int> color(N+1, -1);
        int ans = 0;
        const auto bfs = [&](int i) -> void {
                queue<int> qu;
                qu.push(i);
                color[i] = 0;
                bool bipartite = true;
                vector<int> cnt(2, 0);
                while (not qu.empty()) {
                        int cur = qu.front(); qu.pop();
                        cnt[color[cur]]++;
                        for (const auto &nxt : adj[cur]) {
                                if (color[nxt] == color[cur]) {
                                        bipartite = false;
                                } else if (color[nxt] == -1) {
                                        color[nxt] = color[cur] ^ 1;
                                        qu.push(nxt);
                                }
                        }
                }
                if (bipartite) ans += max(cnt[0], cnt[1]);
        };
        for (int i = 1; i <= N; i++) if (color[i] == -1) {
                bfs(i);
        }
        cout << ans << '\n';
}
 
int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        int T; cin >> T;
        while(T--)
                solution();
        return 0;
}