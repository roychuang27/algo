#include <bits/stdc++.h>
#include <cassert>
#ifdef LOCAL
template <class T> concept Iterable = requires(T x) {
        std::begin(x);
        std::end(x);
};
template <class T> void dbg_print(const T &x) {
        if constexpr (Iterable<T> &&
                      !std::is_convertible_v<T, std::string_view>) {
                std::cerr << '[';
                bool first = true;
                for (const auto &e : x) {
                        if (!first) {
                                std::cerr << ", ";
                        }
                        first = false;
                        dbg_print(e);
                }
                std::cerr << ']';
        } else {
                std::cerr << x;
        }
}
#define dbg(...)                                                             \
        do {                                                                 \
                std::cerr << "\033[1;31m(" #__VA_ARGS__ ") = (";             \
                bool _first = true;                                          \
                ([&](auto &&...args) {                                       \
                        ((std::cerr << (_first ? "" : ", "), _first = false, \
                          dbg_print(args)),                                  \
                         ...);                                               \
                }(__VA_ARGS__));                                             \
                std::cerr << ")\033[0m\n";                                   \
        } while (0)
#else
#define dbg(...) 39
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

#ifdef LOCAL
#define dbgm(x)                                                               \
        do {                                                                  \
                std::cerr << "\033[1;31m"                                     \
                          << "" #x " =>\n";         \
                for (size_t _i = 0; _i < (x).s[0]; ++_i) {                    \
                        std::cerr << " [";                                    \
                        for (size_t _j = 0; _j < (x).s[1]; ++_j)              \
                                std::cerr << (_j ? ", " : "") << (x)[_i, _j]; \
                        std::cerr << "]\n";                                   \
                }                                                             \
                std::cerr << "\033[0m";                                      \
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
                (((assert(i >= 0 && size_t(i) < s[d]),
                   p = p * s[d++] + size_t(i))),
                 ...);
                return p;
        }
        template <class... I> T &operator[](I... i) {
                return a[pos(i...)];
        }
        template <class... I> const T &operator[](I... i) const {
                return a[pos(i...)];
        }
};

constexpr lli INF = 1'000'000'000'000'000'000 + 7'7'777;
using mat = Matrix<lli, 2>;

mat mul(mat a, mat b) {
        mat res(a.s[0], b.s[1], INF);
        for (int i = 0; i < a.s[0]; i++) {
                for (int j = 0; j < a.s[1]; j++) {
                        for (int k = 0; k < b.s[1]; k++) {
                                chmin(res[i, k], a[i, j] + b[j, k]);
                        }
                }
        }
        return res;
}

mat pow(mat a, lli b) {
        assert(b > 0);
        mat res(a.s[0], a.s[0], INF);
        bool f = 0;
        while (b) {
                if (b & 1) {
                        if (f) {
                                res = mul(res, a);
                        } else {
                                res = a;
                                f = 1;
                        }
                }
                a = mul(a, a);
                b >>= 1;
        }
        return res;
}

void solve() {
        int N, M, K;
        cin >> N >> M >> K;
        mat adj_mat(N, N, INF);
        for (int _ = 0; _ < M; _++) {
                int u, v;
                lli c;
                cin >> u >> v >> c;
                u--;
                v--;
                chmin(adj_mat[u, v], c);
        }
        adj_mat = pow(adj_mat, K);
        dbgm(adj_mat);
        if (adj_mat[0, N-1] == INF) {
                cout << -1 << '\n';
        } else {
                cout << adj_mat[0, N-1] << '\n';
        }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        cin.exceptions(cin.failbit);
        solve();
        return 0;
}
