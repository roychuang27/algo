#include <algorithm>
#include <atcoder/fenwicktree>
#include <cmath>
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
#define CORDCOMP(x, fx) sort(ALL(x)); x.erase(unique(ALL(x)), end(x)); const auto fx = [&](int val) -> int { return lower_bound(ALL(x), val) - begin(x); }

using namespace std;
using lli = long long int;

void solution() {
        int N, Q; cin >> N >> Q;
        vector<int> X(N), V(N);
        vector<int> tx, tv;
        for (int i = 0; i < N; i++) {
                cin >> X[i] >> V[i];
                tx.eb(X[i]);
                tv.eb(V[i]);
        }
        CORDCOMP(tx, fx); CORDCOMP(tv, fv);
        int CX = SZ(tx);
        int CV = SZ(tv);
        vector<int> val(CX);
        for (int i = 0; i < N; i++) val[fx(X[i])] = fv(V[i]);
        atcoder::fenwick_tree<int> fenwick(CV);
        vector<tuple<int, int, int>> qs;
        vector<lli> ans(Q);
        for (int i = 0; i < Q; i++) {
                int l, r;
                cin >> l >> r;
                l = fx(l);
                r = fx(r+1)-1;
                if (l > r) {
                        ans[i] = 0;
                        continue;
                }
                qs.eb(l, r, i);
        }
        int B = sqrt(SZ(tx));
        sort(ALL(qs), [&](auto t1, auto t2) {
                if (get<0>(t1)/B == get<0>(t2)/B) return ((get<0>(t1)/B) & 1) ? get<1>(t1) > get<1>(t2) : get<1>(t1) < get<1>(t2);
                return get<0>(t1) < get<0>(t2);
        });
        lli sum = 0;
        const auto add = [&](int x) -> void {
                if (x == -1) return;
                test(val[x]);
                fenwick.add(val[x], +1);
                sum += fenwick.sum(0, val[x]) + fenwick.sum(val[x]+1, CV) + 1;
        };
        const auto del = [&](int x) -> void {
                if (x == -1) return;
                test(val[x]);
                fenwick.add(val[x], -1);
                sum -= fenwick.sum(0, val[x]) + fenwick.sum(val[x]+1, CV) + 1;
        };
        int L = 0, R = -1;
        for (const auto &[l, r, i] : qs) {
                test(l, r);
                while (l < L) add(--L);
                while (r > R) add(++R);
                while (R > r) del(R--);
                while (L < l) del(L++);
                ans[i] = sum;
        }
        for (const lli &a : ans) cout << a << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
