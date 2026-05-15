/*
 * Submission ID: 16401628
 * Problem: Increasing Array Queries
 * Link: https://cses.fi/problemset/task/2416
 */

#include <iostream>
#include <functional>
#include <stack>
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

constexpr int INF = 0x3f3f3f3f;

void solution() {
        int N, Q;
        cin >> N >> Q;
        vector<lli> xs(N+1);
        vector<lli> preSum(N, 0);
        for (int i = 0; i < N; i++) {
                cin >> xs[i];
                if (i != 0) preSum[i] = preSum[i-1] + xs[i];
                else        preSum[i] = xs[i];
        }
        xs[N] = INF;
        function<lli(int, int)>
        range_sum = [&](int a, int b) -> lli {
                if (a == 0) return preSum[b];
                else        return preSum[b] - preSum[a-1];
        };
        vector jump(32, vector<pair<int, lli>> (N+1));
        stack<int> stk;
        stk.push(N);
        for (int i = N-1; i >= 0; i--) {
                while (xs[stk.top()] <= xs[i]) stk.pop();
                int t = stk.top();                
                jump[0][i] = {
                        t, 
                        xs[i]*(t-i-1) - range_sum(i+1, t-1)
                };
                stk.push(i);
        }
        jump[0][N] = {N, 0};
        for (int k = 1; k <= 31; k++) {
                for (int i = 0; i <= N; i++) {
                        int &nxt = jump[k-1][i].first;
                        jump[k][i] = {
                                jump[k-1][nxt].first,
                                jump[k-1][i].second + jump[k-1][nxt].second
                        };
                }
        }
        
        while(Q-->0) {
                int a, b; cin >> a >> b;
                --a; --b;
                lli ans = 0;
                for (int j = 31; j >= 0; j--) {
                        int &nxt = jump[j][a].first;
                        if (nxt <= b) {
                                ans += jump[j][a].second;
                                a = nxt;
                        }
                }
                if (a < b) {
                        ans += xs[a]*(b-a) - range_sum(a+1, b);
                }
                cout << ans << '\n';
        }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}