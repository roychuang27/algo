#include <bits/stdc++.h>
#include <cassert>
#define RED_BOLD "\033[1;31m"
#define WHITE_NORMAL "\033[0m"
#if defined(LOCAL) && __cplusplus >= 202302L
#define dbg(...)                                                               \
        std::println(stderr, RED_BOLD "#{}\n({}) = {}" WHITE_NORMAL, __LINE__, \
                     #__VA_ARGS__, std::forward_as_tuple(__VA_ARGS__))
#define log(msg)                                                      \
        std::println(stderr,                                          \
                "{}#{}\n{}{}", RED_BOLD, __LINE__, #msg, WHITE_NORMAL)
#else
#define dbg(...) 39
#define log(...) 39
#endif
#define ALL(x) std::begin(x), std::end(x)
#define rALL(x) std::rbegin(x), std::rend(x)
template <class T> T square(T a) {
        return a * a;
}
template <class T> bool chmin(T &a, T b) {
        if (b < a) {
                a = b;
                return 1;
        } else {
                return 0;
        }
}
template <class T> bool chmax(T &a, T b) {
        if (a < b) {
                a = b;
                return 1;
        } else {
                return 0;
        }
}
namespace std {
template <class T, std::size_t n> constexpr auto array_fill(T value) {
        std::array<T, n> res;
        for (auto &e : res) {
                e = value;
        }
        return res;
}
}
template <class T, size_t N>
std::istream &operator>>(std::istream &is, std::array<T, N> &a) {
        for (auto &x : a) {
                is >> x;
        }
        return is;
}
template <class T>
std::istream &operator>>(std::istream &is, std::vector<T> &a) {
        for (auto &x : a) {
                is >> x;
        }
        return is;
}
template <class A, class B>
std::istream &operator>>(std::istream &is, std::pair<A, B> &p) {
        return is >> p.first >> p.second;
}
using namespace std;
using lli = long long int;

#if defined(LOCAL) && __cplusplus >= 202302L
#define dbgm(x)                                                                \
        do {                                                                   \
                std::println(stderr, RED_BOLD "#{}: {}" WHITE_NORMAL,          \
                             __LINE__, #x);                                    \
                for (size_t _i = 0; _i < (x).s[0]; ++_i) {                     \
                        std::print(stderr, " [");                              \
                        for (size_t _j = 0; _j < (x).s[1]; ++_j)               \
                                std::print(stderr, "{}{}",                     \
                                           _j ? ", " : "", (x).at(_i, _j));    \
                        std::println(stderr, "]");                             \
                }                                                              \
        } while (0)
#else
#define dbgm(...) 39
#endif
template <class T, size_t D> struct Matrix {
        static_assert(D);
        std::array<size_t, D> s{};
        std::vector<T> a;
        template <class... A>
        requires(sizeof...(A) == D || sizeof...(A) == D + 1) Matrix(A... x) {
                if constexpr (sizeof...(A) == D) {
                        init<0>(1, x..., T{});
                } else {
                        init<0>(1, x...);
                }
        }
        template <size_t d, class X, class... R>
        void init(size_t n, X x, R... r) {
                if constexpr (d < D) {
                        s[d] = x, init<d + 1>(n * s[d], r...);
                } else {
                        a.assign(n, x);
                }
        }
        template <class... I> size_t pos(I... i) const {
                static_assert(sizeof...(I) == D);
                size_t p = 0, d = 0;
                (((assert(std::in_range<size_t>(i) && size_t(i) < s[d]),
                   p = p * s[d++] + size_t(i))),
                 ...);
                return p;
        }
        template <class... I> T &at(I... i) {
                return a[pos(i...)];
        }
        template <class... I> const T &at(I... i) const {
                return a[pos(i...)];
        }
};

void solve() {
        int M, A, B;
        cin >> M >> A >> B;
        Matrix<int, 2> v(M, M, 0);
        auto f = [&](this auto &&self, int x, int y) -> int {
                if (v.at(x, y) != 0)
                        return v.at(x, y);
                if (x == 0 or y == 0) {
                       return v.at(x, y) = 2;
                }
                v.at(x, y) = 1;
                int cur = (A * y + B * x) % M;
                return v.at(x, y) = self(y, cur);
        };
        for (int i = 0; i < M; i++) {
                for (int j = 0; j < M; j++) {
                        if (v.at(i, j) == 0) {
                                f(i, j);
                        }
                }
        }
        int ans = 0;
        for (int i = 0; i < M; i++) {
                for (int j = 0; j < M; j++) {
                        if (v.at(i, j) == 1) {
                                // dbg(i, j);
                                ans++;
                        }
                }
        }
        cout << ans << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        cin.exceptions(cin.failbit);
        solve();
        return 0;
}
