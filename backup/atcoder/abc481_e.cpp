#include <bits/stdc++.h>
#include <cassert>
#define RED_BOLD "\033[1;31m"
#define WHITE_NORMAL "\033[0m"
#if defined(LOCAL) && __cplusplus >= 202302L
#define dbg(...)                                                               \
        std::println(stderr, RED_BOLD "#{}, ({}) = {}" WHITE_NORMAL, __LINE__, \
                     #__VA_ARGS__, std::forward_as_tuple(__VA_ARGS__))
#define log(msg)                                                 \
        std::cerr << RED_BOLD << '#' << __LINE__ << ", " << #msg \
                  << WHITE_NORMAL << std::endl;
#else
#define dbg(...) 39
#define log(...) 39
#endif
#ifdef __cpp_lib_format
#define _FMT_ADD_TYPE_PRINT(T, E)                                    \
        template <> struct std::formatter<T> : std::formatter<int> { \
                auto format(const T &x, auto &c) const {             \
                        return std::format_to(c.out(), "{}", E);     \
                }                                                    \
        };
#else
#define _FMT_ADD_TYPE_PRINT(T, E)
#endif
#define ADD_TYPE_PRINT(T, E)                                    \
        _FMT_ADD_TYPE_PRINT(T, E)                               \
        std::ostream &operator<<(std::ostream &o, const T &x) { \
                return o << (E);                                \
        }
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
template <class T, std::size_t n> auto array_fill(T value) {
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

using frac = pair<long long, long long>;

bool frac_less(frac a, frac b) {
        auto [y1, x1] = a;
        if (x1 < 0) {
                y1 = -y1;
                x1 = -x1;
        }
        auto [y2, x2] = b;
        if (x2 < 0) {
                y2 = -y2;
                x2 = -x2;
        }
        return y1 * x2 < y2 * x1;
}

void solve() {
        int N;
        cin >> N;
        vector<frac> v1, v2;
        v1.reserve(N);
        v2.reserve(N);
        for (int _ = 0; _ < N; _++) {
                lli x, y;
                cin >> x >> y;
                if (x == 0) {
                        assert(y != 0);
                        if (y > 0) v1.emplace_back(1, 0);
                        else v2.emplace_back(1, 0);
                } else {
                        if (x > 0) v1.emplace_back(y, x);
                        else v2.emplace_back(y, x);
                }
        }
        int ans = 0;
        sort(ALL(v1), frac_less);
        sort(ALL(v2), frac_less);
        dbg(v1);
        dbg(v2);
        for (size_t i = 0; i < v1.size(); i++) {
                int cnt = (v1.size() - i - 1) + std::distance(v2.begin(), upper_bound(ALL(v2), v1[i], frac_less));
                chmax(ans, max(N - cnt - 1, cnt) + 1);
        }
        for (size_t i = 0; i < v2.size(); i++) {
                int cnt = (v2.size() - i - 1) + std::distance(v1.begin(), upper_bound(ALL(v1), v2[i], frac_less));
                chmax(ans, max(N - cnt - 1, cnt) + 1);
        }
        cout << ans << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        cin.exceptions(cin.failbit);
        int T;
        cin >> T;
        while (T--)
                solve();
        return 0;
}
