#include <bits/stdc++.h>
#define SZ(x) ((int) x.size())
using namespace std;
typedef long long lli;

int main() {
	int N, A, B;
	cin >> N >> A >> B;
	vector<lli> pre(N+1);
	pre[0] = 0;
	for (int i = 1; i <= N; i++) {
		int x; cin >> x;
		pre[i] = pre[i-1] + x;
	}
	deque<int> dq;
	lli ans = -1e18;
	for (int i = A; i <= N; i++) {
		if (!dq.empty() && dq.front() < i-B) dq.pop_front();
		while (!dq.empty() && pre[dq.back()] > pre[i-A]) dq.pop_back();
		dq.push_back(i-A);
		ans = max(pre[i] - pre[dq.front()], ans);
	}
	cout << ans << '\n'; 
	return 0;
}
