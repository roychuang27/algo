/*
 * Submission ID: 11907673
 * Problem: Trailing Zeros
 * Link: https://cses.fi/problemset/task/1618
 */

#include <bits/stdc++.h>
using namespace std;

int main ()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    long long zero_counter = 0;
    while (n) {
        n /= 5;
        zero_counter += n;
    }
    cout << zero_counter << '\n';
    return 0;
}