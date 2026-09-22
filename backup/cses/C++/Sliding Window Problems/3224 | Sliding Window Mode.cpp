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

void solve() {
        int N, K;
        cin >> N >> K;
        vector<int> A(N);
        for (auto &i : A) cin >> i;
        set<pair<int, int>> st;
        map<int, int> mp;
        for (int i = 0; i < K; i++) {
                mp[A[i]]++;
        }
        for (auto [a, b] : mp) st.insert({-b, a});
        for (int i = K; i < N; i++) {
                cout << st.begin()->second<< ' ';
                st.erase({-mp[A[i]], A[i]});
                st.erase({-mp[A[i-K]], A[i-K]});
                mp[A[i]]++;
                mp[A[i-K]]--;
                st.insert({-mp[A[i]], A[i]});
                st.insert({-mp[A[i-K]], A[i-K]});
        }
        cout << st.begin()->second<< '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        precompute();
        solve();
        return 0;
}

