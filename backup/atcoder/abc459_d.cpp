#include <bits/stdc++.h>
using namespace std;
 
void solve() {
        string s; cin >> s;
        int N = s.size();
        vector<int> freq(30, 0);
        for (auto c : s) {
        	freq[c - 'a']++;
        }
        int max_cnt = 0;
        for (int i = 0; i < 26; i++) max_cnt = max(freq[i], max_cnt);
        if (max_cnt > (N + 1) / 2) {
        	cout << "No\n";
        	return;
        }
        string ans = "";
        int last = 114514;
        cout << "Yes\n";
        for (int i = 0; i < N; i++) {
        	int add = 114514;
        	for (int c = 0; c < 26; c++) {
        		if (freq[c] > 0 and c != last) {
        			if (freq[c] > (N - i) / 2) {
        				add = c;
        				break;
        			} else {
        				add = min(c, add);
        			}
        		}
        	}
        	cout << char(add + 'a');
        	last = add;
        	freq[add]--;
        }
        cout << '\n';
}

int main() {
        cin.tie(0)->sync_with_stdio(0);
        int T;
        cin >> T;
        while (T--) solve();
}
              if (freq[i] > (N + 1) / 2) {
                        cout << "No\n";
                        return;
                }
        }
        cout << "Yes\n";
        int last = 67;
        for (int i = 0; i < N; i++) {
                int max_cnt = 0;
                int cur;
                for (int j = 0; j < 26; j++) if (j != last) {
                        if (freq[j] > max_cnt) {
                                cur = j;
                                max_cnt = freq[j];
                        }
                }
                freq[cur]--;
                cout << (char) (cur + 'a');
                last = cur;
        }
        cout << '\n';
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        int T;
        cin >> T;
        while (T--)
                solution();
        return 0;
}
