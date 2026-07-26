#include <iostream>
#include <vector>
#define test(x) cerr << "Line(" << __LINE__ << ") " #x << ' ' << x << endl
#define printv(x)                          \
{                                          \
        for (auto i : x) cout << i << ' '; \
        cout << endl;                      \
}
#define SQ(x) ((x) * (x))
#define SZ(x) ((int)x.size())

using namespace std;
using lli = long long int;

void solution() {
        int N; cin >> N;
        int i = 0, j = (N - 1) / 2;
        vector<vector<int>> grid(N, vector<int> (N, 0));
        grid[i][j] = 1;
        for (int k = 2; k <= SQ(N); k++) {
                if (grid[(i+N-1)%N][(j+1)%N] == 0) {
                        grid[(i+N-1)%N][(j+1)%N] = k;
                        i = (i+N-1)%N;
                        j = (j+1)%N;
                } else {
                        grid[(i+1)%N][j] = k;
                        i = (i+1)%N;
                }
        }
        for (const auto &v : grid) printv(v);
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
