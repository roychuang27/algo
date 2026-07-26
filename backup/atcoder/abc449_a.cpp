#include <iostream>
#include <iomanip>
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

constexpr double PI = 3.141592653589793;

using namespace std;
using lli = long long int;

void solution() {
        int d; cin >> d;
        double r = d / 2.0;
        cout << fixed << setprecision(7) << PI * SQ(r) << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
