#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#define dbg(...) do { std::cerr << "Line(" << __LINE__ << ") [" #__VA_ARGS__ "] =>"; ([](auto&&... args){ ((std::cerr << ' ' << args), ...); }(__VA_ARGS__)); std::cerr << std::endl; } while(0)
#define dbgv(x) do { std::cerr << "Line(" << __LINE__ << ") " #x " => ["; int _i=0; for (auto& _e : (x)) std::cerr << (_i++ ? ", " : "") << _e; std::cerr << "]" << std::endl; } while(0)
#else
#define dbg(...) 39
#define dbgv(...) 39
#endif
#define ALL(x) std::begin(x), std::end(x)
#define rALL(x) std::rbegin(x), std::rend(x)
template<typename T> struct CORDCOMP { vector<T> v; CORDCOMP(vector<T> x) : v(std::move(x)) { sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end()); } int operator()(const T& x) const { return lower_bound(v.begin(), v.end(), x) - v.begin(); } };
template<class T> T square(T a) { return a * a; }
template<class T> bool chmin(T &a,T b) { if (b < a) { a = b; return 1; } else return 0; }
template<class T> bool chmax(T &a,T b) { if (a < b) { a = b; return 1; } else return 0; }
template<class T, class U> auto vec(size_t n, U value) { return std::vector<T>(n, value); }
template<class T, class... Args> auto vec(size_t n, Args... args) { return std::vector(n, vec<T>(args...)); }
template<class T, size_t n> auto arr(T value) { array<T, n> res; res.fill(value); return res; }
using lli = long long int;

constexpr int MAXVAL = 2e5;
constexpr lli MOD = 1e9 + 7;
int spf[MAXVAL + 1];

void precompute() {
        for (int i = 0; i <= MAXVAL; i++) spf[i] = i;
        for (int i = 2; square(i) <= MAXVAL; i++) {
                if (spf[i] == i) {
                        for (int j = square(i); j <= MAXVAL; j += i) {
                                if (spf[j] == j) {
                                        spf[j] = i;
                                }
                        }
                }
        }
}

lli fpow(lli base, lli exp) {
        lli res = 1;
        while (exp) {
                if (exp & 1) {
                        res *= base;
                        res %= MOD;
                }
                base *= base;
                base %= MOD;
                exp >>= 1;
        }
        return res;
}

lli lcm(vector<int> &v) {
        dbgv(v);
        vector<int> mx(MAXVAL + 1, 0);
        for (int x : v) {
                while (x > 1) {
                        int p = spf[x];
                        int cnt = 0;
                        while (x % p == 0) {
                                x /= p;
                                cnt++;
                        }
                        chmax(mx[p], cnt);
                }
       }
        lli res = 1;
        for (int p = 2; p <= MAXVAL; p++) {
                res *= fpow(p, mx[p]);
                res %= MOD;
        }
        return res;
}

void solve() {
        int N;
        cin >> N;
        vector<int> P(N);
        for (auto &i : P) {
                cin >> i;
                i--;
        }
        vector<bool> vis(N, 0);
        vector<int> v;
        for (int i = 0; i < N; i++) if (!vis[i]) {
                int len = 0;
                int j = i;
                while (!vis[j]) {
                        vis[j] = 1;
                        j = P[j];
                        len++;
                }
                v.emplace_back(len);
        }
        cout << lcm(v) << '\n';
}

int main() {
        #ifndef LOCAL
        cin.tie(nullptr)->sync_with_stdio(false);
        #endif
        precompute();
        solve();
        return 0;
}
