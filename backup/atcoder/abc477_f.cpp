#include <bits/stdc++.h>
#include <atcoder/lazysegtree.hpp>
#include <cassert>
#define RED_BOLD "\033[1;31m"
#define WHITE_NORMAL "\033[0m"
#if defined(LOCAL) && __cplusplus >= 202302L
template <class T> concept Iterable = requires(T x) {
        std::begin(x);
        std::end(x);
};
template <class T> concept TupleLike = requires {
        std::tuple_size<T>::value;
};
template <class T> void dbg_print(const T &x);
template <TupleLike T, size_t... I>
void dbg_print_tuple(const T &x, std::index_sequence<I...>) {
        std::cerr << '(';
        size_t i = 0;
        ((dbg_print(std::get<I>(x)),
          std::cerr << (++i == sizeof...(I) ? "" : ", ")),
         ...);
        std::cerr << ')';
}
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
        } else if constexpr (TupleLike<T>) {
                dbg_print_tuple(
                        x, std::make_index_sequence<std::tuple_size_v<T> >{});
        } else {
                std::cerr << x;
        }
}
#define dbg(...)                                                             \
        do {                                                                 \
                std::cerr << RED_BOLD << "#" << __LINE__ << '\n'             \
                          << "(" #__VA_ARGS__ ") = (";                       \
                bool _first = true;                                          \
                ([&](auto &&...args) {                                       \
                        ((std::cerr << (_first ? "" : ", "), _first = false, \
                          dbg_print(args)),                                  \
                         ...);                                               \
                }(__VA_ARGS__));                                             \
                std::cerr << ')' << WHITE_NORMAL << '\n';                    \
        } while (0)
#define log(x) cerr << RED_BOLD << x << WHITE_NORMAL << endl
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

namespace lazy {
        struct S {
                lli val = 0;
                int len = 0;
        };
        S op(S a, S b) { return {a.val + b.val, a.len + b.len}; }
        S e() { return {0, 0}; }
        using F = lli;
        S m(F f, S s) { return {s.val + f * s.len, s.len}; }
        F c(F f, F g) { return f + g; }
        F id() { return 0LL; }
}

void solve() {
        int N, M, Q;
        cin >> N >> M >> Q;
        vector<pair<int, int>> events(N);
        for (auto &e : events) {
                cin >> e;
                e.first--;
        }
        vector<lli> ans(Q, 0);
        vector<vector<array<int, 4>>> queries(N+1);
        for (int i = 0; i < Q; i++) {
                int r1, r2, c1, c2;
                cin >> r1 >> r2 >> c1 >> c2;
                r1--;
                c1--;
                queries[r1].push_back({c1, c2, i, -1});
                queries[r2].push_back({c1, c2, i, +1});
        }
        vector<lazy::S> tmp(M+1, {0, 1});
        atcoder::lazy_segtree<lazy::S, lazy::op, lazy::e, lazy::F, lazy::m, lazy::c, lazy::id> seg(tmp);
        for (int i = 0; i <= N; i++) {
                for (auto [l, r, id, op] : queries[i]) {
                        ans[id] += seg.prod(l, r).val * op;
                }
                if (i < N) {
                        auto [l, r] = events[i];
                        seg.apply(l, r, +1);
                }
        }
        for (int i = 0; i < Q; i++)
                cout << ans[i] << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        cin.exceptions(cin.failbit);
        solve();
        return 0;
}
