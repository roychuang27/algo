#include <algorithm>
#include <functional>
#include <iostream>
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

class DSU {
        public:
        int N;
        vector<int> root;

        DSU(int n): N(n), root(n+1) {
                for (int i = 1; i <= N; i++) {
                        root[i] = i;
                }
        }

        bool same_component(int a, int b) {
                return find_root(a) == find_root(b);
        }

        int find_root(int x) {
                if (root[x] == x)
                        return x;
                root[x] = find_root(root[x]);
                return root[x];
        }

        void unite(int a, int b) {
                a = find_root(a);
                b = find_root(b);
                root[b] = a;
        }
};

struct edge {
        int u, v, w;
};

void solution() {
        int N, M;
        cin >> N >> M;
        vector<edge> edge_list;
        for (int i = 0; i < M; i++) {
                int u, v, w;
                cin >> u >> v >> w;
                edge_list.emplace_back(edge{u, v, w});
        }
        vector<vector<pair<int, int>>> adj(N+1);
        sort(edge_list.begin(), edge_list.end(), [&](auto e1, auto e2) {
                return e1.w < e2.w;
        });
        DSU dsu(N);
        int components = N;
        for (const auto e : edge_list) {
                if (components <= 1) break;
                if (!dsu.same_component(e.u, e.v)) {
                        dsu.unite(e.u, e.v);
                        components--;
                        adj[e.u].emplace_back(e.v, e.w);
                        adj[e.v].emplace_back(e.u, e.w);
                }
        }

        vector<int> tin(N+1), tout(N+1);
        vector<int> depth(N+1);
        vector<vector<int>> jump(32, vector<int> (N+1));
        vector<vector<int>> ansUp(32, vector<int> (N+1, -INF));
        depth[0] = 0;
        int timer = 0;
        
        function<void(int, int)>
        dfs_find_order = [&](int cur, int parent) -> void {
                // test(parent);
                // test(cur);
                depth[cur] = depth[parent] + 1;
                tin[cur] = timer++;
                
                for (const auto &[nxt, w] : adj[cur]) {
                        if (nxt == parent) {
                                jump[0][cur] = parent;
                                ansUp[0][cur] = w;
                        } else  {
                                dfs_find_order(nxt, cur);
                        }
                }
                
                tout[cur] = timer++;
        };
        
        dfs_find_order(1, 0);
        jump[0][1] = 1;
        for (int k = 1; k <= 31; k++) {
                for (int i = 1; i <= N; i++) {
                        jump[k][i] = jump[k - 1][ jump[k - 1][i] ];
                        ansUp[k][i] = max(ansUp[k-1][i], ansUp[k-1][jump[k-1][i]]);
                }
        }
        
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

        function<int(int, int)>
        ideograph_advantage = [&](int a, int b) -> int {
                int ans = -INF;
                if (a_is_anc_of_b(a, b)) {
                        for (int j = 31; j >= 0; j--) {
                                if (a_is_anc_of_b(a, jump[j][b])) {
                                        ans = max(ans, ansUp[j][b]);
                                        b = jump[j][b];
                                }
                        }
                        return ans;
                }
                if (a_is_anc_of_b(b, a)) {
                        for (int j = 31; j >= 0; j--) {
                                if (a_is_anc_of_b(b, jump[j][a])) {
                                        ans = max(ans, ansUp[j][a]);
                                        a = jump[j][a];
                                }
                        }
                        return ans;
                }

                int c = lca(a, b);
                for (int j = 31; j >= 0; j--) {
                        if (!a_is_anc_of_b(jump[j][a], c)) {
                                ans = max(ans, ansUp[j][a]);
                                a = jump[j][a];
                        }
                        if (!a_is_anc_of_b(jump[j][b], c)) {
                                ans = max(ans, ansUp[j][b]);
                                b = jump[j][b];
                        }
                }

                ans = max({ans, ansUp[0][a], ansUp[0][b]});
                return ans;
        };

        int Q; cin >> Q;
        while (Q--) {
                int a, b; cin >> a >> b;
                cout << ideograph_advantage(a, b) << '\n';
        }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}