/*
 * Submission ID: 11784238
 * Problem: Increasing Array
 * Link: https://cses.fi/problemset/task/1094
 */

#include <bits/stdc++.h>
using namespace std;

int main ()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> x(n);
    cin >> x[0];
    long long cnt = 0;
    for (int i = 1; i < n; i++) {
        cin >> x[i];
        if (x[i] < x[i-1]) {
            cnt += (x[i-1] - x[i]);
            x[i] = x[i-1];
        }
    }
    cout << cnt << endl;
    return 0;
}