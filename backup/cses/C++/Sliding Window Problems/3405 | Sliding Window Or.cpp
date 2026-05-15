/*
 * Submission ID: 14782271
 * Problem: Sliding Window Or
 * Link: https://cses.fi/problemset/task/3405
 */

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
    vector<lli> xs(N);
    int a, b, c;
    cin >> xs[0] >> a >> b >> c;

    for (int i = 1; i < N; i++) {
        xs[i] = (a * xs[i-1] + b) % c;
    }
    vector<int> prefix(N), suffix(N); // of a window

    for (int i = 0; i < N; i += K) {
        prefix[i] = xs[i];
        for (int j = i+1; j < i + K; j++) {
            prefix[j] = prefix[j-1] | xs[j];
        }
        int p = min(N-1, i+K-1);
        suffix[p] = xs[p];
        for (int j = p-1; j >= i; j--) {
            suffix[j] = suffix[j+1] | xs[j];
        }
    }

    int ans = 0;
    for (int i = K-1; i < N; i++) {
        ans ^= (prefix[i] | suffix[i-K+1]);
    }
    cout << ans;
}

int main() {
    fastio;
    solve();
    return 0;
}