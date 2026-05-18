#include <iostream>
#include <vector>
#define test(x) cerr << "Line(" << __LINE__ << ") " #x << ' ' << x << endl
#define printv(x)                                  \
        {                                          \
                for (auto i : x) cout << i << ' '; \
                cout << endl;                      \
        }
#define SQ(x) ((x) * (x))
#define SZ(x) ((int)x.size())

using namespace std;
using lli = long long int;

void solution() {
        int N, Q;
        cin >> N >> Q;
        vector<vector<int>> jump(32, vector<int>(N + 1, -1));

        for (int i = 2; i <= N; i++) {
                cin >> jump[0][i];
        }

        for (int k = 1; k <= 31; k++) {
                for (int i = 1; i <= N; i++) {
                        if (jump[k-1][i] == -1)
                                jump[k][i] = -1;
                        else
                                jump[k][i] = jump[k - 1][ jump[k - 1][i] ];
                }
        }
        
        while (Q--) {
                int x, k;
                cin >> x >> k;
                
                for (int j = 0; (1 << j) <= k; j++) {
                        if (x == -1) continue;
                        if ((1 << j) & k) {
                                x = jump[j][x];
                        }
                }
                
                cout << x << '\n';
        }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}