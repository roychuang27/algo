/*
 * Submission ID: 14470044
 * Problem: Counting Tilings
 * Link: https://cses.fi/problemset/task/2181
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long lli;
constexpr int mod = 1e9 + 7;
int dp[1010][15][2050] = {0};
int m, n;

int q(int mask, int idx) {
//	cout << ((mask >> idx) & 1) << endl;
	return (mask >> idx) & 1;
}

void add_to(int &to, int &from) {
	to += from;
	if (to >= mod) to %= mod;
}

void push(int mask, int i, int j) {
	if (j >= n) {
		add_to(dp[i+1][0][mask], dp[i][j][mask]);
		return;
	}
	if ((n*i+j) % 2 != __builtin_popcount(mask) % 2) return;
	int down = q(mask, j);
	int down_right = q(mask, j + 1);
	if (down) {
		add_to(dp[i][j+1][mask^(1<<j)], dp[i][j][mask]);
	} else {
		add_to(dp[i][j+1][mask^(1<<j)], dp[i][j][mask]);
		if (!down_right and j < (n - 1)) {
			add_to(dp[i][j+2][mask], dp[i][j][mask]);
		}
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m;
	if (n > m) swap(n, m);
	dp[0][0][0] = 1;

	for (int i = 0; i < m; i++) {
		for (int j = 0; j <= n; j++) {
			for (int mask = 0; mask < (1 << n); mask++) {
				push(mask, i, j);
			}
//			cout << int(dp[i][j][0]) << ' ';
		}
//		cout << endl;
	}
	cout << dp[m][0][0] % mod << '\n';

	return 0;
}
