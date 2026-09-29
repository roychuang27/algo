#include <bits/stdc++.h>
#include <cassert>
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

void solve() {
        int N, Q;
        cin >> N >> Q;
        vector<int> events;
        events.reserve(Q);
        vector<bool> locked(N, 0);
        vector<int> last_idx(N, 0);
        vector<char> colors(Q);
        vector<vector<pair<int, int>>> ranges(N);
        for (int i = 0; i < Q; i++) {
                int t;
                cin >> t;
                if (t == 1) {
                        int x;
                        cin >> x;
                        x--;
                        if (!locked[x]) {
                                ranges[x].emplace_back(last_idx[x], i);
                                locked[x] = true;
                        } else {
                                last_idx[x] = i;
                                locked[x] = false;
                        }
                }
                if (t == 2) {
                        char c;
                        cin >> c;
                        events.emplace_back(i);
                        colors[i] = c;
                }
        }
        for (int i = 0; i < N; i++) {
                if (!locked[i])
                        ranges[i].emplace_back(last_idx[i], Q-1);
        }
        dbg(events, colors);
        auto color_between = [&](int l, int r) -> char {
                auto it = lower_bound(ALL(events), l);
                if (it == events.end() or *it > r) {
                        return 0;
                }
                auto it2 = upper_bound(ALL(events), r);
                it2--;
                return colors[*it2];
        };
        auto find_color = [&](int i) -> char {
                reverse(ALL(ranges[i]));
                for (auto [l, r] : ranges[i]) {
                        int c = color_between(l, r);
                        if (c != 0) {
                                return c;
                        }
                }
                return 'a';
        };
        for (int i = 0; i < N; i++) {
                cout << find_color(i);
        }
        cout << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        cin.exceptions(cin.failbit);
        solve();
        return 0;
}
