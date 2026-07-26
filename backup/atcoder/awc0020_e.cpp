#include <algorithm>
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

struct segtree {
        vector<int> t;
        int N;
        segtree(int _n, vector<int> &val) : t(4*_n+10, 0), N(_n) {
                build(1, 1, N, val);
        }
        
        void build(int id, int tl, int tr, vector<int> &val) {
                if (tl == tr) {
                        t[id] = val[tl];
                        return;
                }
                int tm = (tl + tr) / 2;
                build(2*id, tl, tm, val);
                build(2*id+1, tm+1, tr, val);
                t[id] = max(t[2*id], t[2*id+1]);
        }
        
        int range_max(int id, int tl, int tr, int l, int r) {
                if (l <= tl and tr <= r) return t[id];
                int tm = (tl + tr) / 2;
                if (r <= tm)
                        return range_max(2*id, tl, tm, l, r);
                else if (tm + 1 <= l)
                        return range_max(2*id+1, tm+1, tr, l, r);
                else
                        return max(range_max(2*id, tl, tm, l, r),
                                   range_max(2*id+1, tm+1, tr, l, r));
        }
        
        void update(int id, int tl, int tr, int new_val, int pos) {
                if (tl == tr) {
                        t[id] = new_val;
                        return;
                }
                int tm = (tl + tr) / 2;
                if (pos <= tm)
                        update(2*id, tl, tm, new_val, pos);
                else
                        update(2*id+1, tm+1, tr, new_val, pos);
                t[id] = max(t[2*id], t[2*id+1]);
        }
        
        int get_leftest_geq_idx(int id, int tl, int tr, int val) {
                if (t[id] < val) return -1;
                if (tl == tr)
                        return tl;
                int tm = (tl + tr) / 2;
                if (t[2*id] >= val)
                        return get_leftest_geq_idx(2*id, tl, tm, val);
                else
                        return get_leftest_geq_idx(2*id+1, tm+1, tr, val);
        }
};

void solution() {
        int N, M; cin >> N >> M;
        vector<int> ws(N);
        for (auto &w : ws) cin >> w;
        vector<int> cs(M+1);
        for (int i = 1; i <= M; i++) cin >> cs[i];
        segtree st(M, cs);
        int ans = 0;
        for (const auto &w : ws) {
                int idx = st.get_leftest_geq_idx(1, 1, M, w);
                if (idx != -1) {
                        ++ans;
                        st.update(1, 1, M, 0, idx);
                }
        }
        cout << ans << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
     return 0;
}
