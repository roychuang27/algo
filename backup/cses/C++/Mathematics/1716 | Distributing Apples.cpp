#pragma GCC optimize("Ofast")
#include <iostream>
#include <vector>
#define fastio cin.tie(0)->sync_with_stdio(false)
#define eb emplace_back
#define test(x) cerr << "Line(" << __LINE__ << ") " #x << ' ' << x << endl
#define printv(x)                                  \
        {                                          \
                for (auto i : x) cout << i << ' '; \
                cout << endl;                      \
        }
#define pii pair<int, int>
#define pll pair<lli, lli>
#define ALL(x) x.begin(), x.end()
#define rALL(x) x.rbegin(), x.rend()
#define MP(x, y) make_pair((x), (y))
#define SQ(x) ((x) * (x))
#define SZ(x) ((int)x.size())

using namespace std;
typedef long long int lli;

template <typename A, typename B>
ostream& operator<<(ostream& o, pair<A, B> a) {
        return o << a.first << ' ' << a.second;
}
template <typename A, typename B>
istream& operator>>(istream& o, pair<A, B>& a) {
        return o >> a.first >> a.second;
}

constexpr int mod = 1e9 + 7;

lli fpow(lli a, int b) {
        lli res = 1;
        while (b) {
                if (b & 1) res = res * a % mod;
                a = a * a % mod;
                b >>= 1;
        }
        return res % mod;
}

lli modinv(lli a) { return fpow(a, mod - 2); }

void solve() {
        vector<lli> fact(2e6 + 11);
        fact[0] = 1;
        lli m = 1;
        for (int k = 1; k <= 2e6 + 10; k++) {
                m = m * k % mod;
                fact[k] = m;
        }
        int N, M;
        cin >> N >> M;
        int a = N + M - 1, b = N - 1;
        cout << (fact[a] * modinv(fact[b]) % mod) *
                    modinv(fact[a - b]) % mod << '\n';
}

int main() {
        fastio;
        solve();
        return 0;
}
