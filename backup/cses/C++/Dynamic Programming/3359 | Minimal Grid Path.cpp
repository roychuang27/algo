/*
 * Submission ID: 14241785
 * Problem: Minimal Grid Path
 * Link: https://cses.fi/problemset/task/3359
 */

#pragma GCC optimize("Ofast")
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <set>
#include <utility>
#include <cstdio>
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

const int dx[2] = {1, 0};
const int dy[2] = {0, 1};

vector<pair<char, pii>> radix_sort(vector<pair<char, pii>> &vec) {
    if (SZ(vec) <= 1) return vec;
    vector<pair<char, pii>> res;
    vector radix(26, vector<pair<char, pii>> ());
    for (auto &[c, pos] : vec) {
        radix[c - 'A'].eb(c, pos);
    }
    res.clear();
    for (int i = 0; i < 26; i++) {
        if (radix[i].empty()) continue;
        res.eb(radix[i][0]);
        for (int j = 1; j < SZ(radix[i]); j++) {
            if (radix[i][j] != radix[i][j-1]) res.eb(radix[i][j]);
        }
        break;
    }
    return res;
}

void solve() {
    int N; cin >> N;
    vector<string> grid(N);
    for (int i = 0; i < N; i++) {
        cin >> grid[i];
    }
    string ans;
    vector dp(2, vector<pair<char, pii>> ()); // bfs
    dp[0].eb(grid[0][0], pii(0, 0));
    ans += grid[0][0];
    for (int i = 1; i < 2 * N - 1; i++) {
        vector<pair<char, pii>> nxts;
        for (auto &[s, pos] : dp[(i - 1) % 2]) {
            for (int k = 0; k < 2; k++) {
                auto npos = pos;
                npos.first += dx[k];
                npos.second += dy[k];
                if (npos.first >= N or npos.second >= N) continue;
                // test(npos);
                nxts.eb(grid[npos.first][npos.second], npos);
            }
        }
        nxts = radix_sort(nxts);
        auto minItem = nxts[0];
        int j = 1;
        for (; j < SZ(nxts); j++) {
            if (nxts[j].first != minItem.first) break;
        }
        for (int k = SZ(nxts) - 1; k >= j; k--) {
            nxts.pop_back();
        }
        dp[i%2] = nxts;
        ans += nxts[0].first;
    }
    cout << ans << '\n';
}

int main() {
    fastio;
    solve();
    return 0;
}