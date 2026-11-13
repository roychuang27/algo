#include <bits/stdc++.h>
#include <cassert>
using namespace std;
using ll = long long;
using ull = unsigned long long;
// I'll give them a shelter like you've done for me~
#if defined(SHELTER) && defined(__cpp_lib_print)
#define PASSED() \
        println(stderr, "\033[1;31m#{} passed\033[0m", __LINE__);
#define DBG(...)                                   \
        println(stderr,                            \
                "\033[1;31m#{}, ({}) = {}\033[0m", \
                __LINE__,                          \
                #__VA_ARGS__,                      \
                forward_as_tuple(__VA_ARGS__))
#else
#define PASSED()
#define DBG(...)
#endif
template <class T, unsigned_integral U>
T pow(T a, U n) {
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

void single_testcase() {
        ${1}
}

int main() {
        cin.tie(0)->sync_with_stdio(0);
        cin.exceptions(cin.failbit);
        int t = 1;
        // cin >> t;
        for (int i = 0; i < t; i++) {
                cout << (i ? "\n" : "");
                single_testcase();
        }
}
