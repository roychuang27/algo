/*
 * Submission ID: 15977580
 * Problem: Company Queries II
 * Link: https://cses.fi/problemset/task/1688
 */

#include <iostream>
#include <functional>
#include <vector>
#define test(x) cerr << "Line(" << __LINE__ << ") " #x << ' ' << x << endl
#define printv(x)                                  \
        {                                          \
                for (auto i : x) cout << i << ' '; \
                cout << endl;                      \
        }
#define SQ(x) ((x) * (x))
#define SZ(x) ((int)x.size())

using namespace std;
using lli = long long int;

void solution() {
        int N, Q;
        cin >> N >> Q;
        vector<vector<int>> jump(32, vector<int>(N + 1, 1));
        vector<vector<int>> adj(N + 1);

        for (int i = 2; i <= N; i++) {
                int boss; cin >> boss;
                jump[0][i] = boss;
                adj[boss].emplace_back(i);
                adj[i].emplace_back(boss);
        }

        for (int k = 1; k <= 31; k++) {
                for (int i = 1; i <= N; i++) {
                        jump[k][i] = jump[k - 1][ jump[k - 1][i] ];
                }
        }
        
        vector<int> tin(N+1), tout(N+1);
        int timer = 0;
        
        function<void(int, int)>
        dfs_find_order = [&](int cur, int parent) -> void {
                tin[cur] = timer++;
                
                for (const int &nxt : adj[cur]) if (nxt != parent) {
                        dfs_find_order(nxt, cur);
                }
                
                tout[cur] = timer++;
        };
        
        dfs_find_order(1, 1);
        
        function<bool(int, int)>
        a_is_anc_of_b = [&](int a, int b) -> bool {
                return tin[a] <= tin[b] and tout[a] >= tout[b];
        };
        
        function<int(int, int)>
        lca = [&](int a, int b) -> int {
                if (a_is_anc_of_b(a, b)) return a;
                if (a_is_anc_of_b(b, a)) return b;

                for (int j = 31; j >= 0; j--) {
                        if (!a_is_anc_of_b(jump[j][a], b)) {
                                a = jump[j][a];
                        }
                }
                
                return jump[0][a];
        };
        
        while (Q--) {
                int a, b;
                cin >> a >> b;
                cout << lca(a, b) << '\n';
        }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
