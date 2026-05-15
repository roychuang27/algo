/*
 * Submission ID: 16489367
 * Problem: Forest Queries II
 * Link: https://cses.fi/problemset/task/1739
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
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
        int N, Q; cin >> N >> Q;
        function<int(int)> lowbit = [&](int x)->int {
                return x & -x;
        };
        vector BIT(N+1, vector<lli> (N+1, 0));
        vector grid(N+1, vector<int> (N+1, 0));
        function<void(int, int, int)> upd = [&](int x, int y, int val)->void {
                for (int _x = x; _x <= N; _x+=lowbit(_x)) {
                        for (int _y = y; _y <= N; _y+=lowbit(_y)) {
                                BIT[_x][_y] += val;
                        }
                }
        };
        function<lli(int, int)> qry = [&](int x, int y)->lli {
                if (x == 0 or y == 0) return 0;
                lli res = 0;
                for (int _x = x; _x > 0; _x-=lowbit(_x)) {
                        for (int _y = y; _y > 0; _y-=lowbit(_y)) {
                                res += BIT[_x][_y];
                        }
                }
                // test(res);
                return res;
        };
        for (int i = 0; i < N; i++) {
                string s; cin >> s;
                for (int j = 0; j < N; j++) {
                        if (s[j] == '*') {
                                grid[i+1][j+1] = 1;
                                upd(i+1, j+1, +1);
                        }
                }
        }
        while (Q-->0) {
                int op; cin >> op;
                if (op == 1) {
                        int y, x; cin >> y >> x;
                        if (grid[y][x]) {
                                grid[y][x] = 0;
                                upd(y, x, -1);
                        } else {
                                grid[y][x] = 1;
                                upd(y, x, +1);
                        }
                } else if (op == 2) {
                        int y1, x1, y2, x2; cin >> y1 >> x1 >> y2 >> x2;
                        cout << qry(y2, x2) - qry(y2, x1-1) - qry(y1-1, x2) + qry(y1-1, x1-1) << '\n';
                }
        }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
