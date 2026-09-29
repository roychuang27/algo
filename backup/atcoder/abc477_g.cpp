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

#ifdef LOCAL
#define dbgm(x)                                                       \
        do {                                                          \
                std::cerr << "\033[1;31m"                             \
                          << "#" << __LINE__ << ' ' << #x << " =>\n"; \
                for (size_t _i = 0; _i < (x).s[0]; ++_i) {            \
                        std::cerr << " [";                            \
                        for (size_t _j = 0; _j < (x).s[1]; ++_j) {    \
                                if (_j)                               \
                                        std::cerr << ", ";            \
                                dbg_print((x)[_i, _j]);               \
                        }                                             \
                        std::cerr << "]\n";                           \
                }                                                     \
                std::cerr << "\033[0m";                               \
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

struct Fenwick {
        int N;
        vector<int> t;
        int lowbit(int x) {
                return x & -x;
        }
        Fenwick(int n) : N(n), t(n) {
        }
        void add(int i, int delta) {
                i++;
                for (; i <= N; i += lowbit(i)) t[i-1] += delta;
        }
        int pre(int i) {
                i++;
                int res = 0;
                for (; i > 0; i -= lowbit(i)) res += t[i-1];
                return res;
        }
        int sum(int l, int r) {
                return pre(r) - pre(l-1);
        }
};

constexpr int B = 30;

void solve() {
        int N, Q;
        cin >> N >> Q;
        vector<int> X(N);
        cin >> X;
        vector<vector<int>> adj(N);
        for (int _ = 1; _ < N; _++) {
                int u, v;
                cin >> u >> v;
                u--;
                v--;
                adj[u].emplace_back(v);
                adj[v].emplace_back(u);
        }
        vector<int> ord(2*N);
        vector<int> tin(2*N, -1), tout(2*N, -1);
        Matrix<int, 2> table(N, B, 0);
        int timer = 0;
        [&](this auto &&self, int cur, int par) -> void {
                tin[cur] = timer++;
                ord[tin[cur]] = cur;
                for (int &nxt : adj[cur]) if (nxt != par) self(nxt, cur);
                if (cur != 0) table[cur, 0] = par;
                tout[cur] = timer++;
                ord[tout[cur]] = cur;
        }(0, -1);
        for (int j = 1; j < B; j++) {
                for (int i = 0; i < N; i++) {
                        table[i, j] = table[table[i, j-1], j-1];
                }
        }
        vector<array<int, 6>> qs;
        vector<int> ans(Q);
        auto anc = [&](int f, int s) -> bool {
                return tin[f] <= tin[s] and tout[s] <= tout[f];
        };
        auto lca = [&](int f, int s) {
                if (anc(f, s)) return f;
                if (anc(f, s)) return s;
                for (int j = B-1; j >= 0; j--) {
                        if (!anc(table[f, j], s)) f = table[f, j];
                }
                return table[f, 0];
        };
        for (int i = 0; i < Q; i++) {
                int s, t, a, b;
                cin >> s >> t >> a >> b;
                s--;
                t--;
                if (tin[s] > tin[t]) swap(s, t);
                if (anc(s, t))
                        qs.push_back({tout[t], tout[s], s, a, b, i});
                else
                        qs.push_back({tout[s], tin[t], lca(s, t), a, b, i});
        }
        int blk_size = sqrt(N);
        sort(ALL(qs), [&](auto q1, auto q2) {
                     if (q1[0] / blk_size != q2[0] / blk_size) {
                             return q1[0] < q2[0];
                     }
                     if ((q1[0] / blk_size) & 1) {
                             return q1[1] / blk_size > q2[1] / blk_size;
                     } else {
                             return q1[1] / blk_size < q2[1] / blk_size;
                     }
        });
        dbg(qs);
        vector<int> cnt(N+1, 0);
        vector<bool> exist(N, 0);
        vector<int> ccnt(N+2, 0);
        ccnt[0] = N;
        // vector<set<int>> e(N+1);
        // for (int i = 1; i <= N; i++) e[0].insert(i);
        auto add = [&](int x) -> void {
                // e[cnt[x]].erase(x);
                cnt[x]++;
                ccnt[cnt[x]]++;
                // e[cnt[x]].insert(x);
        };
        auto del = [&](int x) -> void {
                // e[cnt[x]].erase(x);
                ccnt[cnt[x]]--;
                cnt[x]--;
                // e[cnt[x]].insert(x);
        };
        auto toggle = [&](int i) -> void {
                if (exist[i]) {
                        del(X[i]);
                        exist[i] = 0;
                } else {
                        add(X[i]);
                        exist[i] = 1;
                }
        };
        auto qry = [&](int l, int r) -> int {
                return ccnt[l] - ccnt[r+1];
        };
        int l = 0, r = -1;
        for (auto [ql, qr, c, a, b, i] : qs) {
                while (ql < l) toggle(ord[--l]);
                while (r < qr) toggle(ord[++r]);
                while (l < ql) toggle(ord[l++]);
                while (qr < r) toggle(ord[r--]);
                bool added_lca = 0;
                if (!exist[c]) {
                        add(X[c]);
                        added_lca = 1;
                }
                ans[i] = qry(a, b);
                // dbg(e);
                if (added_lca) del(X[c]);
        }
        for (auto i : ans) cout << i << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        cin.exceptions(cin.failbit);
        solve();
        return 0;
}
