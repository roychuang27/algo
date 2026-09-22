#include <bits/stdc++.h>
#ifdef LOCAL
#define dbg(...) do { std::cerr << "Line(" << __LINE__ << ") [" #__VA_ARGS__ "] =>"; ([](auto&&... args){ ((std::cerr << ' ' << args), ...); }(__VA_ARGS__)); std::cerr << std::endl; } while(0)
#define dbgv(x) do { std::cerr << "Line(" << __LINE__ << ") " #x " => ["; int _i=0; for (auto& _e : (x)) std::cerr << (_i++ ? ", " : "") << _e; std::cerr << "]" << std::endl; } while(0)
#else
#define dbg(...) 39
#define dbgv(...) 39
#endif
#define ALL(x) std::begin(x), std::end(x)
#define rALL(x) std::rbegin(x), std::rend(x)
#define SZ(x) ((int) x.size())
#define SQ(x) ((x) * (x))
#define CORDCOMP(x, fx) std::sort(ALL(x)); x.erase(std::unique(ALL(x)), std::end(x)); const auto fx = [&](int val) -> int { return std::lower_bound(ALL(x), val) - std::begin(x); }
#define fst first
#define sec second

using lli = long long int;
using namespace std;

constexpr int maxN = 1e7;

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        vector<bool> is_prime(maxN + 1, true);
        vector<int> primes;
        is_prime[0] = is_prime[1] = false;
        for (int i = 2; i <= maxN; i++) {
                if (is_prime[i]) primes.emplace_back(i);
                for (int p : primes) {
                        if (i * p > maxN) break;
                        is_prime[i * p] = false;
                        if (i % p == 0) break;
                }
        }
        vector<string> prime_str;
        for (int p : primes) {
                prime_str.emplace_back(to_string(p));
        }

        string s;
        cin >> s;
        int N = SZ(s);

        for (string t : prime_str) {
                if (SZ(t) != N) continue;
                bool f = 1;
                for (int i = 0; i < N and f; i++) {
                        for (int j = 0; j < N and f; j++) {
                                if (t[i] == t[j]) {
                                        if (s[i] != s[j]) {
                                                f = 0;
                                                break;
                                        }
                                } else {
                                        if (s[i] == s[j]) {
                                                f = 0;
                                                break;
                                        }
                                }
                        }
                }
                if (f) {
                        cout << t << '\n';
                        return 0;
                }
        }
        cout << -1 << '\n';

        return 0;
}


