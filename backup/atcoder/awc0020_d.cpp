#include <algorithm>
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

using namespace std;
using lli = long long int;

void solution() {
        int N, L;
        cin >> N >> L;
        vector<pair<int, int>> rs(N);
        for (int i = 0; i < N; i++) {
                int x, r;
                cin >> x >> r;
                rs.eb(x-r, x+r);
        }
        sort(ALL(rs));
        int curL = 0;
        for (auto &[l, r] : rs) {
                if (l > curL) {
                        cout << "No\n";
                        return;
                }
                curL = max(curL, r);
        }
        if (curL < L) {
                cout << "No\n";
                return;
        }
        cout << "Yes\n";
        return;
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
