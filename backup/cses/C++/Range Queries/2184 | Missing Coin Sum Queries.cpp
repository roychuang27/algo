#include <bits/stdc++.h>
#include <cassert>

using namespace std;
using lli = long long int;

constexpr int B = 30;

template <class T> bool chmin(T &a, T b) {
        if (b < a) {
                a = b;
                return 1;
        } else {
                return 0;
        }
}
template <class T> bool chmax(T &a, T b) {
        if (a < b) {
                a = b;
                return 1;
        } else {
                return 0;
        }
}
namespace std {
template <class T, std::size_t n> auto array_fill(T value) {
        std::array<T, n> res;
        res.fill(value);
        return res;
}
}

struct Zkw {
        using S = array<lli, B>;
        int N;
        vector<S> t;
        S op(S a, S b) {
                for (int i = 0; i < B; i++) {
                        chmin(a[i], b[i]);
                }
                return a;
        }
        S e() {
                return array_fill<lli, B>(2e9);
        }
        S prod(int l, int r) {
                S res = e();
                for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
                        if (l & 1) res = op(t[l++], res);
                        if (r & 1) res = op(res, t[--r]);
                }
                return res;
        }
        void build() {
                for (int i = N-1; i > 0; i--) {
                        t[i] = op(t[i<<1], t[i<<1|1]);
                }
        }
        Zkw(int n) : N(n), t(2*N, e()) {}
};

void precompute() {
}

void solve() {
        int N, Q;
        cin >> N >> Q;
        Zkw zkw(N);
        vector<array<lli, B>> pre(N+1, array_fill<lli, B>(0));
        for (int i = 0; i < N; i++) {
                int x;
                cin >> x;
                int lg = log2(x);
                zkw.t[i+N][lg] = x;
                pre[i+1][lg] = x;
        }
        zkw.build();
        for (int i = 1; i <= N; i++) for (int j = 0; j < B; j++) pre[i][j] += pre[i-1][j];
        for (int _ = 0; _ < Q; _++) {
                int l, r;
                cin >> l >> r;
                l--;
                auto mn = zkw.prod(l, r);
                lli sum = 0, ans = -1;
                for (int i = 0; i < B; i++) {
                        if (sum + 1 < (1 << (i + 1)) and mn[i] > sum + 1) {
                                ans = sum + 1;
                                break;
                        }
                        sum += pre[r][i] - pre[l][i];
                }
                if (ans == -1) {
                        cout << sum + 1 << '\n';
                } else {
                        cout << ans << '\n';
                }
        }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        precompute();
        solve();
        return 0;
}
