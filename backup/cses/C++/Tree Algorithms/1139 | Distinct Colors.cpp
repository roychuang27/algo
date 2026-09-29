#include <bits/stdc++.h>
#include <cassert>
#ifdef LOCAL
#define dbg(...)                                                               \
        do {                                                                   \
                std::cerr << "\033[1;31m"                                      \
                          << "Line(" << __LINE__ << ") [" #__VA_ARGS__ "] =>"; \
                ([](auto &&...args) {                                          \
                        ((std::cerr << ' ' << args), ...);                     \
                }(__VA_ARGS__));                                               \
                std::cerr << "\033[0m\n";                                      \
        } while (0)
#define dbgv(x)                                                      \
        do {                                                         \
                std::cerr << "\033[1;31m"                            \
                          << "Line(" << __LINE__ << ") " #x " => ["; \
                int _i = 0;                                          \
                for (auto &_e : (x))                                \
                        std::cerr << (_i++ ? ", " : "") << _e;       \
                std::cerr << "]\033[0m\n";                           \
        } while (0)
#else
#define dbg(...) 39
#define dbgv(...) 39
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
        for (auto &e : res) e = value;
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

struct Fenwick {
        int N;
        vector<int> b;
        Fenwick(int n) : N(n), b(n + 1, 0) {}
        void add(int idx, int delta) {
                for (; idx <= N; idx += (idx & -idx)) {
                        b[idx] += delta;
                }
        }
        int qry(int idx) {
                int res = 0;
                for (; idx >= 1; idx -= (idx & -idx)) {
                        res += b[idx];
                }
                return res;
        }
        int sum(int l, int r) {
                return qry(r) - qry(l - 1);
        }
};

void solve() {
        int N;
        cin >> N;
        vector<int> c(N);
        cin >> c;
        vector<int> tmp = c;
        sort(ALL(tmp));
        tmp.erase(unique(ALL(tmp)), tmp.end());
        for (auto &i : c) i = lower_bound(ALL(tmp), i) - tmp.begin();
        vector<int> colors_cnt(N, 0);
        Fenwick bit(2*N);
        vector<vector<int>> adj(N);
        for (int _ = 1; _ < N; _++) {
                int a, b;
                cin >> a >> b;
                a--;
                b--;
                adj[a].emplace_back(b);
                adj[b].emplace_back(a);
        }
        int timer = 1;
        map<int, int> mn_idx;
        function<void(int, int)> dfs = [&](int cur, int par) -> void {
                int time_in = timer++;
                if (mn_idx[c[cur]]) {
                        bit.add(mn_idx[c[cur]], -1);
                }
                mn_idx[c[cur]] = time_in;
                bit.add(time_in, +1);
                for (auto &nxt : adj[cur]) if (nxt != par) {
                        dfs(nxt, cur);
                }
                int time_out = timer++;
                // dbg(cur);
                // for (int i = 1; i <= 2*N; i++) cerr << bit.sum(i, i) << ' ';
                // cerr << endl;
                colors_cnt[cur] = bit.sum(time_in, time_out);
        };
        dfs(0, -1);
        for (auto &i : colors_cnt) cout << i << ' ';
        cout << '\n';
}

int main() {
#ifndef LOCAL
        cin.tie(nullptr)->sync_with_stdio(false);
#endif
        solve();
        return 0;
}
