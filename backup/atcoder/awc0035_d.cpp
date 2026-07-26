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
        int N, M; cin >> N >> M;
        vector<lli> V(N);
        vector<pair<lli, lli>> W(M);
        for (int i = 0; i < N; i++) cin >> V[i];
        for (int i = 0; i < M; i++) cin >> W[i].F >> W[i].S;
        sort(ALL(V));
        sort(ALL(W), [](auto p1, auto p2) {
                return p1.F * p2.S < p2.F * p1.S; // p1.F / p1.S < p2.F / p2.S
        });
        int ans = 0;
        int i = N-1, j = M-1;
        while (i >= 0 and j >= 0) {
                if (V[i] * W[j].S >= W[j].F) {
                        ans++;
                        i--;
                }
                j--;
        }
        cout << ans << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
