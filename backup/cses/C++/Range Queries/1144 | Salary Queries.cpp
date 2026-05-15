/*
 * Submission ID: 16788479
 * Problem: Salary Queries
 * Link: https://cses.fi/problemset/task/1144
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <tuple>
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

class Fenwick {
    private:
        int N;
        vector<lli> b;
    public:
        Fenwick(int _N) : N(_N), b(N+1, 0) {}
        int lowbit(int x) {
                return x & -x;
        }
        void modify(int idx, int delta) {
                for (int pos = idx; pos <= N; pos += lowbit(pos)) {
                        b[pos] += delta;
                }
        }
        lli query(int idx) {
                if (idx == 0) return 0;
                lli res = 0;
                for (int pos = idx; pos >= 1; pos -= lowbit(pos)) {
                        res += b[pos];
                }
                return res;
        }
};

enum types { Modify, Query };

void solution() {
        int N, Q; cin >> N >> Q;
        vector<int> ps(N);
        vector<int> tmp;
        for (int &p : ps) {
                cin >> p;
                tmp.eb(p);
        }
        vector<tuple<types, int, int>> qs(Q);
        for (auto &[type, a, b] : qs) {
                char c; cin >> c;
                if (c == '!') {
                        type = Modify;
                        cin >> a >> b;
                        a--;
                        tmp.eb(b);
                } else {
                        type = Query;
                        cin >> a >> b;
                        tmp.eb(a); tmp.eb(b);
                }
        }
        sort(ALL(tmp));
        tmp.erase(unique(ALL(tmp)), tmp.end());
        const function f = [&](int x) -> int {
                return lower_bound(ALL(tmp), x) - tmp.begin() + 1;
        };
        Fenwick fenwick(SZ(tmp));
        for (int &p : ps) {
                p = f(p);
                fenwick.modify(p, +1);
        }
        for (auto &[type, a, b] : qs) {
                if (type == Modify) {
                        fenwick.modify(ps[a], -1);
                        b = f(b);
                        ps[a] = b;
                        fenwick.modify(b, +1);
                } else {
                        a = f(a);
                        b = f(b);
                        cout << fenwick.query(b) - fenwick.query(a - 1) << '\n';
                }
        }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
