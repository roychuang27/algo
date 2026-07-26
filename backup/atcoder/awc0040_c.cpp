#include <algorithm>
#include <functional>
#include <iostream>
#include <utility>
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
        int N, K; cin >> N >> K;
        vector<int> X(N);
        vector<pair<int, int>> qs(N);
        vector<int> tmp;
        for (int i = 0; i < N; i++) {
                cin >> X[i];
                qs[i] = {X[i], X[i] + K};
                tmp.eb(X[i]);
                tmp.eb(X[i]+K);
        }
        sort(ALL(tmp));
        tmp.erase(unique(ALL(tmp)), tmp.end());
        const function f = [&](int x) -> int {
                return lower_bound(ALL(tmp), x) - tmp.begin() + 1;
        };
        for (int &x : X) x = f(x);
        for (auto &[l, r] : qs) l = f(l), r = f(r);
        int M = SZ(tmp);
        vector<int> BIT(M + 1, 0);
        const function qry = [&](int i) {
                int res = 0;
                for (int _i = i; _i > 0; _i -= _i & -_i)
                        res += BIT[_i];
                return res;
        };
        const function upd = [&](int i, int v) {
                for (int _i = i; _i <= M; _i += _i & -_i)
                        BIT[_i] += v;
        };
        for (const int &x : X) upd(x, +1);
        int ans = 0;
        for (const auto &[l, r] : qs) {
                ans = max(qry(r) - qry(l-1), ans);
        }
        cout << ans << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
