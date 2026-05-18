#pragma GCC optimize("Ofast")
#include <algorithm>
#include <iostream>
#include <vector>
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
const int inf = 1e9 + 10;

struct ZKW {
    int tree[400005];
    int N = 0;

    void init(int n) {
        N = n;
    }
    
    void build(vector<int> &arr) {
        for (int i = 0; i < N; i++) {
            tree[N + i] = arr[i];
        }
        for (int i = N - 1; i > 0; i--) {
            tree[i] = min(tree[2 * i], tree[2 * i + 1]);
        }
    }
    
    void modify(int idx, int val) {
        idx += N;
        tree[idx] = val;
        idx /= 2;
        while (idx >= 1) {
            tree[idx] = min(tree[2 * idx], tree[2 * idx + 1]);
            idx /= 2;
        }
    }
    
    lli query(int l, int r) {
        l += N;
        r += N;
        int res = inf;
        while (l <= r) {
            if (l % 2 == 1) {
                res = min(tree[l], res);
                l++;
            }
            if (r % 2 == 0) {
                res = min(tree[r], res);
                r--;
            }
            l /= 2;
            r /= 2;
        }
        return res;
    }
} up, down;
// up: p[j] + j - i
// down: p[j] - j + i

void solve() {
    int N, Q;
    cin >> N >> Q;
    vector<int> ps(N);
    for (int i = 0; i < N; i++) {
        cin >> ps[i];
    }
    vector<int> arr_up(N), arr_down(N);
    for (int i = 0; i < N; i++) arr_up[i] = ps[i] + i;
    for (int i = 0; i < N; i++) arr_down[i] = ps[i] - i;
    up.init(N);
    down.init(N);
    up.build(arr_up);
    down.build(arr_down);

    for (int i = 0; i < Q; i++) {
        int op; cin >> op;
        if (op == 1) {
            int k, x;
            cin >> k >> x;
            up.modify(k-1, x+k-1);
            down.modify(k-1, x-k+1);
        } else {
            int k; cin >> k;
            int ql = down.query(0, k-1) + k - 1;
            int qr = up.query(k, N-1) - k + 1;
            cout << min(ql, qr) << '\n';
        }
    }
}

int main() {
    fastio;
    solve();
    return 0;
}