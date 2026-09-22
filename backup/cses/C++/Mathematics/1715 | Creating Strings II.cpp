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
template<typename T, std::size_t N> using arr = std::array<T, N>;
using lli = long long int;

constexpr lli MOD = 1e9 + 7;
constexpr int MAXN = 1e6;
lli fact[MAXN + 1];

void precompute() {
        fact[0] = 1;
        for (int i = 1; i <= MAXN; i++) fact[i] = fact[i-1] * i % MOD;
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

lli inv(lli num) {
        return fpow(num, MOD - 2);
}

void solve() {
        string S;
        cin >> S;
        map<char, int> cnt;
        int N = S.size();
        for (char c : S) cnt[c]++;
        lli ans = fact[N];
        dbg(ans);
        for (auto [c, v] : cnt) {
                ans *= inv(fact[v]);
                ans %= MOD;
        }
        cout << ans << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        precompute();
        solve();
        return 0;
}

