#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false);
	int n;
	cin >> n;

	vector<vector<int>> idx(n + 1);
	for(int i = 0; i < n; i++) {
		int a;
		cin >> a;
		idx[a].push_back(i);
	}

	int q;
	cin >> q;

	while(q--) {
		int l, r, x;
		cin >> l >> r >> x;
		cout << lower_bound(idx[x].begin(), idx[x].end(), r) - lower_bound(idx[x].begin(), idx[x].end(), l - 1) << endl;
	}
} + 1);

    for (int i = 0; i < Q; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        queries_L[l].push_back({x, i});
        queries_R[r].push_back({x, i});
    }

    vector<int> cnt(2e5 + 1, 0);
    vector<int> ans(Q);

    for (int pos = 1; pos <= N; pos++) {
        for (auto [x, i] : queries_L[pos]) {
            ans[i] -= cnt[x];
        }
        cnt[A[pos]]++;
        for (auto [x, i] : queries_R[pos]) {
            ans[i] += cnt[x];
        }
    }

    for (auto i : ans) 
        cout << i << '\n';
}

int main () {
    solve();
    return 0;
}