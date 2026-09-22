#include <bits/stdc++.h>
#include <cassert>
#ifdef LOCAL
#define dbg(...) do { std::cerr << "Line(" << __LINE__ << ") [" #__VA_ARGS__ "] =>"; ([](auto&&... args){ ((std::cerr << ' ' << args), ...); }(__VA_ARGS__)); std::cerr << std::endl; } while(0)
#define dbgv(x) do { std::cerr << "Line(" << __LINE__ << ") " #x " => ["; int _i=0; for (auto& _e : (x)) std::cerr << (_i++ ? ", " : "") << _e; std::cerr << "]" << std::endl; } while(0)
#else
#define dbg(...) 39
#define dbgv(...) 39
#endif
#define ALL(x) std::begin(x), std::end(x)
#define rALL(x) std::rbegin(x), std::rend(x)
template<class T> T square(T a) { return a * a; }
template<class T> bool chmin(T &a,T b) { if (b < a) { a = b; return 1; } else return 0; }
template<class T> bool chmax(T &a,T b) { if (a < b) { a = b; return 1; } else return 0; }
template<class T, class U> auto vector_recursive(std::size_t n, U value) { return std::vector<T>(n, value); }
template<class T, class... Args> auto vector_recursive(std::size_t n, Args... args) { return std::vector(n, vector_recursive<T>(args...)); }
template<class T, std::size_t n> auto array_fill(T value) { std::array<T, n> res; res.fill(value); return res; }
template <class T, size_t D> struct Matrix { static_assert(D); std::array<size_t, D> s{}; std::vector<T> a; template <class... A> requires(sizeof...(A) == D || sizeof...(A) == D + 1) Matrix(A... x) { if constexpr (sizeof...(A) == D) init<0>(1, x..., T{}); else init<0>(1, x...); } private: template <size_t d, class X, class... R> void init(size_t n, X x, R... r) { if constexpr (d < D) s[d] = x, init<d + 1>(n * s[d], r...); else a.assign(n, x); } template <class... I> size_t pos(I... i) const { static_assert(sizeof...(I) == D); size_t p = 0, d = 0; (((assert(i >= 0 && size_t(i) < s[d]), p = p * s[d++] + size_t(i))), ...); return p; } public: template <class... I> T& operator[](I... i) { return a[pos(i...)]; } template <class... I> const T& operator[](I... i) const { return a[pos(i...)]; } };
template <class T> std::istream& operator>>(std::istream& is, Matrix<T, 1>& m) { for (auto& x : m.a) is >> x; return is; }
template <class T> std::istream& operator>>(std::istream& is, Matrix<T, 2>& m) { for (auto& x : m.a) is >> x; return is; }
template <class T> std::ostream& operator<<(std::ostream& os, const Matrix<T, 1>& m) { for (size_t i = 0; i < m.s[0]; ++i) { if (i) os << ' '; os << m[i]; } return os; }
template <class T> std::ostream& operator<<(std::ostream& os, const Matrix<T, 2>& m) { for (size_t i = 0; i < m.s[0]; ++i) { if (i) os << '\n'; for (size_t j = 0; j < m.s[1]; ++j) { if (j) os << ' '; os << m[i, j]; } } return os; }
template <class T, size_t N> std::istream& operator>>(std::istream& is, std::array<T, N>& a) { for (auto& x : a) is >> x; return is; }
template <class T> std::istream& operator>>(std::istream& is, std::vector<T>& a) { for (auto& x : a) is >> x; return is; }
template <class A, class B> std::istream& operator>>(std::istream& is, std::pair<A, B>& p) { return is >> p.first >> p.second; }
template <class T, size_t N> std::ostream& operator<<(std::ostream& os, const std::array<T, N>& a) { for (size_t i = 0; i < N; ++i) { if (i) os << ' '; os << a[i]; } return os; }
template <class T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& a) { for (size_t i = 0; i < a.size(); ++i) { if (i) os << ' '; os << a[i]; } return os; }
template <class A, class B> std::ostream& operator<<(std::ostream& os, const std::pair<A, B>& p) { return os << p.first << ' ' << p.second; }
template <long long M> struct Mint { long long x; Mint(long long x = 0) : x((x % M + M) % M) {} Mint& operator+=(Mint b) { x += b.x; if (x >= M) x -= M; return *this; } Mint& operator-=(Mint b) { x -= b.x; if (x < 0) x += M; return *this; } Mint& operator*=(Mint b) { x = 1LL * x * b.x % M; return *this; } Mint pow(long long n) const { Mint r = 1, a = *this; for (; n; n >>= 1, a *= a) if (n & 1) r *= a; return r; } Mint inv() const { return pow(M - 2); } Mint& operator/=(Mint b) { return *this *= b.inv(); } friend Mint operator+(Mint a, Mint b) { return a += b; } friend Mint operator-(Mint a, Mint b) { return a -= b; } friend Mint operator*(Mint a, Mint b) { return a *= b; } friend Mint operator/(Mint a, Mint b) { return a /= b; } friend std::ostream& operator<<(std::ostream& os, Mint a) { return os << a.x; } friend std::istream& operator>>(std::istream& is, Mint& a) { long long x; is >> x; a = x; return is; } };

using namespace std;
using lli = long long int;

void precompute() {
}

void solve() {
}

int main() {
#ifndef LOCAL
        cin.tie(nullptr)->sync_with_stdio(false);
#endif
        precompute();
        solve();
        return 0;
}
