#include <bits/stdc++.h>
#include <cassert>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#define fir(x, a, b) for (int x = (a); x < (b); x++)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
// I'll give them a shelter like you've done for me~
#if defined(SHELTER) && defined(__cpp_lib_print)
#define line(...) println(stderr, "\033[1;31m#{} passed\033[0m", __LINE__)
#define dbg(...)                                   \
        println(stderr,                            \
                "\033[1;31m#{}, ({}) = {}\033[0m", \
                __LINE__,                          \
                #__VA_ARGS__,                      \
                forward_as_tuple(__VA_ARGS__))
#else
#define line(...) 39
#define dbg(...) 39
#endif
template <class T>
T pow(T a, ull n) {
        T r = T(1);
        for (; n; n >>= 1, a = a * a) {
                if (n & 1) {
                        r = r * a;
                }
        }
        return r;
}
template <bool s = 1, class T>
bool chmin(T &a, T b) {
        return (s ? b < a : b <= a) && (a = b, 1);
}
template <bool s = 1, class T>
bool chmax(T &a, T b) {
        return (s ? a < b : a <= b) && (a = b, 1);
}
template <class T, size_t n>
auto array_fill(T v) {
        array<T, n> r;
        r.fill(v);
        return r;
}
template <class A, class B>
istream &operator>>(istream &i, pair<A, B> &p) {
        return i >> p.first >> p.second;
}
template <class T, size_t N>
istream &operator>>(istream &i, array<T, N> &a) {
        for (auto &x : a) {
                i >> x;
        }
        return i;
}
template <class T>
istream &operator>>(istream &i, vector<T> &a) {
        for (auto &x : a) {
                i >> x;
        }
        return i;
}
template <class T>
struct ITER {
        const T &v;
        string_view s = " ";
        ITER(T &_v):
                v(_v),
                s(" ") {
        }
        ITER(T &_v, string_view _s):
                v(_v),
                s(_s) {
        }
        friend ostream &operator<<(ostream &o, const ITER<T> &it) {
                string_view p;
                for (const auto &e : it.v) {
                        o << p << e;
                        p = it.s;
                }
                return o;
        }
};

void single_testcase() {
        ${1}
}

int main() {
        cin.tie(0)->sync_with_stdio(0);
        cin.exceptions(cin.failbit);
        int t = 1;
        // cin >> t;
        fir(i, 0, t) {
                cout << (i ? "\n" : "");
                single_testcase();
        }
}
