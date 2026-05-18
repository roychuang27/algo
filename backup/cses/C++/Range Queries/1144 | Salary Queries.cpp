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
 
inline int lowbit(int k) {
    return k & -k;
}
 
void update(vector<int> &fenwick, int N, int pos, int val) {
    while (pos <= N) {
        fenwick[pos] += val;
//        pos ^= (lowbit(pos) << 1);
//        pos ^= lowbit(pos);
		pos += lowbit(pos);
    }
}
 
int query(vector<int> &fenwick, int pos) {
	int res = 0;
    while (pos >= 1) {
        res += fenwick[pos];
        pos ^= lowbit(pos);
    }
    return res;
}
 
map<int, int> mp;
vector<int> fenwick(1e6, 0);
vector<int> nums;
 
int main() {
	int N, Q;
	cin >> N >> Q;
	vector<int> ps(N + 5);
	for (int i = 1; i <= N; i++) {
		cin >> ps[i];
		nums.eb(ps[i]);
	}
	vector<pair<int, int>> qs(Q);
	vector<int> qt(Q);
	for (int i = 0; i < Q; i++) {
		char c; cin >> c;
		if (c == '?') {
			qt[i] = 1;
			int a, b;
			cin >> a >> b;
			a--;
			nums.eb(a);
			nums.eb(b);
			qs[i] = MP(a, b);
		} else {
			qt[i] = 2;
			int k, x;
			cin >> k >> x;
			nums.eb(x);
			qs[i] = MP(k, x);
		}
	}
 
	sort(nums.begin(), nums.end());
	nums.resize(unique(nums.begin(), nums.end()) -  nums.begin());
    auto idx = [&](int x) {
        return (int)(lower_bound(nums.begin(), nums.end(), x) -
                     nums.begin()) + 1;
    };
    
    int ord = SZ(nums);
 
	for (int i = 1; i <= N; i++) {
		update(fenwick, ord, idx(ps[i]), 1);
	}
 
	for (int i = 0; i < Q; i++) {
		int a = qs[i].first;
		int b = qs[i].second;
		if (qt[i] == 1) {
			cout << query(fenwick, idx(b)) - query(fenwick, idx(a)) << '\n';
		} else {
			update(fenwick, ord, idx(ps[a]), -1);
			ps[a] = b;
			update(fenwick, ord, idx(b), 1);
		}
	}
 
	return 0;
}
