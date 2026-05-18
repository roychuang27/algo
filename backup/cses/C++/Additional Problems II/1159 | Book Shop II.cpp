#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
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
    int N, X;
    cin >> N >> X;
    vector<lli> hs(N), ps(N), ks(N);
    for (int i = 0; i < N; i++) {
    	cin >> hs[i];
	}
	for (int i = 0; i < N; i++) {
    	cin >> ps[i];
	}
	for (int i = 0; i < N; i++) {
    	cin >> ks[i];
	}
	vector<lli> dp(X + 1, 0);
	for (int i = 0; i < N; i++) {
		int cnt = min(ks[i], X / hs[i]);
		for (int k = 1; cnt > 0; k <<= 1) {
			k = min(cnt, k);
			cnt -= k;
			lli cost = hs[i] * k;
			lli value = ps[i] * k;
			for (int j = X; j - cost >= 0; j--) {
				dp[j] = max(dp[j], dp[j - cost] + value);
			}
		}
//		printv(dp);
	}
	cout << dp[X] << '\n';
}

int main() {
    fastio;
    solve();
    return 0;
}
