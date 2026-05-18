#include <bits/stdc++.h>
#define SZ(x) ((int) x.size())
using namespace std;

using lli = long long int;

lli dp[20][10][2][2];

lli solve(string &s, int i, int prev_digit, bool leading_zero, bool tight) {
        if (s == "-1")
                return 0;
        
        if (i == SZ(s))
                return 1;
        if (dp[i][prev_digit][leading_zero][tight] != -1)
                return dp[i][prev_digit][leading_zero][tight];
        
        lli res = 0;
        int upper_bound;
        if (tight)
                upper_bound = s[i] - '0';
        else
                upper_bound = 9;
        
        for (int cur_digit = 0; cur_digit <= upper_bound; cur_digit++) {
                if (cur_digit == prev_digit and cur_digit != 0)
                        continue;
                if (cur_digit == 0 and cur_digit == prev_digit and !leading_zero)
                        continue;
                
                res += solve(s, i+1, cur_digit, leading_zero&(cur_digit==0), tight&(cur_digit == upper_bound));
        }

        dp[i][prev_digit][leading_zero][tight] = res;
        return res;
}

int main() {
        lli a, b;
        cin >> a >> b;
        string s1 = to_string(a-1);
        memset(dp, -1, sizeof(dp));
        lli res1 = solve(s1, 0, 0, 1, 1);
        string s2 = to_string(b);
        memset(dp, -1, sizeof(dp));
        lli res2 = solve(s2, 0, 0, 1, 1);

        cout << res2 - res1 << endl;
}