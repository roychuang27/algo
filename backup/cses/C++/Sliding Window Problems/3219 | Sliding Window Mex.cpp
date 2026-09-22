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

void precompute() {
}

struct Fenwick {
        int N;
        vector<int> b;
        Fenwick(int n) : N(n), b(N+1, 0) {}
        void add(int idx, int delta) {
                idx++;
                for (; idx <= N; idx += (idx & -idx)) b[idx] += delta;
        }
        lli pre(int i) {
                i++;
                lli res = 0;
                for (; i > 0; i -= (i & -i)) res += b[i];
                return res;
        }
};

void solve() {
        int N, K;
        cin >> N >> K;
        vector<int> A(N);
        for (auto &i : A) cin >> i;
        map<int, int> mp;
        Fenwick bit(N+1);
        CORDCOMP comp(A);
        for (int i = 0; i < K; i++) {
                if (!mp[A[i]]) bit.add(comp(A[i]), 1);
                mp[A[i]]++;
        }
        auto find_mex = [&]() -> int {
                // for (int i = 0; i <= N; i++) cerr << bit.pre(i) - bit.pre(i-1) << ' '; cerr << endl;
                int l = 0, r = 1e9;
                while (l < r) {
                        int m = (l + r) / 2;
                        if (bit.pre(comp(m+1)-1) < m+1) r = m;
                        else l = m + 1;
                }
                return l;
        };
        for (int i = K; i < N; i++) {
                cout << find_mex() << ' ';
                mp[A[i-K]]--;
                if (!mp[A[i-K]]) bit.add(comp(A[i-K]), -1);
                if (!mp[A[i]]) bit.add(comp(A[i]), 1);
                mp[A[i]]++;
        }
        cout << find_mex() << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        precompute();
        solve();
        return 0;
}

