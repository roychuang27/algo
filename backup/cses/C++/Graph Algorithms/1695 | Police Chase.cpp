/*
 * Submission ID: 15943789
 * Problem: Police Chase
 * Link: https://cses.fi/problemset/task/1695
 */

#include <bits/stdc++.h>
#define SZ(x) ((int) x.size())
#define uwu return 0
using namespace std;
using lli = long long int;

constexpr lli INF = 1e18;

struct flow_edge{
        lli cap, flow;
        int u, v, rev_id;
        
        flow_edge(int _u, int _v, lli _c, lli _f, int _r):
                cap(_c),
                flow(_f),
                u(_u),
                v(_v),
                rev_id(_r)
        {}
};

struct Dinic {
        int s, t;
        int N;
        vector<int> ptr;
        vector<flow_edge> edges;
        vector<int> dist;
        vector<vector<int>> adj_edges;
        int edges_cnt = 0;
        
        Dinic(int n, int _s, int _t):
                s(_s),
                t(_t),
                N(n),
                ptr(N + 10),
                dist(N + 10),
                adj_edges(N + 10)
        {}

        lli dfs_push(int u, lli flow) {
                if (flow == 0)
                        return 0;
                if (u == t)
                        return flow;
                
                while (ptr[u] < SZ(adj_edges[u])) {
                        int i = adj_edges[u][ptr[u]];
                        flow_edge &e = edges[i];
                        ptr[u]++;
                        
                        if (dist[e.v] != dist[e.u] + 1)
                                continue;
                                
                        if (e.flow >= e.cap)
                                continue;
                                
                        lli p = dfs_push(e.v, min(flow, e.cap - e.flow));
                        if (p > 0) {
                                e.flow += p;
                                edges[e.rev_id].flow -= p;
                                return p;
                        }
                }
                
                return 0;
        }
        
        bool bfs_get_dist() {
                fill(dist.begin(), dist.end(), -1);
                dist[s] = 0;
                queue<int> q;
                q.push(s);
                while (!q.empty()) {
                        int cur = q.front();
                        q.pop();
                        for (const auto &edge_id : adj_edges[cur]) {
                                flow_edge &e = edges[edge_id];
                                int nxt = e.v;
                                if (dist[nxt] != -1)
                                        continue;
                                if (e.flow == e.cap)
                                        continue;
                                
                                dist[nxt] = dist[cur] + 1;
                                q.push(nxt);
                        }
                }
                
                return dist[t] != -1;
        }
        
        void add_edge(int u, int v, lli cap, lli flow) {
                adj_edges[u].push_back(edges_cnt);
                edges.push_back(flow_edge(u, v, cap, flow, edges_cnt + 1));
                adj_edges[v].push_back(edges_cnt + 1);
                edges.push_back(flow_edge(v, u, 0, -flow, edges_cnt));
                edges_cnt += 2;
        }
        
        lli flow() {
                lli f = 0;
                
                while (true) {
                        if (bfs_get_dist() == false)
                                break;
                        
                        fill(ptr.begin(), ptr.end(), 0);
                        while (lli p = dfs_push(s, INF)) {
                                f += p;
                        }
                }
                
                return f;
        }
        
        void output_network(){
                cout << "Network\n";
                for(auto &i:edges){
                        cout << i.u << ' ' << i.v << ' ' << i.cap << ' ' << i.flow << '\n';
                }
                return;
        }
};

void solve() {
        int N, M; cin >> N >> M;
        Dinic dinic(N, 1, N);
        vector<vector<bool>> connected(N+1, vector<bool> (N+1, 0));
        for (int i = 0; i < M; i++) {
                int a, b;
                cin >> a >> b;
                dinic.add_edge(a, b, 1, 0);
                dinic.add_edge(b, a, 1, 0);
                connected[a][b] = connected[b][a] = 1;
        }
        
        cout << dinic.flow() << '\n';
        dinic.bfs_get_dist();

        vector<pair<int, int>> ans;
        
        for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= N; j++) {
                        if (connected[i][j] and dinic.dist[i] != -1 and dinic.dist[j] == -1) {
                                ans.emplace_back(i, j);
                        }
                }
        }
        
        for (auto &p : ans) {
                cout << p.first << ' ' << p.second << '\n';
        }
}

int main() {
        cin.tie(0)->sync_with_stdio(0);
        solve();
        return 0;
}
