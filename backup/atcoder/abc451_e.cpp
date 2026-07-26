#include <algorithm>
#include <functional>
#include <iostream>
#include <utility>
#include <tuple>
#include <vector>
#ifndef ONLINE_JUDGE
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

constexpr int INF = 0x3f3f3f3f;

class DSU {
        public:
        int N;
        vector<int> root;
 
        DSU(int n): N(n) {
                root.resize(N);
                for (int i = 0; i < N; i++) root[i] = i;
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

void solution() {
        int N; cin >> N;
        vector<vector<int>> A(N, vector<int> (N));
        A[0][0] = 0;
        vector<tuple<int, int, int>> edge_list;
        for (int i = 0; i < N-1; i++) {
                for (int j = i+1; j < N; j++) {
                        cin >> A[i][j];
                        A[j][i] = A[i][j];
                        edge_list.eb(A[i][j], i, j);
                }
        }
        sort(ALL(edge_list));
        vector<vector<int>> adj(N);
        DSU dsu(N);
        for (const auto &[w, u, v] : edge_list) {
                if (dsu.same_component(u, v)) continue;
                adj[u].eb(v);
                adj[v].eb(u);
                dsu.unite(u, v);
        }
        bool yes = 1;
        for (int i = 0; i < N; i++) {
                const function<void(int, int, int)> dfs = [&](int cur, int parent, int d) -> void {
                        if (!yes) return;
                        for (const auto &nxt : adj[cur]) if (nxt != parent) {
                                if (d + A[cur][nxt] != A[i][nxt]) {
                                        yes = 0;
                                        return;
                                }
                                dfs(nxt, cur, d + A[cur][nxt]);
                        }
                };
                dfs(i, i, 0);
                if (!yes) break;
        }
        if (yes) {
                cout << "Yes\n";
        } else {
                cout << "No\n";
        }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
        for (int i = 1; i <= N; i++) {
                        jump[k][i] = jump[k - 1][ jump[k - 1][i] ];
                }
        }
        
        const function<bool(int, int)> a_is_anc_of_b = [&](int a, int b) -> bool {
                return tin[a] <= tin[b] and tout[a] >= tout[b];
        };
        
        const function<int(int, int)> lca = [&](int a, int b) -> int {
                if (a_is_anc_of_b(a, b)) return a;
                if (a_is_anc_of_b(b, a)) return b;
 
                for (int j = 31; j >= 0; j--) {
                        if (!a_is_anc_of_b(jump[j][a], b)) {
                                a = jump[j][a];
                        }
                }
                
                return jump[0][a];
        };
        
        const function<int(int, int)> dist = [&](int a, int b) -> int{
                return depth[a] + depth[b] - 2*depth[lca(a, b)];
        };

        vector<int> p;
        const function<void(int, int)> dfs = [&](int cur, int parent) -> void {
                if (!yes) return;
                p.eb(cur);
                for (const auto &nxt : adj[cur]) if (nxt != parent) {
                        for (const int &j : p) {
                                if (dist(j, nxt) != A[j][nxt]) {
                                        yes = 0;
                                        return;
                                }
                        }
                        dfs(nxt, cur);
                }
        };
        dfs(1, 1);
        if (yes) {
                cout << "Yes\n";
        } else {
                cout << "No\n";
        }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
