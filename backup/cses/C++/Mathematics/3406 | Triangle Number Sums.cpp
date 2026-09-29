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
                std::cerr << "\033[1;31m(" #__VA_ARGS__ ") = (";             \
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

vector<lli> triangle_numbers;
constexpr int B = 2e6 + 10;

void precompute() {
        triangle_numbers.reserve(B);
        lli sum = 0;
        for (lli i = 1; i <= B; i++) {
                sum += i;
                triangle_numbers.emplace_back(sum);
        }
}

bool is_triangle_number(lli x) {
        // dbg(triangle_numbers);
        auto it = lower_bound(ALL(triangle_numbers), x);
        if (it == triangle_numbers.end()) return false;
        return *it == x;
}

bool is_sum_of_two_triangle_numbers(lli x) {
        int l = 0, r = B-1;
        while (l <= r) {
                if (triangle_numbers[l] + triangle_numbers[r] == x) return true;
                else if (triangle_numbers[l] + triangle_numbers[r] < x) l++;
                else r--;
        }
        return false;
}

void solve() {
        lli N;
        cin >> N;
        if (is_triangle_number(N)) {
                cout << 1 << '\n';
        } else {
                if (is_sum_of_two_triangle_numbers(N)) {
                        cout << 2 << '\n';
                } else {
                        cout << 3 << '\n';
                }
        }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        cin.exceptions(cin.failbit);
        precompute();
        int T;
        cin >> T;
        while (T--)
                solve();
        return 0;
}

