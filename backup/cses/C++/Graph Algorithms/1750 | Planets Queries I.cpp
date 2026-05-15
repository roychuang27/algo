/*
 * Submission ID: 14662531
 * Problem: Planets Queries I
 * Link: https://cses.fi/problemset/task/1750
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N, Q;
	cin >> N >> Q;
	vector<vector<int>> jump(32, vector<int> (N+1));
	for (int i = 1; i <= N; i++) {
		cin >> jump[0][i];
	}
	for (int k = 1; k <= 31; k++) {
		for (int i = 1; i <= N; i++) {
			jump[k][i] = jump[k-1][ jump[k-1][i] ];
		}
	}
	while (Q--) {
		int k, x;
		cin >> x >> k;
		int i = 0;
		while ((1 << i) <= k) {
			if (k & (1 << i)) {
				x = jump[i][x];
			}
			i++;
		}
		cout << x << '\n';
	}
	return 0;
}
