#include <algorithm>
#include <functional>
#include <iostream>
#include <utility>
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

void solution() {
        int N, Q; cin >> N >> Q;
        vector<lli> BIT(N+1, 0);
        const function qry = [&](int i) -> lli {
                if (i <= 0) return 0;
                lli res = 0;
                for (int j = i; j >= 1; j -= (j & -j)) {
                        res += BIT[j];
                }
                return res;
        };
        const function upd = [&](int k, int u) -> void {
                for (int j = k; j <= N; j += (j & -j)) {
                        BIT[j] += u;
                }
        };
        const function range_sum = [&](int a, int b) -> lli {
                return qry(b) - qry(a-1);
        };
        for (int i = 1; i <= N; i++) {
                int x; cin >> x;
                upd(i, +x);
        }
        while (Q-->0) {
                int op; cin >> op;
                if (op == 1) {
                        int k, u; cin >> k >> u;
                        upd(k, u - range_sum(k, k));
                } else {
                        int a, b; cin >> a >> b;
                        cout << range_sum(a, b) << '\n';
                }
        }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
