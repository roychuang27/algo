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
        vector<int> toposort;
        toposort.reserve(N);
        vector<vector<int>> adj(N+1);
        vector<int> in_deg(N+1, 0);
        for (int i = 0; i < M; i++) {
                int a, b; cin >> a >> b;
                adj[a].eb(b);
                in_deg[b]++;
        }
        priority_queue<int, vector<int>, std::greater<int>> min_heap;
        for (int i = 1; i <= N; i++) {
                if (in_deg[i] == 0)
                        min_heap.push(i);
        }
        while (not min_heap.empty()) {
                int u = min_heap.top(); min_heap.pop();
                toposort.eb(u);
                for (const int &v : adj[u]) {
                        in_deg[v]--;
                        if (in_deg[v] == 0)
                                min_heap.push(v);
                }
        }
        for (const int &v : toposort) cout << v << ' ';
        cout << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
