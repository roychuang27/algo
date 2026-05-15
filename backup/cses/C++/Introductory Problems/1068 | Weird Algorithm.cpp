/*
 * Submission ID: 14711941
 * Problem: Weird Algorithm
 * Link: https://cses.fi/problemset/task/1068
 */

#include <iostream>
using namespace std;

int main() {
    long long n; cin >> n;
    if (n == 1) {
    	cout << 1 << '\n';
    } else {
        while (n != 1) {
        	cout << n << ' ';
            if (n % 2 == 1) {
                n = 3 * n + 1;
            } else {
                n = n / 2;
            }
        }
        cout << 1 << '\n';
    }

    return 0;
}