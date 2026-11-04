#include <bits/stdc++.h>
using namespace std;

struct ZKW {
        int N;
        vector<pair<int, int>> t;
        ZKW(int n, vector<int>& v) : N(n), t(2 * N) {
                for (int i = 0; i < N; i++) t[i + N] = {v[i], v[i]};
        }
        pair<int, int> combine(pair<int, int> p1, pair<int, int> p2) {
                return {max(p1.first, p2.first), min(p1.second, p2.second)};
        }
        void build() {
                for (int i = N - 1; i > 0; --i)
                        t[i] = combine(t[i << 1], t[i << 1 | 1]);
        }

        pair<int, int> query(int l, int r) {
                pair<int, int> res = {-1, 1e9};
                for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
                        if (l & 1) res = combine(res, t[l++]);
                        if (r & 1) res = combine(res, t[--r]);
                }
                return res;
        }
};

constexpr int INF = 0x3f3f3f3f;

int main() {
        cin.tie(0)->sync_with_stdio(0);

        int N, K, D;
        cin >> N >> K >> D;
        vector<array<int, 3>> v(N);
        for (auto& [x, t, s] : v) cin >> x >> t >> s;

        sort(v.begin(), v.end());
        vector<int> s(N);
        for (int i = 0; i < N; i++) s[i] = v[i][2];
        ZKW zkw(N, s);
        zkw.build();

        int ans = INF;
        vector<int> cnt(K+1, 0);
        int types = 0;

        for (int l = 0, r = 0; r < N; r++) {
                if (cnt[v[r][1]] == 0) types++;
                cnt[v[r][1]]++;

                if (r == N-1 or v[r][0] != v[r+1][0]) {
                        while (types == K) {
                                if (l == 0 or v[l][0] != v[l-1][0]) {
                                        auto p = zkw.query(l, r+1);
                                        if (p.first - p.second <= D) {
                                                ans = min(ans, v[r][0] - v[l][0]);
                                        }
                                }
                                cnt[v[l][1]]--;
                                if (cnt[v[l][1]] == 0) types--;
                                l++;
                        }
                }
        }

        if (ans == INF)
                cout << -1 << '\n';
        else
                cout << ans << '\n';

        return 0;
}
