#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

using lli = long long int;

class Fenwick {
    public:
        int N;
        vector<lli> b;
        
        Fenwick(int _n) : N(_n), b(N + 1, 0) {}
        
        int lowbit(int x) {
                return x & -x;
        }
        
        void add(int idx, int delta) {
                for (int pos = idx; pos <= N; pos += lowbit(pos)) {
                        b[pos] += delta;
                }
        }

        lli query(int idx) {
                lli res = 0;
                for (int pos = idx; pos >= 1; pos -= lowbit(pos)) {
                        res += b[pos];
                }
                return res;
        }

        lli sum(int l, int r) {
                return query(r) - query(l-1);
        }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    cin >> N >> Q;

    vector<lli> V(N+1);
    for (int i = 1; i <= N; i++) cin >> V[i];

    vector<vector<int>> adj(N+1);

    for (int _ = 0; _ < N-1; _++) {
        int A, B;
        cin >> A >> B;
        adj[A].emplace_back(B);
        adj[B].emplace_back(A);
    }
    
    vector<int> time_in(N+1);
    vector<int> time_out(N+1);
    int timer = 1;

    const auto dfs = [&](auto &&self, int cur, int parent) -> void {
        time_in[cur] = timer++;

        for (auto &nxt : adj[cur]) if (nxt != parent) {
            self(self, nxt, cur);
        }

        time_out[cur] = timer++;
    };
    dfs(dfs, 1, 1);

    Fenwick fenwick(2*N+1);

    for (int i = 1; i <= N; i++) {
        fenwick.add(time_in[i], V[i]);
    }

    for (int _ = 0; _ < Q; _++) {
        int op;
        cin >> op;
        if (op == 1) {
            int s;
            lli x;
            cin >> s >> x;
            fenwick.add(time_in[s], x - fenwick.sum(time_in[s], time_in[s]));
        } else {
            int s;
            cin >> s;
            cout << fenwick.sum(time_in[s], time_out[s]) << '\n';
        }
    }
}