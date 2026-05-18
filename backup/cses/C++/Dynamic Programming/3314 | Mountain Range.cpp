#pragma GCC optimize("Ofast")
#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <stack>
#define fastio cin.tie(0)->sync_with_stdio(false)
#define eb emplace_back
#define test(x) cerr << "Line(" << __LINE__ << ") " #x << ' ' << x << endl
#define printv(x) { \
    for (auto i : x) cout << i << ' '; \
    cout << endl; \
}
#define pii pair<int, int>
#define pll pair<lli, lli>
#define ALL(x) x.begin(), x.end()
#define rALL(x) x.rbegin(), x.rend()
#define MP(x, y) make_pair((x), (y))
#define SQ(x) ((x)*(x))
#define SZ(x) ((int) x.size())
 
using namespace std;
typedef long long int lli;
 
template <typename A, typename B>
ostream& operator << (ostream& o, pair<A, B> a) {
    return o << a.first << ' ' << a.second;
}
template <typename A, typename B>
istream& operator >> (istream& o, pair<A, B> &a) {
    return o >> a.first >> a.second;
}
 
struct ZKW {
    lli t[400005];
    int N = 0;
 
    void printdbg() {
        int l = N, r = 2 * N - 1;
        while (l <= r) {
            for (int i = l; i <= r; i++) cerr << '(' << t[i] << ')' << ' ';
            cerr << endl;
            if (l % 2 == 1) l++;
            if (r % 2 == 0) r--;
            l /= 2;
            r /= 2;
        }
    }
 
    void init(int n) {
        N = n;
        for (int i = 0; i < 2 * N; i++) {
            t[i] = 0;
        }
    }
    
    void modify(int idx, int val) {
        idx += N;
        t[idx] = val;
        idx /= 2;
        while (idx >= 1) {
            t[idx] = max(t[2 * idx], t[2 * idx + 1]);
            idx /= 2;
        }
    }
 
    lli query(int l, int r) {
        l += N;
        r += N;
        if (l > r) return 0;
        lli res = 0;
        while (l <= r) {
            if (l % 2 == 1) {
                res = max(t[l], res);
                l++;
            }
            if (r % 2 == 0) {
                res = max(t[r], res);
                r--;
            }
            l /= 2;
            r /= 2;
        }
        return res;
    }
} zkw;
 
void solve() {
    int N; cin >> N;
    vector<int> hs(N);
    for (auto &x : hs) cin >> x;
    vector<pii> order(N);
    for (int i = 0; i < N; i++) order[i] = {hs[i], i};
    sort(ALL(order));
    vector<int> l_nearest_bigger(N), r_nearest_bigger(N);
    stack<int> stk;
    for (int i = 0; i < N; i++) {
        while (!stk.empty() && hs[stk.top()] < hs[i]) stk.pop();
        if (stk.empty()) {
            l_nearest_bigger[i] = -1;
        } else {
            l_nearest_bigger[i] = stk.top();
        }
        stk.push(i);
    }
    stack<int> stk2;
    for (int i = N - 1; i >= 0; i--) {
        while (!stk2.empty() && hs[stk2.top()] < hs[i]) stk2.pop();
        if (stk2.empty()) {
            r_nearest_bigger[i] = N;
        } else {
            r_nearest_bigger[i] = stk2.top();
        }
        stk2.push(i);
    }
    zkw.init(N);
    for (auto &[_, i] : order) {
        zkw.modify(i, 1 + max(zkw.query(l_nearest_bigger[i]+1, i-1), zkw.query(i+1, r_nearest_bigger[i]-1)));
    }
    cout << zkw.query(0, N-1) << '\n';
}
 
int main() {
    fastio;
    solve();
    return 0;
}
