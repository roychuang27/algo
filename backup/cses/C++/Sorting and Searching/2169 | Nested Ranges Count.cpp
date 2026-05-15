/*
 * Submission ID: 14525226
 * Problem: Nested Ranges Count
 * Link: https://cses.fi/problemset/task/2169
 */

#pragma GCC optimize("Ofast")
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#define fastio cin.tie(0)->sync_with_stdio(false)
#define eb emplace_back
#define test(x) cerr << "Line(" << __LINE__ << ") " #x << ' ' << x << endl
#define printv(x)                          \
    {                                      \
        for (auto i : x) cout << i << ' '; \
        cout << endl;                      \
    }
#define pii pair<int, int>
#define pll pair<lli, lli>
#define ALL(x) x.begin(), x.end()
#define rALL(x) x.rbegin(), x.rend()
#define MP(x, y) make_pair((x), (y))
#define SQ(x) ((x) * (x))
#define SZ(x) ((int)x.size())

using namespace std;
typedef long long int lli;

template <typename A, typename B>
ostream& operator<<(ostream& o, pair<A, B> a) {
    return o << a.first << ' ' << a.second;
}
template <typename A, typename B>
istream& operator>>(istream& o, pair<A, B>& a) {
    return o >> a.first >> a.second;
}

inline int lowbit(int k) {
    return k & -k;
}
 
void update(vector<int> &fenwick, int N, int pos, int val) {
    while (pos <= N) {
        fenwick[pos] += val;
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

void solve() {
    int N;
    cin >> N;
    vector<pii> ranges(N);
    vector<int> id(N);
    vector<int> ans1(N), ans2(N);
    vector<int> nums;
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        nums.eb(x);
        nums.eb(y);
        ranges[i] = {x, y};
        id[i] = i;
    }
    sort(nums.begin(), nums.end());
    nums.resize(unique(nums.begin(), nums.end()) - nums.begin());
    auto idx = [&](int x) {
        return (int)(lower_bound(nums.begin(), nums.end(), x) - nums.begin()) + 1;
    };

    for (int i = 0; i < N; i++) {
        ranges[i].first = idx(ranges[i].first);
        ranges[i].second = idx(ranges[i].second);
    }

    sort(ALL(id), [&](int a, int b) {
        if (ranges[a].first == ranges[b].first) return ranges[a].second < ranges[b].second;
        return ranges[a] > ranges[b];
    });

    vector<int> BIT1(2 * N + 5, 0);
    for (int i = 0; i < N; i++) {
        auto [x, y] = ranges[id[i]];
        ans1[id[i]] = query(BIT1, y);
        update(BIT1, 2*N, y, 1);
    }
    printv(ans1);

    reverse(ALL(id));
    
    vector<int> BIT2(2 * N + 5, 0);
    for (int i = 0; i < N; i++) {
        auto [x, y] = ranges[id[i]];
        // cout << x << ' ' << y << ' ' << endl;
        ans2[id[i]] = query(BIT2, 2*N+1-y);
        update(BIT2, 2*N, 2*N+1-y, 1);
        // for (int j = 1; j <= 2*N; j++) cout << query(BIT2, j) << ' ';
        // cout << endl;
    }
    printv(ans2);
}

int main() {
    fastio;
    solve();
    return 0;
}