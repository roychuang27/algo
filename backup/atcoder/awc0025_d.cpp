#include <algorithm>
#include <cmath>
#include <cstdio>
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
        int N, S; lli Q; scanf("%d %d %lld", &N, &S, &Q);
        vector<pair<int, int>> X(N);
        int S_val;
        for (int i = 1; i <= N; i++) {
                scanf(" %d", &X[i-1].F);
                X[i-1].S = i;
                if (i == S) S_val = X[i-1].F;
        }
        sort(ALL(X));
#define TWO_POW_LIMIT 60
        vector jmp(TWO_POW_LIMIT+1, vector<int> (N));
        jmp[0][0] = 1;
        jmp[0][N-1] = N-2;
        for (int i = 1; i < N-1; i++) {
                int a = i-1, b = i+1;
                if (abs(X[b].F-X[i].F) < abs(X[i].F-X[a].F)) {
                        jmp[0][i] = b;
                } else if (abs(X[b].F-X[i].F) > abs(X[i].F-X[a].F)) {
                        jmp[0][i] = a;
                } else {
                        if (X[a].S < X[b].S) jmp[0][i] = a;
                        else                 jmp[0][i] = b;
                }
        }
        for (int k = 1; k <= TWO_POW_LIMIT; k++) {
                for (int i = 0; i < N; i++) {
                        jmp[k][i] = jmp[k-1][ jmp[k-1][i] ];
                }
        }
        int p = lower_bound(ALL(X), pair<int, int>{S_val, 0}) - X.begin();
        for (int j = TWO_POW_LIMIT; j >= 0; j--) if (Q & (1LL << j)) {
                p = jmp[j][p];
        }
        printf("%d", X[p].S);
}

int main() {
        solution();
        return 0;
}
