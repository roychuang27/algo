#include <iostream>
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
        int N, M;
        cin >> N >> M;
        int x = (N + 1) / 2;
        if (x >= M) cout << "Yes";
        else        cout << "No";
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
