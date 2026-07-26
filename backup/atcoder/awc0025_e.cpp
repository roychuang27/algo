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
#define eb emplace_back
#define ALL(x) x.begin(), x.end()
#define rALL(x) x.begin(), x.end()

using namespace std;
using lli = long long int;

int lowbit(int x) {
        return x & -x;
}

void solution() {
        int N, Q; cin >> N >> Q;
        vector<int> BIT(N+1);
        const function qry = [&](int i)->int {
                int res = 0;
                for (int _i = i; _i >= 1; _i -= lowbit(_i)) {
                        res += BIT[_i];
                }
                return res;
        };
        const function upd = [&](int i, int delta)->void {
                for (int _i = i; _i <= N; _i += lowbit(_i)) {
                        BIT[_i] += delta;
                }
        };
        const function g = [&](int x)->int {
                int l = 1, r = N;
                while (l < r) {
                        int m = (l + r) / 2;
                        if (qry(m) >= x) r = m;
                        else             l = m + 1;
                }
                return l;
        };
        vector<int> D(N+1);
        for (int i = 1; i <= N; i++) cin >> D[i];
        for (int i = 1; i <= N; i++) upd(i, +1);
        int cnt = N;
        while (Q-->0) {
                int t; cin >> t;
                if (cnt >= t) {
                        int i = g(t);
                        D[i]--;
                        if (D[i] == 0) {
                                upd(i, -1);
                                cnt--;
                        }
                }
                cout << cnt << '\n';
        }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
