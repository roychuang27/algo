#include <algorithm>
#include <array>
#include <iostream>
#include <map>
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

class Fenwick {
        public:
        const int capacity = 2e5;
        vector<lli> b;
        
        Fenwick() {
                b = vector<lli> (capacity + 10, 0);
        }
        
        int lowbit(int x) {
                return x & -x;
        }
        
        void modify(int idx, int delta) {
                for (int pos = idx; pos <= capacity; pos += lowbit(pos)) {
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
};

void solution() {
        int N, Q;
        cin >> N >> Q;
        vector<int> xs(N + 1);
        for (int i = 1; i <= N; i++) {
                cin >> xs[i];
        }
        vector<array<int, 3>> qs(Q);
        vector<int> ans(Q);
        for (int i = 0; i < Q; i++) {
                int l, r;
                cin >> l >> r;
                qs[i] = {l, r, i};
        }
        sort(qs.begin(), qs.end(), [&](auto q1, auto q2) {
                return q1[1] < q2[1];
        });
        map<int, int> mp;
        Fenwick fenwick;
        int R = 0;
        for (const auto &[l, r, i] : qs) {
                while (R < r) {
                        R++;
                        if (mp[xs[R]]) {
                                fenwick.modify(mp[xs[R]], -1);
                        }
                        fenwick.modify(R, +1);
                        mp[xs[R]] = R;
                }
                ans[i] = fenwick.query(r) - fenwick.query(l-1);
        }
        for (const auto &x : ans) cout << x << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}