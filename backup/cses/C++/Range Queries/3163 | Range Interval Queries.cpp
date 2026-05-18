#include <algorithm>
#include <array>
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
                if (idx == 0)
                        return 0;
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
        vector<pair<int, int>> xs(N + 1);
        for (int i = 1; i <= N; i++) {
                cin >> xs[i].first;
                xs[i].second = i;
        }

        // a <= i <= b, c <= x_i <= d

        vector<array<int, 5>> qs; // i, a, b, x, sign
        vector<int> ans(Q, 0);
        for (int i = 0; i < Q; i++) {
                int a, b, c, d;
                cin >> a >> b >> c >> d;
                qs.push_back({i, a, b, c-1, -1});
                qs.push_back({i, a, b, d, 1});
        }
        Fenwick fenwick;
        
        sort(qs.begin(), qs.end(),
                [&](auto q1, auto q2) {
                        return q1[3] < q2[3];
                }
        );
        
        sort(xs.begin()+1, xs.end(),
                [&](auto x1, auto x2) {
                        return x1.first < x2.first;
                }
        );
        
        int p = 1;
        for (auto &[i, l, r, x, sign] : qs) {
                while (p <= N and xs[p].first <= x) {
                        fenwick.modify(xs[p].second, +1);
                        p++;
                }
                ans[i] += sign * (fenwick.query(r) - fenwick.query(l-1));
        }
        
        for (auto &k : ans) cout << k << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}