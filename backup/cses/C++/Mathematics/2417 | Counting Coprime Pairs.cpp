/*
 * Submission ID: 15077186
 * Problem: Counting Coprime Pairs
 * Link: https://cses.fi/problemset/task/2417
 */

#include <iostream>
#include <vector>
#define fastio cin.tie(0)->sync_with_stdio(false)
#define eb emplace_back
#define test(x) cerr << "Line(" << __LINE__ << ") " #x << ' ' << x << endl
#define printv(x)                                  \
        {                                          \
                for (auto i : x) cout << i << ' '; \
                cout << endl;                      \
        }
#define pii pair<int, int>
#define pll pair<lli, lli>
#define ALL(x) x.begin(), x.end()
#define rALL(x) x.rbegin(), x.rend()
#define MP(x, y) make_pair((x), (y))
#define SQ(x) ((x) * (x))
#define SZ(x) ((int)x.size())

using namespace std;
typedef long long int lli;

template <typename A, typename B>
ostream& operator<<(ostream& o, pair<A, B> a) {
        return o << a.first << ' ' << a.second;
}
template <typename A, typename B>
istream& operator>>(istream& o, pair<A, B>& a) {
        return o >> a.first >> a.second;
}

constexpr int max_A = 1e6;

void solve() {
       int N; cin >> N;
        vector<lli> dp(max_A + 1, 0);
        vector<int> cnt(max_A + 1, 0);

        for (int i = 0; i < N; i++) {
                int x; cin >> x;
                cnt[x]++;
        }

        for (int k = max_A; k >= 1; k--) {
                lli mul_dp = 0, mul_cnt = 0;

                for (int mul = k; mul <= max_A; mul += k) {
                        mul_dp += dp[mul];
                        mul_cnt += cnt[mul];
                }

                dp[k] = ((mul_cnt) * (mul_cnt - 1) / 2) - mul_dp;
        }

        cout << dp[1] << '\n';
}

int main() {
        fastio;
        solve();
        return 0;
}