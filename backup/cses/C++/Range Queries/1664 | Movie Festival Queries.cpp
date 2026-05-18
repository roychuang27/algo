#include <algorithm>
#include <array>
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
const int INF = 0x3f3f3f3f;
const int TIME_UB = 1e6;

void solution() {
        int N, Q;
        cin >> N >> Q;
        vector<array<int, 2>> movies(N);
        for (int i = 0; i < N; i++) cin >> movies[i][0] >> movies[i][1];

        vector jmp(32, vector<int>(TIME_UB+1, -1)); // jmp[movie_id] -> nxt id
        sort(ALL(movies), [&](auto a, auto b) {
                return a[1] < b[1];
        });
        int it = 0;
        for (int t = 0; t <= TIME_UB; t++) {
                while (it < N) {
                        if (movies[it][0] >= t) {
                                jmp[0][t] = movies[it][1];
                                break;
                        }
                        it++;
                }
        }

        for (int k = 1; k <= 31; k++) {
                for (int t = 0; t <= TIME_UB; t++) {
                        if (jmp[k-1][t] != -1)
                                jmp[k][t] = jmp[k-1][ jmp[k-1][t] ];
                }
        }

        while (Q-->0) {
                int a, b;
                cin >> a >> b;
                int ans = 0;
                for (int j = 31; j >= 0; j--) {
                        if (jmp[j][a] != -1 and jmp[j][a] <= b) {
                                ans += (1 << j);
                                a = jmp[j][a];
                        }
                }
                cout << ans << '\n';
        }
} 

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
