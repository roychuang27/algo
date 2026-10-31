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
                  << WHITE_NORMAL << '\n';
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

using pt = pair<long long, long long>;
using frac = pair<long long, long long>;

bool frac_less(pt a, pt b) {
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
        return (__int128) y1 * x2 < (__int128) y2 * x1;
}

int sign(long long x) {
        if (x < 0) return -1;
        if (x > 0) return 1;
        return 0;
}

frac minimize_sum_y_distance(vector<long long> xs, vector<long long> ys) {
        // minimize |y_i - mx_i|
        int n = xs.size();
        vector<pt> pts;
        pts.reserve(n);

        for (int i = 0; i < n; i++) {
                if (xs[i] < 0) {
                        // transpose
                        xs[i] *= -1;
                        ys[i] *= -1;
                }
                if (xs[i] > 0) {
                        pts.emplace_back(ys[i], xs[i]);
                }
        }

        if (pts.empty()) {
                long long res = 0;
                for (long long y : ys) res += llabs(y);
                return {res, 1};
        }

        sort(ALL(pts), frac_less);

        // a linear function of slope m
        long long suf_x = 0;
        for (auto [_, x] : pts) suf_x += x;

        frac turning_slope = {0, 0};
        long long pre_x = 0;
        for (auto [y, x] : pts) {
                int sign_before = sign(suf_x - pre_x);
                pre_x += x;
                suf_x -= x;
                int sign_after = sign(suf_x - pre_x);
                if (sign_before * sign_after <= 0) {
                        turning_slope = {y, x};
                        break;
                }
        }
        assert(turning_slope != make_pair(0LL, 0LL));

        frac res = {0, turning_slope.second};
        for (int i = 0; i < n; i++) {
                res.first += llabs(xs[i] * turning_slope.first - ys[i] * turning_slope.second);
        }

        long long g = gcd(res.first, res.second);
        return {res.first / g, res.second / g};
}

void solve() {
        int n;
        cin >> n;
        vector<long long> a(n), b(n);
        cin >> a >> b;
        auto r1 = minimize_sum_y_distance(a, b), r2 = minimize_sum_y_distance(b, a);
        if (frac_less(r1, r2)) {
                cout << r1.first << ' ' << r1.second << endl;
        } else {
                cout << r2.first << ' ' << r2.second << endl;
        }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        cin.exceptions(cin.failbit);
        solve();
        return 0;
}
