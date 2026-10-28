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

void solve() {
        int N, Q;
        cin >> N >> Q;
        vector<int> A(N);
        cin >> A;
        vector<lli> pre(N+1);
        vector<lli> ppre(N+1);
        for (int i = 0; i < N; i++) {
                pre[i+1] = pre[i] + A[i];
        }
        for (int i = 1; i <= N; i++) {
                ppre[i] = ppre[i-1] + pre[i];
        }
        auto f = [&](lli x) -> int {
                lli l = 0, r = N;
                while (l < r) {
                        lli m = (l + r + 1) / 2;
                        if (m * (m + 1) > 2 * x) r = m - 1;
                        else l = m;
                }
                return l;
        };
        dbg(pre, ppre);
        for (int _ = 0; _ < Q; _++) {
                lli l, r;
                cin >> l >> r;
                l--;
                r--;
                lli f1 = f(l), f2 = f(r);
                l -= f1 * (f1 + 1) / 2;
                r -= f2 * (f2 + 1) / 2;
                dbg(l, f1, r, f2);
                dbg(pre[f1+1]-pre[l]);
                dbg(ppre[f2] - ppre[f1+1]);
                dbg(pre[r+1]);
                if (f2 == f1) {
                        cout << pre[r+1] - pre[l] << '\n';
                } else {
                        cout << pre[f1+1] - pre[l] + ppre[f2] - ppre[f1+1] + pre[r + 1] << '\n';
                }
        }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        cin.exceptions(cin.failbit);
        solve();
        return 0;
}
