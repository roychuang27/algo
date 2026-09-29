#include <bits/stdc++.h>
#include <cassert>
#define RED_BOLD "\033[1;31m"
#define WHITE_NORMAL "\033[0m"
#if defined(LOCAL) && __cplusplus >= 202302L
#define dbg(...) std::println(stderr, RED_BOLD "#{}\n({}) = {}" WHITE_NORMAL, __LINE__, #__VA_ARGS__, std::forward_as_tuple(__VA_ARGS__))
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

lli nC3(lli n) {
        if (n < 3) return 0LL;
        return n * (n - 1) * (n - 2) / 6;
}

void solve() {
        int N, Q;
        cin >> N >> Q;
        vector<int> A(N);
        cin >> A;
        vector<int> tmp = A;
        sort(ALL(tmp));
        tmp.erase(unique(ALL(tmp)), tmp.end());
        for (int &i : A) i = distance(tmp.begin(), lower_bound(ALL(tmp), i));
        vector<lli> ans(Q, 0);
        vector<array<int, 3>> qs(Q);
        for (int i = 0; i < Q; i++) {
                int l, r;
                cin >> l >> r;
                l--;
                r--;
                qs[i] = {l, r, i};
        }
        int K = sqrt(N);
        sort(ALL(qs), [&](auto qa, auto qb) {
                if (qa[0] / K != qb[0] / K) {
                        return qa[0] / K < qb[0] / K;
                }
                if ((qa[0] / K) & 1) {
                        return qa[1] > qb[1];
                } else {
                        return qa[1] < qb[1];
                }
        });
        lli cur = 0;
        vector<lli> cnt(N);
        auto add = [&](int n) {
                if (cnt[n] >= 3) {
                        cur -= nC3(cnt[n]);
                }
                cnt[n]++;
                if (cnt[n] >= 3) {
                        cur += nC3(cnt[n]);
                }
        };
        auto del = [&](int n) {
                if (cnt[n] >= 3) {
                        cur -= nC3(cnt[n]);
                }
                cnt[n]--;
                if (cnt[n] >= 3) {
                        cur += nC3(cnt[n]);
                }
        };
        int l = 0, r = -1;
        for (auto [ql, qr, id] : qs) {
                while (ql < l) add(A[--l]);
                while (r < qr) add(A[++r]);
                while (l < ql) del(A[l++]);
                while (qr < r) del(A[r--]);
                ans[id] = cur;
        }
        for (lli i : ans) {
                cout << i << '\n';
        }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        cin.exceptions(cin.failbit);
        solve();
        return 0;
}
