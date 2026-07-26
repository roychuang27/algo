#include <functional>
#include <iostream>
#include <stack>
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
        int N; cin >> N;
        vector<int> H(N);
        for (auto &h : H) cin >> h;
        stack<int> stk;
        stk.push(H[0]);
        lli ans = 0;
        for (int i = 1; i < N; i++) {
                while (not stk.empty() and stk.top() <= H[i]) stk.pop();
                ans += SZ(stk);
                stk.push(H[i]);
        }
        cout << ans << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}