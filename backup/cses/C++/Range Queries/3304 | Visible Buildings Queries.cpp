#include <iostream>
#include <functional>
#include <stack>
#include <vector>
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

constexpr int INF = 0x3f3f3f3f;

void solution() {
        int N, Q;
        cin >> N >> Q;
        vector<int> hs(N+2, INF);
        for (int i = 1; i <= N; i++) {
                cin >> hs[i];
        }
        vector<vector<int>> adj(N+2);
        vector<vector<int>> jump(32, vector<int> (N+2, N+1));
        
        stack<int> stk;
        stk.push(N+1);
        for (int i = N; i >= 1; i--) {
                while (hs[stk.top()] <= hs[i])
                        stk.pop();
                int t = stk.top();
                adj[t].emplace_back(i);
                adj[i].emplace_back(t);
                jump[0][i] = t;
                stk.push(i);
        }

        for (int k = 1; k <= 31; k++) {
                for (int i = 1; i <= N; i++) {
                        jump[k][i] = jump[k - 1][ jump[k - 1][i] ];
                }
        }
        
        // vector<int> tin(N+1), tout(N+1);
        // int timer = 0;
        // function<void(int, int)>
        // dfs_build = [&](int cur, int parent) -> void {
        //         tin[cur] = timer++;

        //         for (const int &nxt : adj[cur]) if (nxt != parent)
        //                 dfs_build(nxt, cur);
                
        //         tout[cur] = timer++;
        // };
        // dfs_build(0, 0);

        // function<bool(int, int)>
        // a_is_anc_of_b = [&](int a, int b) -> bool {
        //         return tin[a] <= tin[b] and tout[a] >= tout[b];
        // };
        
        
        for (int i = 0; i < Q; i++) {
                int a, b;
                cin >> a >> b;
                
                int cnt = 0;
                for (int j = 31; j >= 0; j--) {
                        if (jump[j][a] <= b) {
                                cnt += (1 << j);
                                a = jump[j][a];
                        }
                }
                cout << cnt+1 << '\n';
        }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}