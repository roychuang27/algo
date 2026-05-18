#pragma GCC optimize("Ofast")
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
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
    int N, M, K;
    cin >> N >> M >> K;
    vector<vector<pair<int, lli>>> adj(N+1);
    for (int i = 0; i < M; i++) {
        int a, b;
        lli c;
        cin >> a >> b >> c;
        adj[a].eb(b, c);
    }

    priority_queue<pair<lli, int>, vector<pair<lli, int>>, greater<pair<lli, int>>> pq;
    vector<int> cnt(N+1, 0);
    pq.push({0, 1});
    vector<lli> lens;

    while (cnt[N] < K) {
        auto [dist, cur] = pq.top();
        pq.pop();

        if (cnt[cur] >= K) continue;
        cnt[cur]++;

        if (cur == N) {
            lens.eb(dist);
        }
        for (const auto &[nxt, w] : adj[cur]) {
            pq.push({dist+w, nxt});
        }
    }

    printv(lens);

}

int main() {
    fastio;
    solve();
    return 0;
}