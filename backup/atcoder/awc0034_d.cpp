#include <algorithm>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>
#define test(x) cerr << "Line(" << __LINE__ << ") " #x << ' ' << x << endl
#define printv(x)                          \
{                                          \
        for (auto i : x) cout << i << ' '; \
        cout << endl;                      \
}
#define SQ(x) ((x) * (x))
#define SZ(x) ((int)x.size())
#define eb emplace_back
#define ALL(x) x.begin(), x.end()
#define rALL(x) x.begin(), x.end()
#define F first
#define S second

using namespace std;
using lli = long long int;

void solution() {
        int N; cin >> N;
        vector<pair<int, int>> V(N);
        for (auto &[l, r] : V) cin >> l >> r;
        sort(ALL(V), [](auto p1, auto p2) {
                if (p1.S == p2.S) return p1.F > p2.F;
                return p1.S < p2.S;
        });
        int ans = 0;
        int last = 0;
        for (auto [l, r] : V) {
                if (last <= l) {
                        ans++;
                        last = r;
                }
        }
        cout << ans << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
