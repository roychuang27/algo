#include <bits/stdc++.h>
using lli = long long int;
using namespace std;

int find_smallest_prime(int n) {
        int maxValue = 2 * n + 1000000;
        vector<bool> is_prime(maxValue + 1, true);
        vector<int> primes;
        is_prime[0] = false;
        is_prime[1] = true;
        for (int i = 2; i <= maxValue; i++) {
                if (is_prime[i]) {
                        primes.push_back(i);
                        if (i > n) {
                                return i;
                        }
                }
                for (const int &p : primes) {
                        if (i * p > maxValue)
                                break;
                        is_prime[i * p] = false;
                        if (i % p == 0)
                                break;
                }
        }
        return -1;
}

int find_smallest_perfect_square(int n) {
        int l = 1, r = 2000;
        while (l < r) {
                int m = (l + r) / 2;
                if (m * m > n) {
                        r = m;
                } else {
                        l = m + 1;
                }
        }
        return l * l;
}

int find_smallest_perfect_cube(int n) {
        int l = 1, r = 200;
        while (l < r) {
                int m = (l + r) / 2;
                if (m * m * m > n) {
                        r = m;
                } else {
                        l = m + 1;
                }
        }
        return l * l * l;
}


int main() {
        int N;
        cin >> N;
        cout << find_smallest_prime(N) << ' ' << find_smallest_perfect_square(N) << ' ' << find_smallest_perfect_cube(N);
        return 0;
}