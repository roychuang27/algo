#include <bits/stdc++.h>
#include <cassert>
#include <queue>
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
                std::cerr << "\033[1;31m";                                   \
                std::cerr << "#" << __LINE__ << '\n';                    \
                std::cerr << "(" #__VA_ARGS__ ") = (";                       \
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

constexpr lli INF = 1e18;

void solve() {
        int N, Q;
        cin >> N >> Q;
        vector<lli> A(N), B(N);
        cin >> A >> B;
        vector<vector<pair<int, lli>>> adj(N+1);
        for (int i = 0; i < N; i++) {
                adj[i].emplace_back((i+1)%N, A[i]);
                adj[(i+1)%N].emplace_back(i, A[i]);
                adj[i].emplace_back(N, B[i]);
                adj[N].emplace_back(i, B[i]);
        }
        priority_queue<pair<lli, int>> pq;
        vector<lli> dis(N+1, INF);
        pq.push({0, N});
        while (!pq.empty()) {
                auto [d, cur] = pq.top();
                pq.pop();
                if (dis[cur] != INF)
                        continue;
                dis[cur] = -d;
                for (auto [nxt, w] : adj[cur]) if (dis[nxt] == INF) {
                        pq.push({d-w, nxt});
                }
        }
        vector<lli> pre(N+1, 0);
        for (int i = 1; i <= N; i++) {
                pre[i] = pre[i-1] + A[i-1];
        }
        for (int _ = 0; _ < Q; _++) {
                int s, t;
                cin >> s >> t;
                s--;
                t--;
                if (t == N) {
                        cout << dis[s] << '\n';
                } else {
                        cout << min({pre[t] - pre[s], pre[N] - (pre[t] - pre[s]), dis[s] + dis[t]}) << '\n';
                }
        }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        cin.exceptions(cin.failbit);
        solve();
        return 0;
}
