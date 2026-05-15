/*
 * Submission ID: 14470493
 * Problem: String Reorder
 * Link: https://cses.fi/problemset/task/1743
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
//	int N; cin >> N;
	string s; cin >> s;
	int N = s.length();
	vector<int> freq(30, 0);
	for (auto c : s) {
		freq[c - 'A']++;
	}
	int max_cnt = 0;
	for (int i = 0; i < 26; i++) max_cnt = max(freq[i], max_cnt);
	if (max_cnt > (N + 1) / 2) {
		cout << "-1" << endl;
		return 0;
	}
	string ans = "";
	int last = 114514;
//	cout << N << endl;
	for (int i = 0; i < N; i++) {
		int add = 114514;
		for (int c = 0; c < 26; c++) {
//			cout << c << ' ' << last << endl;
			if (freq[c] > 0 and c != last) {
				if (freq[c] > (N - i) / 2) {
					add = c;
					break;
				} else {
					add = min(c, add);
				}
			}
		}
//		ans += (add + 'A');
		cout << char(add + 'A');
		last = add;
		freq[add]--;
//		cout << i << endl;
	}
//	cout << ans << '\n';
	return 0;
}
