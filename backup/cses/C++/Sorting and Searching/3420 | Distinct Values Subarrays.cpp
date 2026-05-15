/*
 * Submission ID: 14518019
 * Problem: Distinct Values Subarrays
 * Link: https://cses.fi/problemset/task/3420
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long lli;

int main() {
	map<int, int> mp;
	int N; cin >> N;
	lli ans = 0;
	int last_idx = 0;
	for (int i = 1; i <= N; i++) {
		int x; cin >> x;
		if (mp[x]) {
			last_idx = max(mp[x], last_idx);
		}
		ans += (i - last_idx);
//		cout << ans << ' '; 
		mp[x] = i;
	}
	cout << ans << '\n';
	return 0;
}
