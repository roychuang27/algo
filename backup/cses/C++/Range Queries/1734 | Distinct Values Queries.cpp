/*
 * Submission ID: 16736333
 * Problem: Distinct Values Queries
 * Link: https://cses.fi/problemset/task/1734
 */

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
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

struct Qry {
        int l, r, i;
};

void solution() {
        int N, Q; cin >> N >> Q;
        vector<int> A(N);
        for (int &x : A) cin >> x;
        vector<int> v = A;
        sort(ALL(v));
        v.erase(unique(ALL(v)), v.end());
        const function f = [&](int x) {
                return lower_bound(ALL(v), x) - v.begin();
        };
        for (int &x : A) x = f(x);
        vector<Qry> qs(Q);
        for (int i = 0; i < Q; i++) {
                cin >> qs[i].l >> qs[i].r;
                qs[i].l--; qs[i].r--;
                qs[i].i = i;
        }
        int K = sqrt(N);
        sort(ALL(qs), [&](Qry &x, Qry &y) {
                if(x.l / K != y.l / K) return x.l / K < y.l / K;
                return ((x.l / K) % 2 == 0)? x.r < y.r : x.r > y.r;
        });
        vector<int> ans(Q);
        vector<int> freq(N, 0);
        int L = 0, R = -1;
        int c = 0;

        const function add = [&](int x) {
                if (freq[x] == 0) {
                        c++;
                }
                freq[x]++;
        };

        const function del = [&](int x) {
                freq[x]--;
                if (freq[x] == 0) c--;
        };

        for (const auto &[l, r, i] : qs) {
                while (R < r) add(A[++R]);
                while (L > l) add(A[--L]);
                while (R > r) del(A[R--]);
                while (L < l) del(A[L++]);
                ans[i] = c;
        }

        for (const int &a : ans) cout << a << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
