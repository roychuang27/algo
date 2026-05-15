/*
 * Submission ID: 13205818
 * Problem: Sliding Window Minimum
 * Link: https://cses.fi/problemset/task/3221
 */

#pragma GCC optimize("Ofast")
#include <iostream>
#include <deque>
#include <vector>
#define fastio cin.tie(0)->sync_with_stdio(false)
#define eb emplace_back
#define pii pair<int, int>
#define pll pair<lli, lli>
#define ALL(x) x.begin(), x.end()
#define rALL(x) x.rbegin(), x.rend()
#define MP(x, y) make_pair((x), (y))
#define SQ(x) ((x)*(x))
#define SZ(x) ((int) x.size())

using namespace std;
typedef long long lli;

template <typename A, typename B>
ostream& operator << (ostream& o, pair<A, B> a) {
    return o << a.first << ' ' << a.second;
}
template <typename A, typename B>
istream& operator >> (istream& o, pair<A, B> &a) {
    return o >> a.first >> a.second;
}

void solve() {
    int N, K;
    cin >> N >> K;
    lli x, a, b, c;
    cin >> x >> a >> b >> c;
    vector<lli> arr(N);
    arr[0] = x;
    for (int i = 1; i < N; i++) arr[i] = (a * arr[i-1] + b) % c;
    // for (auto x : arr) cerr << x << ' ';
    // cerr << endl;
    deque<pii> dq;
    dq.eb(arr[0], 0);
    for (int i = 1; i < K; i++) {
        while (!dq.empty() && dq[0].first >= arr[i]) dq.pop_front();
        while (!dq.empty() && dq.end() [-1].first >= arr[i]) dq.pop_back();
        dq.eb(arr[i], i);
    }
    lli ans = 0;
    ans ^= dq[0].first;
    for (int i = K; i < N; i++) {
        if (dq[0].second <= i - K) dq.pop_front();
        while (!dq.empty() && dq[0].first >= arr[i]) dq.pop_front();
        while (!dq.empty() && dq.end()[-1].first >= arr[i]) dq.pop_back();
        dq.eb(arr[i], i);
        ans ^= dq[0].first;
    }
    cout << ans << '\n';
}

int main() {
    fastio;
    solve();
    return 0;
}